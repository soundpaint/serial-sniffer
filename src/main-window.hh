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

#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include <ctime>
#include <QtCore/QObject>
#include <QtCore/QProcess>
#include <QtCore/QString>
#include <QtGui/QIcon>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QAction>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTabWidget>
#include <app-control.hh>
#include <menu-bar.hh>
#include <config-panel.hh>
#include <control-panel.hh>
#include <log-panel.hh>
#include <patch.hh>

class Main_window : public QMainWindow
{
  Q_OBJECT
public:
  explicit Main_window(const uint16_t width,
                       const uint16_t height,
                       App_control *app_control,
                       Patch *patch,
                       Qt_actions *actions,
                       QWidget *parent = 0);
  virtual ~Main_window();
  IConsole_logger *get_console_logger();
  void closeEvent(QCloseEvent *event);
  void load_config_values();
  void config_dirty_changed();
  const bool get_config_dirty() const;
private:
  App_control *_app_control;
  Patch *_patch;
  QIcon *_window_icon;
  Menu_bar *_menu_bar;
  QTabWidget *_tab;
  Config_panel *_config_panel;
  Control_panel *_control_panel;
  Log_panel *_log_panel;
};

#endif /* MAIN_WINDOW_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
