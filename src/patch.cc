/*
 * serial-sniffer -- a serial port sniffer and logger
 *
 * Copyright (C) 2021 Jürgen Reuter
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * As a special exception to the GNU General Public License, if you
 * distribute this file as part of a program that contains a
 * configuration script generated by Autoconf, you may include it
 * under the same distribution terms that you use for the rest of that
 * program.
 *
 * For updates and more info or contacting the author, visit:
 * <https://github.com/soundpaint/serial-sniffer>
 *
 * Author's web site: www.juergen-reuter.de
 */

#include <patch.hh>
#include <unistd.h>
#include <sstream>
#include <log.hh>

Patch::Patch(App_control *app_control)
{
  if (!app_control) {
    Log::fatal("Main_window::Main_window(): app_control is NULL");
  }
  _app_control = app_control;

  _uarts = new std::map<const uint32_t, Uart *>();
  if (!_uarts) {
    Log::fatal("Patch::Patch(): not enough memory");
  }

  _lines = new std::map<const uint32_t, Line *>();
  if (!_lines) {
    Log::fatal("Patch::Patch(): not enough memory");
  }

  _event_listeners = new std::vector<ISerial_event_listener *>();
  if (!_event_listeners) {
    Log::fatal("Patch::Patch(): not enough memory");
  }

  const IConfig *config = _app_control->get_config();
  _com1 = new Uart(_app_control, std::string("COM1"),
                   config->get_serial_in_dev_path());
  if (!_com1) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }
  add_uart(_com1);

  _com2 = new Uart(_app_control, std::string("COM2"),
                   config->get_serial_out_dev_path());
  if (!_com2) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }
  add_uart(_com2);

  _com1->propagate_input_to(_com2);
}

Patch::~Patch()
{
  // locally managed non-Qt objects
  _com1->stop_receiving(true);
  _com1->stop_transmitting(true);
  _com2->stop_receiving(true);
  _com2->stop_transmitting(true);
  remove_uart(_com1);
  remove_uart(_com2);
  delete _event_listeners;
  _event_listeners = 0;
  delete _uarts;
  _uarts = 0;
  delete _lines;
  _lines = 0;
  delete _com1;
  _com1 = 0;
  delete _com2;
  _com2 = 0;

  // elsewhere managed objects
  _app_control = 0;
}

void
Patch::add_uart(Uart *uart)
{
  if (!uart) {
    Log::fatal("Patch::add_uart(): uart is NULL");
  }
  if (!_uarts) {
    Log::fatal("Patch::add_uart(): _uarts is NULL");
  }
  if (!_lines) {
    Log::fatal("Patch::add_uart(): _lines is NULL");
  }

  const uint32_t id = uart->get_id();
  std::map<const uint32_t, Uart *>::iterator iter = _uarts->find(id);
  if (iter != _uarts->end()) {
    std::stringstream msg;
    msg << "Patch::add_uart(): id "
        << id << " already assigned to uart "
        << iter->second->get_name();
    Log::fatal(msg.str());
  }
  (*_uarts)[id] = uart;

  const std::vector<const ILine_info *> lines = uart->get_all_lines();
  for (auto line_info = std::begin(lines);
       line_info != std::end(lines); ++line_info) {
    (*_lines)[(*line_info)->get_id()] = (Line *)(*line_info);
  }

  const int size = _event_listeners->size();
  for (int index = 0; index < size; index++) {
    ISerial_event_listener *listener = (*_event_listeners)[index];
    uart->add_event_listener(listener);
  }
}

void
Patch::remove_uart(Uart *uart)
{
  if (!uart) {
    Log::fatal("Patch::remove_uart(): uart is NULL");
  }
  if (!_uarts) {
    Log::fatal("Patch::remove_uart(): _uarts is NULL");
  }

  const int size = _event_listeners->size();
  for (int index = 0; index < size; index++) {
    ISerial_event_listener *listener = (*_event_listeners)[index];
    uart->remove_event_listener(listener);

    const std::vector<const ILine_info *> lines = uart->get_all_lines();
    for (auto line_info = std::begin(lines);
         line_info != std::end(lines); ++line_info) {
      ((Line *)(*line_info))->remove_event_listener(listener);
    }
  }

  const uint32_t id = uart->get_id();

  _uarts->erase(id);
}

const std::vector<const IUart_info *>
Patch::get_all_uarts() const
{
  std::vector<const IUart_info *> uarts = std::vector<const IUart_info *>();
  std::map<const uint32_t, Uart *>::iterator it = _uarts->begin();
  while (it != _uarts->end()) {
    uarts.push_back(it->second);
    it++;
  }
  return uarts;
}

Uart *
Patch::lookup_uart_by_id(const uint32_t id) const
{
  std::map<uint32_t, Uart *>::iterator it = _uarts->find(id);
  if (it == _uarts->end()) {
    return NULL;
  }
  return (*_uarts)[id];
}

Line *
Patch::lookup_line_by_id(const uint32_t id) const
{
  std::map<uint32_t, Line *>::iterator it = _lines->find(id);
  if (it == _lines->end()) {
    return NULL;
  }
  return (*_lines)[id];
}

const IUart_info *
Patch::get_uart_info(const uint32_t id) const
{
  const Uart *uart = lookup_uart_by_id(id);
  if (!uart) {
    Log::fatal("Patch::get_uart_info(): no uart found with specified id");
  }
  return uart;
}

void
Patch::start_line(const uint32_t id)
{
  Line *line = lookup_line_by_id(id);
  if (!line) {
    Log::fatal("Patch::start_line(): no line found with specified id");
  }
  line->start();
}

void
Patch::stop_line(const uint32_t id)
{
  Line *line = lookup_line_by_id(id);
  if (!line) {
    Log::fatal("Patch::stop_line(): no line found with specified id");
  }
  {
    std::stringstream msg;
    msg << "[STRM1] stop_line " << id;
    Log::trace(msg.str());
  }
  line->stop();
  {
    std::stringstream msg;
    msg << "[STRM2] stop_line " << id;
    Log::trace(msg.str());
  }
}

void
Patch::add_event_listener(ISerial_event_listener *listener)
{
  if (!listener) {
    Log::fatal("Patch::add_event_listener(): listener is NULL");
  }
  if (!_event_listeners) {
    Log::fatal("Patch::add_event_listener(): _event_listeners is NULL");
  }
  _event_listeners->push_back(listener);

  for (auto entry = std::begin(*_uarts);
       entry != std::end(*_uarts); ++entry) {
    Uart *uart = entry->second;
    if (!uart) {
      std::stringstream msg;
      msg << "Patch::add_event-listener(): uart "
          << entry->first << " is NULL";
      Log::fatal(msg.str());
    }
    uart->add_event_listener(listener);
  }
}

void
Patch::remove_event_listener(ISerial_event_listener *listener)
{
  if (!listener) {
    Log::fatal("Patch::remove_event_listener(): listener is NULL");
  }
  if (!_event_listeners) {
    Log::fatal("Patch::remove_event_listener(): _event_listeners is NULL");
  }
  auto tail_start =
    std::remove(_event_listeners->begin(),
                _event_listeners->end(),
                listener);
  _event_listeners->erase(tail_start, _event_listeners->end());

  for (auto entry = std::begin(*_uarts);
       entry != std::end(*_uarts); ++entry) {
    Uart *uart = entry->second;
    if (!uart) {
      std::stringstream msg;
      msg << "Patch::add_event-listener(): uart "
          << entry->first << " is NULL";
      Log::fatal(msg.str());
    }
    uart->remove_event_listener(listener);
  }
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
