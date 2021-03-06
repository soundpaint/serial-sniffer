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

#include <serial-config-parity-bit-panel.hh>
#include <log.hh>

Serial_config_parity_bit_panel::
Serial_config_parity_bit_panel(App_control *app_control, QWidget *parent)
  : QWidget(parent)
{
  if (!app_control) {
    Log::fatal("Serial_config_parity_bit_panel::Serial_config_parity_bit_panel(): "
               "app_control is NULL");
  }
  _app_control = app_control;

  _layout = new QHBoxLayout();
  if (!_layout) {
    Log::fatal("Serial_config_parity_bit_panel::Serial_config_parity_bit_panel(): "
               "not enough memory");
  }
  _layout->setContentsMargins(0, 0, 0, 0);
  setLayout(_layout);

  // none
  _rb_none = new QRadioButton(tr("&None"), this);
  if (!_rb_none) {
    Log::fatal("Serial_config_parity_bit_panel::Serial_config_parity_bit_panel(): "
               "not enough memory");
  }
  _layout->addWidget(_rb_none);

  // even
  _rb_even = new QRadioButton(tr("&Even"), this);
  if (!_rb_even) {
    Log::fatal("Serial_config_parity_bit_panel::Serial_config_parity_bit_panel(): "
               "not enough memory");
  }
  _layout->addWidget(_rb_even);

  // odd
  _rb_odd = new QRadioButton(tr("&Odd"), this);
  if (!_rb_odd) {
    Log::fatal("Serial_config_parity_bit_panel::Serial_config_parity_bit_panel(): "
               "not enough memory");
  }
  _layout->addWidget(_rb_odd);

  _layout->addStretch();
  create_actions();
}

Serial_config_parity_bit_panel::~Serial_config_parity_bit_panel()
{
  // locally managed Qt objects
  _layout->deleteLater();
  _layout = 0;
  _rb_none->deleteLater();
  _rb_none = 0;
  _rb_even->deleteLater();
  _rb_even = 0;
  _rb_odd->deleteLater();
  _rb_odd = 0;

  // elsewhere managed objects
  _app_control = 0;

  _dirty = false;
}

const int CASE_EXCEPTION = 42;

void
Serial_config_parity_bit_panel::save_values()
{
  Config *config = _app_control->get_config();
  if (_rb_none->isChecked()) {
    config->set_serial_parity_bit(IConfig::none);
  } else if (_rb_even->isChecked()) {
    config->set_serial_parity_bit(IConfig::even);
  } else if (_rb_odd->isChecked()) {
    config->set_serial_parity_bit(IConfig::odd);
  } else {
    // keep config unmodified
  }
  _dirty = false;
}

void
Serial_config_parity_bit_panel::load_values()
{
  const IConfig *config = _app_control->get_config();
  const IConfig::parity_bit_t parity_bit = config->get_serial_parity_bit();
  switch (parity_bit) {
  case IConfig::none:
    _rb_none->setChecked(true);
    break;
  case IConfig::even:
    _rb_even->setChecked(true);
    break;
  case IConfig::odd:
    _rb_odd->setChecked(true);
    break;
  default:
    throw CASE_EXCEPTION;
  }
  _dirty = false;
}

const bool
Serial_config_parity_bit_panel::get_dirty() const
{
  return
    _dirty;
}

void
Serial_config_parity_bit_panel::create_actions()
{
  connect(_rb_none, &QRadioButton::clicked,
          _app_control, [=](){
            _dirty = true;
            _app_control->config_dirty_changed();
          });
  connect(_rb_even, &QRadioButton::clicked,
          _app_control, [=](){
            _dirty = true;
            _app_control->config_dirty_changed();
          });
  connect(_rb_odd, &QRadioButton::clicked,
          _app_control, [=](){
            _dirty = true;
            _app_control->config_dirty_changed();
          });
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
