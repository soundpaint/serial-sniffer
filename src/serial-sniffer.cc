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

#include <serial-sniffer.hh>
#include <cmath>
#include <fstream>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMessageBox>
#include <config.hh>
#include <log.hh>

const char *
Serial_sniffer::STYLE_SHEET_FILE_PATH = "style.qss";

Serial_sniffer::Serial_sniffer(int &argc, char **argv)
  : App_control(argc, argv)
{
  _main_window = 0;
  srand(1);
  _style_sheet = read_style_sheet(STYLE_SHEET_FILE_PATH);
  setStyleSheet(_style_sheet);

  _config = new Config("config.xml");
  if (!_config) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }

  _actions = new Qt_actions(this);
  if (!_actions) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }

  _streamer_thread = new Streamer_thread(this);
  if (!_streamer_thread) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }

  _file_logger = new File_logger(_config);
  if (!_file_logger) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }
  _streamer_thread->add_event_listener(_file_logger);

  const QRect screen_geometry = QApplication::desktop()->screenGeometry();
  const uint16_t screen_width = screen_geometry.width();
  const uint16_t screen_height = screen_geometry.height();
  {
    std::stringstream msg;
    msg << "[screen_width=" << screen_width <<
      ", screen_height=" << screen_height << "]";
    Log::info(msg.str());
  }

  const bool full_screen = _config->get_full_screen();
  const uint16_t width =
    full_screen ? screen_width : _config->get_window_width();
  const uint16_t height =
    full_screen ? screen_height : _config->get_window_height();
  {
    std::stringstream msg;
    msg << "[width=" << width << ", height=" << height << "]";
    Log::info(msg.str());
  }

  if (_config->get_enable_audio()) {
    // TODO
  } else {
    // TODO
  }

  _main_window = new Main_window(width, height, this, _streamer_thread,
                                 _actions);
  if (!_main_window) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }
  _main_window->load_config_values();
  _console_logger = _main_window->get_console_logger();

  _license_dialog = new License_dialog(_main_window);
  if (!_license_dialog) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }

  _about_dialog = new About_dialog(_main_window);
  if (!_about_dialog) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): not enough memory");
  }

  if (full_screen) {
    _main_window->showFullScreen();
  } else {
    _main_window->show();
  }
  if (!_main_window->isVisible()) {
    Log::fatal("Serial_sniffer::Serial_sniffer(): "
               "invisible main window");
  }
}

Serial_sniffer::~Serial_sniffer()
{
  // locally managed non-Qt objects
  _streamer_thread->remove_event_listener(_file_logger);
  delete _streamer_thread;
  _streamer_thread = 0;
  delete _file_logger;
  _file_logger = 0;
  delete _config;
  _config = 0;
  delete[] _style_sheet;
  _style_sheet = 0;

  // elsewhere managed objects
  _console_logger = 0;
}

void
Serial_sniffer::stop_threads()
{
  if (_streamer_thread) {
    _streamer_thread->stop(true);
  }
}

const char *
Serial_sniffer::read_style_sheet(const char *file_path)
{
  std::ifstream in_file(file_path);
  if (!in_file.good()) {
    Log::warn("Serial_sniffer::read_style_sheet(): no style sheet \"style.qss\"");
    return NULL;
  }
  in_file.seekg(0, std::ios::end);
  const int file_length = in_file.tellg();
  in_file.seekg(0, std::ios::beg);
  char *file_data = new char[file_length + 1];
  if (!file_data) {
    Log::fatal("Serial_sniffer::read_style_sheet(): not enough memory");
  }
  in_file.read(file_data, file_length);
  file_data[file_length] = 0; // null-terminated string
  in_file.close();
  return file_data;
}

void
Serial_sniffer::quit()
{
  if (get_config_dirty()) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(_main_window, tr("Unsaved Configuration Changes"),
                                  tr("There are unsaved configuration changes.  "
                                     "Are you sure to shut down the system anyway?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
      return;
    }
  }
  QApplication::quit();
}

void
Serial_sniffer::show_license()
{
  _license_dialog->show();
}

void
Serial_sniffer::show_about()
{
  _about_dialog->show();
}

void
Serial_sniffer::start_stream()
{
  _streamer_thread->start();
}

void
Serial_sniffer::stop_stream()
{
  _streamer_thread->stop();
}

void
Serial_sniffer::start_file_log()
{
  _file_logger->start();
}

void
Serial_sniffer::stop_file_log()
{
  _file_logger->stop();
}

void
Serial_sniffer::start_console_log()
{
  _console_logger->start();
}

void
Serial_sniffer::stop_console_log()
{
  _console_logger->stop();
}

void
Serial_sniffer::clear_console_log()
{
  _console_logger->clear();
}

Config *
Serial_sniffer::get_config() const
{
  return _config;
}

void
Serial_sniffer::config_dirty_changed()
{
  if (_main_window) {
    _main_window->config_dirty_changed();
  } else {
    // this class has not yet been fully initialized
    // => ignore signals
  }
}

const bool
Serial_sniffer::get_config_dirty() const
{
  return
    _main_window &&
    _main_window->get_config_dirty();
}

void
Serial_sniffer::save_config(std::string file_path) const
{
  _config->save(file_path);
}

const std::vector<const IUart_info *>
Serial_sniffer::get_all_uarts() const
{
  return _streamer_thread->get_all_uarts();
}

const IUart_info *
Serial_sniffer::get_uart_info(const uint32_t id) const
{
  return _streamer_thread->get_uart_info(id);
}

void
Serial_sniffer::start_line(const uint32_t id)
{
  _streamer_thread->start_line(id);
}

void
Serial_sniffer::stop_line(const uint32_t id)
{
  {
    std::stringstream msg;
    msg << "[APP1] stop_line "
        << id;
    Log::debug(msg.str());
  }
  _streamer_thread->stop_line(id);
  {
    std::stringstream msg;
    msg << "[APP2] stop_line "
        << id;
    Log::debug(msg.str());
  }
}

void
Serial_sniffer::closing()
{
  stop_threads();

  // locally managed Qt objects
  _main_window->deleteLater();
  _main_window = 0;
  _license_dialog->deleteLater();
  _license_dialog = 0;
  _about_dialog->deleteLater();
  _about_dialog = 0;
  _actions->deleteLater();
  _actions = 0;
}

int main(int argc, char *argv[])
{
  Serial_sniffer *serial_sniffer = new Serial_sniffer(argc, argv);
  QObject::connect(serial_sniffer, SIGNAL(aboutToQuit()),
                   serial_sniffer, SLOT(closing()));
  const int result = serial_sniffer->exec();

  delete serial_sniffer;
  serial_sniffer = 0;

  exit(result);
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
