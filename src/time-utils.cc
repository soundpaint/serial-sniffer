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

#include <time-utils.hh>
#include <iomanip>

const std::chrono::time_point<std::chrono::system_clock>
Time_utils::MIN_TIME_POINT = std::chrono::system_clock::time_point::min();

Time_utils::Time_utils()
{
}

Time_utils::~Time_utils()
{
}

const std::chrono::time_point<std::chrono::system_clock>
Time_utils::time_point_now()
{
  return std::chrono::system_clock::now();
}

const std::string
Time_utils::time_point_as_local(const std::chrono::system_clock::time_point
                                time_point)
{
  std::stringstream local_time;
  std::time_t time = std::chrono::system_clock::to_time_t(time_point);
  local_time << std::put_time(std::localtime(&time), "%c %Z");
  return local_time.str();
}

const std::string
Time_utils::time_point_as_gmt(const std::chrono::system_clock::time_point
                              time_point)
{
  std::stringstream gmt_time;
  std::time_t time = std::chrono::system_clock::to_time_t(time_point);
  gmt_time << std::put_time(std::gmtime(&time), "%c %Z");
  return gmt_time.str();
}

const std::string
Time_utils::now_as_local()
{
  return time_point_as_local(time_point_now());
}

const std::string
Time_utils::now_as_gmt()
{
  return time_point_as_gmt(time_point_now());
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */