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

#ifndef UART_HH
#define UART_HH

#include <pthread.h>
#include <iuart-info.hh>
#include <termios.h>
#include <app-control.hh>
#include <line-in.hh>
#include <line-out.hh>

class Uart : public IUart_info, public ISerial_event_listener
{
public:
  Uart(App_control *app_control, const std::string name,
       const std::string dev_path);
  virtual ~Uart();
  const uint32_t get_id() const;
  const std::string get_name() const;
  void add_status_listener(ILine_status_listener *listener);
  void remove_status_listener(ILine_status_listener *listener);
  void add_event_listener(ISerial_event_listener *listener);
  void remove_event_listener(ISerial_event_listener *listener);
  const std::vector<const ILine_info *> get_all_lines() const;
  void start_receiving(const bool ignore_status = false);
  void stop_receiving(const bool ignore_status = false);
  const bool is_receiving() const;
  void start_transmitting(const bool ignore_status = false);
  void stop_transmitting(const bool ignore_status = false);
  const bool is_transmitting() const;
  void filter_line_out_for_line(const ILine_info *line_info);
  void notify_event(const Serial_event *event);
  void propagate_input_to(const Uart *other);
  void unpropagate_input_to(const Uart *other);
private:
  App_control *_app_control;
  uint32_t _id;
  std::string _name;
  std::string _dev_path;
  Line_in *_line_in;
  Line_out *_line_out;
  int _filestream;
  static uint32_t _next_id;
  static uint32_t create_id();
  void open_uart();
  void setup_options();
  void close();
};

std::ostream &operator <<(std::ostream &os, const Uart &uart);

#endif /* UART_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */