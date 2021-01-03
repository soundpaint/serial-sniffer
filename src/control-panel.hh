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

#ifndef CONTROL_PANEL_HH
#define CONTROL_PANEL_HH

#include <QtWidgets/QVBoxLayout>
#include <app-control.hh>
#include <control-file-logger-panel.hh>
#include <control-console-logger-panel.hh>
#include <control-serial-ports-panel.hh>
#include <control-stream-panel.hh>
#include <streamer-thread.hh>

class Control_panel : public QWidget
{
  Q_OBJECT
public:
  explicit Control_panel(App_control *app_control,
                         Streamer_thread *streamer_thread,
                         QWidget *parent);
  virtual ~Control_panel();
  ILogger_status_listener *get_logger_control_panel();
private:
  App_control *_app_control;
  Streamer_thread *_streamer_thread;
  QVBoxLayout *_layout;
  Control_file_logger_panel *_control_file_logger_panel;
  Control_console_logger_panel *_control_console_logger_panel;
  Control_serial_ports_panel *_control_serial_ports_panel;
  Control_stream_panel *_control_stream_panel;
  void create_actions();
};

#endif /* CONTROL_PANEL_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
