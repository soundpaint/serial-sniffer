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

#include <key-bindings.hh>
#include <log.hh>

Key_bindings::Key_bindings()
{
  _bindings = new std::map<int, Action>();
  if (!_bindings) {
    Log::fatal("Key_bindings::Key_bindings(): not enough memory");
  }
}

Key_bindings::~Key_bindings()
{
  // locally managed non-Qt objects
  delete _bindings;
  _bindings = 0;
}

std::map<int, Key_bindings::Action>::iterator
Key_bindings::iterator_begin() const
{
  return _bindings->begin();
}

const std::map<int, Key_bindings::Action>::iterator
Key_bindings::iterator_end() const
{
  return _bindings->end();
}

void
Key_bindings::bind_key_to_action(const int key, const Action action)
{
  std::map<int, Action>::iterator iter = _bindings->find(key);
  if (iter != _bindings->end()) {
    std::stringstream msg;
    msg << "Key_bindings::bind_key_to_action(): action " << action <<
      ": key " << key << " already assigned to action " << iter->second;
    Log::fatal(msg.str());
  }
  (*_bindings)[key] = action;
}

const Key_bindings::Action
Key_bindings::get_action_for_key(const int key) const
{
  std::map<int, Action>::iterator iter = _bindings->find(key);
  if (iter != _bindings->end()) {
    return iter->second;
  }
  return None;
}
