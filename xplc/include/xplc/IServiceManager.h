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

#ifndef __XPLC_ISERVICEMANAGER_H__
#define __XPLC_ISERVICEMANAGER_H__

#if defined(__GNUC__) && __GNUC__ > 3
# pragma GCC system_header
#endif

/** \file
 *
 * The service manager interface.
 */

#include <xplc/IObject.h>
#include <xplc/IComponentProvider.h>

/** \interface IServiceManager IServiceManager.h xplc/IServiceManager.h
 *
 * The %XPLC service manager interface.
 *
 * To do anything with %XPLC, you need to use the service manager. You
 * can obtain it by calling XPLC_getServiceManager().
 *
 * The service manager knows how to find objects from their UUID. It
 * does so by searching a list of service providers (objects that
 * implement the IComponentProvider interface), querying them in turn
 * until the object is found.
 *
 * The component providers are those who know how to find objects through
 * various means. For example, one might get objects from a statically
 * defined list of objects, another might search a directory for
 * plugins, etc...
 *
 * If you want to provide an IComponentProvider, you should register with
 * the service manager.
 */
class IServiceManager: public IComponentProvider {
  UNSTABLE_INTERFACE
public:
  /**
   * Register a provider to be handled by this manager.
   */
  virtual void addProvider(IComponentProvider*) = 0;
    
  /** Register a provider to be handled by this manager, explicitly
   * adding it to the beginning of the list (highest priority).
   */
  virtual void addFirstProvider(IComponentProvider*) = 0;
    
  /** Register a provider to be handled by this manager, explicitly
   * adding it to the end of the list (lowest priority).
   */
  virtual void addLastProvider(IComponentProvider*) = 0;
    
  /** Remove a provider from the list.
   */
  virtual void removeProvider(IComponentProvider*) = 0;
};

/// IServiceManager's IID
DEFINE_IID(IServiceManager, {0x22bdabd9, 0xa63a, 0x4b5e,
  {0xb1, 0x61, 0xb6, 0x36, 0x52, 0x27, 0xd7, 0x8e}});

#endif /* __XPLC_ISERVICEMANAGER_H__ */
