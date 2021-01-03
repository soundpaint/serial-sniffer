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

#ifndef LOG_CONFIG_PANEL_HH
#define LOG_CONFIG_PANEL_HH

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>
#include <app-control.hh>

class Log_config_panel : public QGroupBox
{
  Q_OBJECT
public:
  explicit Log_config_panel(App_control *app_control,
                            QWidget *parent);
  virtual ~Log_config_panel();
public slots:
  void save_values();
  void load_values();
  const bool get_dirty() const;
private:
  App_control *_app_control;
  QFormLayout *_layout;
  QCheckBox *_edit_enable_file_logging_on_start;
  QLineEdit *_edit_dir_path;
  QLineEdit *_edit_filename_pattern;
  QCheckBox *_edit_append_on_start;
  bool _dirty;
  void create_actions();
};

#endif /* LOG_CONFIG_PANEL_HH */

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
