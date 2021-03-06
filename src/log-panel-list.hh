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

#ifndef LOG_PANEL_LIST_HH
#define LOG_PANEL_LIST_HH

#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>
#include <app-control.hh>
#include <iserial-event-listener.hh>

class Log_panel_list :
  public QListWidget,
  public ISerial_event_listener
{
  Q_OBJECT
public:
  static const int BUFFERED_LINES;
  explicit Log_panel_list(App_control *app_control,
                          QWidget *parent);
  virtual ~Log_panel_list();
  void update_events(const std::vector<Serial_event> *_events);
  virtual void notify_event(const Serial_event *event);
  void start_log();
  void stop_log();
  void clear_log();
public slots:
private:
  App_control *_app_control;
  ISerial_event_listener *_log_panel_list_updater;
  bool _accept_events;
  void create_actions();
};

std::ostream &operator <<(std::ostream &os,
                          const Log_panel_list &log_panel_list);

#endif /* LOG_PANEL_LIST_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
