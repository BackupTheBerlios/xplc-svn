/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Net Integration Technologies, Inc.
 * Copyright (C) 2004-2006, Pierre Phaneuf
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

#ifndef __XPLC_CORE_H__
#define __XPLC_CORE_H__

#include <xplc/IComponentManager.h>

extern "C" IComponentManager* XPLC_getComponentManager();

static const UUID XPLC_staticComponentProvider = {0xf8c76062, 0xf241, 0x4f38,
												  {0x80, 0x8d, 0x73, 0x88,
												   0x31, 0x22, 0x89, 0xd8}};

static const UUID XPLC_moduleLoader = {0x59e3fa68, 0x807c, 0x4ecb,
                                       {0xbc, 0x26, 0xb8, 0x08,
                                        0x37, 0xcb, 0x32, 0x7e}};

static const UUID XPLC_moduleManagerFactory = {0x251c9dfc, 0xc76b, 0x454e,
                                               {0xaa, 0xcb, 0x95, 0x8e,
                                                0x06, 0x35, 0xe2, 0x72}};

static const UUID XPLC_genericFactory = {0x414a69c6, 0x3c9e, 0x49f7,
                                         {0xab, 0x08, 0xe5, 0x5c,
                                          0x7b, 0x6c, 0x23, 0x34}};

static const UUID XPLC_categoryManager = {0xa7b3c486, 0x3725, 0x4500,
                                          {0xa4, 0x4c, 0x59, 0x13,
                                           0x1d, 0x65, 0x9e, 0x20}};

#endif /* __XPLC_CORE_H__ */
