/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef __XPLC_UTILS_H__
#define __XPLC_UTILS_H__

#undef GENERICDEBUG

#ifdef GENERICDEBUG
#include <stdio.h>
#endif

template<class Component>
class GenericComponent: public Component {
private:
  unsigned int refcount;
public:
  GenericComponent(): refcount(0) {
#ifdef GENERICDEBUG
    fprintf(stderr, "%s: instantiated\n", __PRETTY_FUNCTION__);
#endif
  }
#ifdef GENERICDEBUG
  virtual ~GenericComponent() {
    fprintf(stderr, "%s: destroyed\n", __PRETTY_FUNCTION__);
  }
#endif
  void operator delete(void* self) {
    ::delete self;
  }
  virtual unsigned int addRef() {
#ifdef GENERICDEBUG
    fprintf(stderr, "%s = %i\n", __PRETTY_FUNCTION__, refcount + 1);
#endif

    return ++refcount;
  }
  virtual unsigned int release() {
#ifdef GENERICDEBUG
    fprintf(stderr, "%s = %i\n", __PRETTY_FUNCTION__, refcount - 1);
#endif

    if(--refcount)
      return refcount;

    /* protect against re-entering the destructor */
    refcount = 1;

    delete this;

    return 0;
  }
};

#endif /* __XPLC_UTILS_H__ */
