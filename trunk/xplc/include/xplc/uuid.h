/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2002, Pierre Phaneuf
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 */

#ifndef __XPLC_UUID_H__
#define __XPLC_UUID_H__

/* FIXME: these should not be here. */
#include <assert.h>
#include <string.h>
#include <stdlib.h>

static const char UUID_hexchars[] = "0123456789abcdef";

struct UUID {
  unsigned int data0;
  unsigned short data1;
  unsigned short data2;
  unsigned char data3[8];
  /* FIXME: the remaining of this is C++-specific. */
  static const UUID null;
  bool equals(const UUID& uuid) const {
    return
      (this == &uuid) ||
      ((static_cast<const unsigned int*>(&data0)[0] == static_cast<const unsigned int*>(&uuid.data0)[0]) &&
       (static_cast<const unsigned int*>(&data0)[1] == static_cast<const unsigned int*>(&uuid.data0)[1]) &&
       (static_cast<const unsigned int*>(&data0)[2] == static_cast<const unsigned int*>(&uuid.data0)[2]) &&
       (static_cast<const unsigned int*>(&data0)[3] == static_cast<const unsigned int*>(&uuid.data0)[3]));
  }
  void fromString(const char* str) {
    char tmp[3];
    char* end;
    bool format1 = false;
    bool ok = false;

    do {
      if(*str == '{') {
        format1 = true;
        ++str;
      }

      data0 = strtoul(str, &end, 16);
      if(end != str + 8)
        break;
      str = end;

      if(*str != '-')
        break;
      ++str;

      data1 = strtoul(str, &end, 16);
      if(end != str + 4)
        break;
      str = end;

      if(*str != '-')
        break;
      ++str;

      data2 = strtoul(str, &end, 16);
      if(end != str + 4)
        break;
      str = end;

      if(*str != '-')
        break;
      ++str;

      tmp[2] = 0;

      strncpy(tmp, str, 2);
      data3[0] = strtoul(tmp, &end, 16);
      if(end != tmp + 2)
        break;
      str += 2;

      strncpy(tmp, str, 2);
      data3[1] = strtoul(tmp, &end, 16);
      if(end != tmp + 2)
        break;
      str += 2;

      if(*str != '-')
        break;
      ++str;

      for(int i = 2; i < 8; ++i) {
        strncpy(tmp, str, 2);
        data3[i] = strtoul(tmp, &end, 16);
        if(end != tmp + 2)
          break;
        str += 2;
      }

      if(format1) {
        if(*str != '}')
          break;
        ++str;
      }

      if(*str != 0)
        break;

      ok = true;
    } while(0);

    if(!ok)
      *this = null;
  }
  /* str should point to at least 39 bytes of available memory. */
  char* toString(char* str) const {
    assert(str);

    str[0] = '{';
    str[1] = UUID_hexchars[data0 >> 28];
    str[2] = UUID_hexchars[(data0 >> 24) & 0xf];
    str[3] = UUID_hexchars[(data0 >> 20) & 0xf];
    str[4] = UUID_hexchars[(data0 >> 16) & 0xf];
    str[5] = UUID_hexchars[(data0 >> 12) & 0xf];
    str[6] = UUID_hexchars[(data0 >> 8) & 0xf];
    str[7] = UUID_hexchars[(data0 >> 4) & 0xf];
    str[8] = UUID_hexchars[data0 & 0xf];
    str[9] = '-';
    str[10] = UUID_hexchars[(data1 >> 12) & 0xf];
    str[11] = UUID_hexchars[(data1 >> 8) & 0xf];
    str[12] = UUID_hexchars[(data1 >> 4) & 0xf];
    str[13] = UUID_hexchars[data1 & 0xf];
    str[14] = '-';
    str[15] = UUID_hexchars[(data2 >> 12) & 0xf];
    str[16] = UUID_hexchars[(data2 >> 8) & 0xf];
    str[17] = UUID_hexchars[(data2 >> 4) & 0xf];
    str[18] = UUID_hexchars[data2 & 0xf];
    str[19] = '-';
    str[20] = UUID_hexchars[data3[0] >> 4];
    str[21] = UUID_hexchars[data3[0] & 0xf];
    str[22] = UUID_hexchars[data3[1] >> 4];
    str[23] = UUID_hexchars[data3[1] & 0xf];
    str[24] = '-';
    str[25] = UUID_hexchars[data3[2] >> 4];
    str[26] = UUID_hexchars[data3[2] & 0xf];
    str[27] = UUID_hexchars[data3[3] >> 4];
    str[28] = UUID_hexchars[data3[3] & 0xf];
    str[29] = UUID_hexchars[data3[4] >> 4];
    str[30] = UUID_hexchars[data3[4] & 0xf];
    str[31] = UUID_hexchars[data3[5] >> 4];
    str[32] = UUID_hexchars[data3[5] & 0xf];
    str[33] = UUID_hexchars[data3[6] >> 4];
    str[34] = UUID_hexchars[data3[6] & 0xf];
    str[35] = UUID_hexchars[data3[7] >> 4];
    str[36] = UUID_hexchars[data3[7] & 0xf];
    str[37] = '}';
    str[38] = 0;

    return str;
  }
};

#ifdef __GNUC__
#define DEFINE_UUID(symbol) const UUID symbol __attribute__((weak))
#endif
#ifdef _MSC_VER
#define DEFINE_UUID(symbol) __declspec(selectany) const UUID symbol
#endif

DEFINE_UUID(UUID::null) = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};

#endif /* __XPLC_UUID_H__ */
