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

#ifndef APP_CONTROL_HH
#define APP_CONTROL_HH

#include <vector>
#include <QtWidgets/QApplication>
#include <iapp-control.hh>
#include <iuart-info.hh>
#include <about-dialog.hh>
#include <config.hh>
#include <license-dialog.hh>

class App_control : public QApplication, public IApp_control
{
  Q_OBJECT
public:
  explicit App_control(int &argc, char **argv);
  virtual ~App_control();
  virtual void quit() = 0;
  virtual void show_license() = 0;
  virtual void show_about() = 0;
  virtual void start_stream() = 0;
  virtual void stop_stream() = 0;
  virtual void start_file_log() = 0;
  virtual void stop_file_log() = 0;
  virtual void start_console_log() = 0;
  virtual void stop_console_log() = 0;
  virtual void clear_console_log() = 0;
  virtual const std::vector<const IUart_info *> get_all_uarts() const = 0;
  virtual const IUart_info *get_uart_info(const uint32_t id) const = 0;
  virtual void start_line(const uint32_t id) = 0;
  virtual void stop_line(const uint32_t id) = 0;
  virtual Config *get_config() const = 0;
  virtual void save_config(std::string file_path) const = 0;
public slots:
  virtual void config_dirty_changed() = 0;
};

#endif /* APP_CONTROL_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */