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

#include "../test.h"
#include <xplc/utils.h>
#include <xplc/IStaticServiceHandler.h>
#include <xplc/IMonikerService.h>

/*
 * test007
 *
 * Verifies the moniker facility
 */

void test() {
  IServiceManager* servmgr;
  IStaticServiceHandler* handler;
  IMonikerService* monikers;
  IObject* test;
  IObject* obj;

  servmgr = XPLC::getServiceManager();
  ASSERT(servmgr != 0, "could not obtain service manager");

  obj = servmgr->getObject(XPLC::staticServiceHandler);
  ASSERT(obj != 0, "could not obtain static service handler");

  handler = mutateInterface<IStaticServiceHandler>(obj);
  ASSERT(handler != 0, "static service handler does not have the IStaticServiceHandler interface");

  test = new TestObject;
  ASSERT(test != 0, "could not create TestObject");

  handler->addObject(TestObject_CID, test);
  VERIFY(servmgr->getObject(TestObject_CID) == test, "adding the test object did not work");
  VERIFY(test->release() == 1, "incorrect refcount on test object");

  VERIFY(handler->release() == 2, "incorrect refcount on static service handler");

  obj = servmgr->getObject(XPLC::monikers);
  ASSERT(obj != 0, "could not obtain moniker component");
  
  monikers = mutateInterface<IMonikerService>(obj);
  ASSERT(monikers != 0, "moniker service does not have the IMoniker interface");

  monikers->registerObject("testobject", TestObject_CID);

  obj = monikers->resolve("testobject");
  ASSERT(obj != 0, "resolving the test object returned nothing");
  ASSERT(obj == test, "the testobject moniker resolved to something else than the test object");

  VERIFY(obj->release() == 1, "refcount is wrong on the test object");

  servmgr->shutdown();
  VERIFY(servmgr->release() == 0, "service manager has non-zero refcount after shutdown/release");
}

