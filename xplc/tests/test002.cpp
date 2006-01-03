/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2006, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
 * Copyright (C) 2002-2004, Net Integration Technologies, Inc.
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

#include "test.h"
#include <xplc/utils.h>
#include "../xplc/staticprovider.h"

/*
 * test002
 *
 * Verifies the static component provider.
 */

void test002() {
  IStaticComponentProvider* provider;
  TestObject* test;
  IObject* obj;
  ITestInterface *itest;

  provider = new StaticComponentProvider;
  ASSERT(provider != 0, "could not instantiate static component provider");

  test = new TestObject;
  ASSERT(test != 0, "could not instantiate test object");

  VERIFY(test->getRefCount() == 1, "the test object has an incorrect refcount");

  provider->addObject(TestObject_CID, test);
  VERIFY(test->getRefCount() == 2, "static component provider did not addRef the test component");

  obj = provider->getObject(TestObject_CID);
  ASSERT(obj != 0, "could not get test component from static component provider");

  itest = mutate<ITestInterface>(obj);
  ASSERT(itest != 0, "test component does not have the expected interface");

  VERIFY(test->getRefCount() == 3, "the test object has an incorrect refcount");
  itest->setRefCount(10);
  itest->addRef();
  VERIFY(itest->getRefCount() == 11, "test component has unexpected behavior");
  itest->setRefCount(3);

  VERIFY(itest->release() == 2, "test component has incorrect refcount");

  provider->removeObject(TestObject_CID);
  VERIFY(test->getRefCount() == 1, "static component provider did not release the test component");

  obj = provider->getObject(TestObject_CID);
  VERIFY(!obj, "static component provider did not remove the test component");
  if(obj)
    obj->release();

  VERIFY(provider->release() == 0, "static component provider has non-zero refcount after release");

  VERIFY(test->release() == 0, "test object has non-zero refcount after release");

  xplcdelete test;
}

