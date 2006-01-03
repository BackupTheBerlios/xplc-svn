/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2006, Pierre Phaneuf
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

#ifndef __XPLC_ISTATICCOMPONENTPROVIDER_H__
#define __XPLC_ISTATICCOMPONENTPROVIDER_H__

#if defined(__GNUC__) && __GNUC__ > 3
# pragma GCC system_header
#endif

#include <xplc/IComponentProvider.h>

/**
 * Component provider for statically linked components.
 */

class IStaticComponentProvider: public IComponentProvider {
  UNSTABLE_INTERFACE
public:
  /** Adds an object to the static component provider. */
  virtual void addObject(const UUID&, IObject*) = 0;
  /** Removes an object from the static component provider. */
  virtual void removeObject(const UUID&) = 0;
};

DEFINE_IID(IStaticComponentProvider, {0x0a599d64, 0x0684, 0x4c44,
  {0x8a, 0xbc, 0xab, 0xfd, 0x5d, 0xe0, 0x22, 0x59}});

#endif /* __XPLC_ISTATICCOMPONENTPROVIDER_H__ */
