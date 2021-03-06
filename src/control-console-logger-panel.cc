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

#include <control-console-logger-panel.hh>
#include <log.hh>

Control_console_logger_panel::
Control_console_logger_panel(App_control *app_control,
                             QWidget *parent)
  : QGroupBox(tr("Con&sole Log"), parent)
{
  if (!app_control) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "app_control is NULL");
  }
  _app_control = app_control;

  _layout = new QVBoxLayout();
  if (!_layout) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  setLayout(_layout);

  _buttons_panel = new QWidget();
  if (!_buttons_panel) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  _layout->addWidget(_buttons_panel);

  _buttons_layout = new QHBoxLayout();
  if (!_buttons_layout) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  _buttons_panel->setLayout(_buttons_layout);

  // clear button
  _button_clear = new QPushButton(tr("&Clear"), this);
  if (!_button_clear) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  _button_clear->setEnabled(true);
  _buttons_layout->addWidget(_button_clear);

  _buttons_layout->addStretch();

  // start button
  _button_start = new QPushButton(tr("&Start"), this);
  if (!_button_start) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  _button_start->setEnabled(true);
  _buttons_layout->addWidget(_button_start);

  // stop button
  _button_stop = new QPushButton(tr("Sto&p"), this);
  if (!_button_stop) {
    Log::fatal("Control_console_logger_panel::Control_console_logger_panel(): "
               "not enough memory");
  }
  _button_stop->setEnabled(false);
  _button_stop->setAutoDefault(true);
  _button_stop->setDefault(true);
  _buttons_layout->addWidget(_button_stop);

  _layout->addStretch();
  create_actions();
}

Control_console_logger_panel::~Control_console_logger_panel()
{
  // locally managed Qt objects
  _layout->deleteLater();
  _layout = 0;
  _buttons_layout->deleteLater();
  _buttons_layout = 0;
  _buttons_panel->deleteLater();
  _buttons_panel = 0;
  _button_clear->deleteLater();
  _button_clear = 0;
  _button_start->deleteLater();
  _button_start = 0;
  _button_stop->deleteLater();
  _button_stop = 0;

  // elsewhere managed objects
  _app_control = 0;
}

void
Control_console_logger_panel::create_actions()
{
  connect(_button_clear, &QPushButton::released,
          _app_control, [=](){ _app_control->clear_console_log(); });
  connect(_button_start, &QPushButton::released,
          _app_control, [=](){ _app_control->start_console_log(); });
  connect(_button_stop, &QPushButton::released,
          _app_control, [=](){ _app_control->stop_console_log(); });
}

void
Control_console_logger_panel::logger_started()
{
  _button_start->setEnabled(false);
  _button_stop->setEnabled(true);
}

void
Control_console_logger_panel::logger_stopped()
{
  _button_start->setEnabled(true);
  _button_stop->setEnabled(false);
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
