/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2003, Pierre Phaneuf
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

#include <xplc/ICategoryManager.h>
#include "test.h"

/*
 * test010
 *
 * Tests categories.
 */

/* FIXME: to be done */
void test010() {
  IServiceManager* servmgr;
  ICategoryManager* catmgr;

  servmgr = XPLC_getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  catmgr = servmgr->getObject(XPLC_categoryManager);
  ASSERT(catmgr != 0, "could not obtain category manager");

  VERIFY(catmgr->release() == 1, "category manager has wrong refcount");

  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after release");
}

