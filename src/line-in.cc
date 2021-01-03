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

#include <line-in.hh>
#include <unistd.h>
#include <log.hh>

Line_in::Line_in(IUart_info *uart_info,
                 const int filestream,
                 const uint32_t buffer_size)
  : Line(uart_info, rx, std::string("RX"), filestream, buffer_size)
{
}

Line_in::~Line_in()
{
}

#define SIMULATE

void
Line_in::transfer_prework()
{
#ifdef SIMULATE
  {
    std::stringstream message;
    message << "Line_in::transfer_prework(): "
            << to_string()
            << ": read next event";
    Log::debug(message.str());
  }
#else
#endif
}

void
Line_in::transfer()
{
#ifdef SIMULATE
  std::unique_lock<std::mutex> lock = acquire_interrupt_lock();
  get_interrupt_condition()->wait_for(lock, std::chrono::milliseconds(9990));
  _buffer[0] = rand() & 0xff;
  {
    std::stringstream message;
    message << "Line_in::transfer(): "
            << to_string()
            << ": generated random value: "
            << (uint32_t)_buffer[0];
    Log::debug(message.str());
  }
  _bytes_read = 1;
#else
  if (_filestream != -1) {
    _bytes_read =
      read(_filestream, (void*)_buffer, _buffer_size);
    if (_bytes_read < 0) {
      return; // line stopped while in read() => drop data
    }
  }
#endif
}

void
Line_in::transfer_postwork()
{
  if (_filestream != -1) {
    if (_bytes_read < 0) {
      switch (errno) {
      case EINTR:
        // TODO: Check if line was requested to stop.
        {
          std::stringstream msg;
          msg << "Line_in::transfer_postwork(): errno=" << errno << "(EINTR)";
          Log::warn(msg.str());
        }
        break;
      default:
        {
          std::stringstream msg;
          msg << "Line_in::transfer_postwork(): errno=" << errno;
          Log::warn(msg.str());
        }
        break;
      }
      // limit bandwidth of retrials just in case of a permanent error
      usleep(4000000);
    } else if (_bytes_read == 0) {
      // no data waiting => do nothing
    } else {
      std::stringstream msg;
      msg << "Line_in::transfer_postwork(): "
          << to_string() << ": "
          << _bytes_read << " byte(s) read" << std::endl;
      Log::debug(msg.str());
      for (int i = 0; i < _bytes_read; i++) {
        {
          std::stringstream message;
          message << "YYYYYYYYYY "
                  << to_string()
                  << ": handling random value: "
                  << (uint32_t)_buffer[i];
          Log::trace(message.str());
        }
        const Serial_event event =
          Serial_event::create_receive_data(this, _buffer[i]);
        notify_event_listeners(&event);
      }
    }
  }
}

/*
 * Local variables:
 *   mode: c++
 *   coding: utf-8
 * End:
 */
