/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_CONFIG_H__
#define __XPLC_CONFIG_H__

/*
 * Platforms that do not support Autoconf should skip including that
 * file.
 */
#if !defined(WIN32)
#include <xplc/autoconf.h>
#endif

#ifdef WIN32
#define UNSTABLE
#endif

#if defined(WITH_DLOPEN) || defined(WIN32)
#define HAVE_DYNAMIC_LOADING
#endif

#endif /* __XPLC_CONFIG_H__ */
