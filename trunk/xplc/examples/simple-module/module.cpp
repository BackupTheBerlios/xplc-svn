/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2004, Pierre Phaneuf
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

#include <xplc/module.h>
#include "simple.h"

/* This is the list of UUIDs that this module can provide objects for,
 * along with a pointer to the function that will provide it. This *
 * example has only one component, but there is no restriction on how
 * many components can a single module have (you do not have to put
 * one component per module).
*/
static const XPLC_ComponentEntry components[] = {
  { SimpleComponent_CID, &getSimpleComponent },
  { UUID_null, 0 }
};

const XPLC_ModuleInfo XPLC_Module = {
  XPLC_MODULE_MAGIC,
  XPLC_MODULE_VERSION_MAJOR,
  XPLC_MODULE_VERSION_MINOR,
  "Simple Example Module",
  components,
  0,
  0
};

