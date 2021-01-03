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

#include <serial-event-pass-all-filter.hh>

const Serial_event_pass_all_filter
Serial_event_pass_all_filter::DEFAULT_INSTANCE = Serial_event_pass_all_filter();

Serial_event_pass_all_filter::Serial_event_pass_all_filter()
{
}

Serial_event_pass_all_filter::~Serial_event_pass_all_filter()
{
}

const bool
Serial_event_pass_all_filter::accept0(const Serial_event *event) const
{
  return true;
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */