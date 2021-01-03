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

#include <qt-actions.hh>
#include <log.hh>

Qt_actions::Qt_actions(IApp_control *app_control)
{
  if (!app_control) {
    Log::fatal("Qt_actions::Qt_actions(): app_control is NULL");
  }
  _app_control = app_control;
}

Qt_actions::~Qt_actions()
{
  // elsewhere managed objects
  _app_control = 0;
}

void
Qt_actions::add_action_file_quit(QAction *action)
{
  connect(action, &QAction::triggered,
          this, &Qt_actions::action_file_quit);
}

void
Qt_actions::action_file_quit()
{
  _app_control->quit();
}

void
Qt_actions::add_action_help_license(QAction *action)
{
  connect(action, &QAction::triggered,
          this, &Qt_actions::action_help_license);
}

void
Qt_actions::action_help_license()
{
  _app_control->show_license();
}

void
Qt_actions::add_action_help_about(QAction *action)
{
  connect(action, &QAction::triggered,
          this, &Qt_actions::action_help_about);
}

void
Qt_actions::action_help_about()
{
  _app_control->show_about();
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */