/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2006, Pierre Phaneuf
 * Copyright (C) 2001, Stéphane Lajoie
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

#include "test.h"
#include <xplc/utils.h>

/*
 * test001
 *
 * Verifies that the component manager queries providers properly.
 */

const UUID obj1 = {0xd60530d8, 0x9a3d, 0x4c8e, {0xaa, 0x0b, 0x48, 0x32, 0xc6, 0x9c, 0xf0, 0x1a}};

const UUID obj2 = {0x862adfe4, 0x0821, 0x4f88, {0x85, 0x4a, 0xb9, 0xbf, 0xb9, 0xdc, 0x8a, 0x29}};

const UUID obj3 = {0xe1eabacb, 0x0795, 0x4c6d, {0x81, 0x8e, 0x7a, 0xab, 0x2c, 0x5a, 0x82, 0x25}};

class Provider1: public IComponentProvider {
  IMPLEMENT_IOBJECT(Provider1);
public:
  static Provider1* create() {
    return new Provider1;
  }
  virtual IObject* getObject(const UUID& uuid) {
    if(uuid == obj1) {
      return reinterpret_cast<IObject*>(1);
    }

    return 0;
  }
};

class Provider2: public IComponentProvider {
  IMPLEMENT_IOBJECT(Provider2);
public:
  static Provider2* create() {
    return new Provider2;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(uuid != obj1, "request for the first object reached second provider");

    if(uuid == obj2) {
      return reinterpret_cast<IObject*>(2);
    }

    return 0;
  }
};

class Provider3: public IComponentProvider {
  IMPLEMENT_IOBJECT(Provider3);
public:
  static Provider3* create() {
    return new Provider3;
  }
  virtual IObject* getObject(const UUID& uuid) {
    VERIFY(uuid != obj1, "request for the first object reached third provider");
    VERIFY(uuid != obj2, "request for the second object reached third provider");
    if(uuid == obj3) {
      return reinterpret_cast<IObject*>(3);
    }

    return 0;
  }
};

UUID_MAP_BEGIN(Provider1)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IComponentProvider)
  UUID_MAP_END

UUID_MAP_BEGIN(Provider2)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IComponentProvider)
  UUID_MAP_END

UUID_MAP_BEGIN(Provider3)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IComponentProvider)
  UUID_MAP_END

void test001() {
  IServiceManager* serv;
  IComponentProvider* provider1;
  IComponentProvider* provider2;
  IComponentProvider* provider3;
  IObject* obj;

  serv = XPLC_getServiceManager();

  ASSERT(serv != 0, "could not obtain component manager");

  provider1 = Provider1::create();
  ASSERT(provider1 != 0, "could not instantiate test provider 1");
  serv->addFirstProvider(provider1);

  provider2 = Provider2::create();
  ASSERT(provider2 != 0, "could not instantiate test provider 2");
  serv->addProvider(provider2);

  provider3 = Provider3::create();
  ASSERT(provider3 != 0, "could not instantiate test provider 2");
  serv->addLastProvider(provider3);

  obj = serv->getObject(obj1);
  VERIFY(obj != 0, "object 1 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(1), "asked for object 1 and got another one");

  obj = serv->getObject(obj2);
  VERIFY(obj != 0, "object 2 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(2), "asked for object 2 and got another one");

  obj = serv->getObject(obj3);
  VERIFY(obj != 0, "object 3 was not found");
  VERIFY(obj == reinterpret_cast<IObject*>(3), "asked for object 3 and got another one");

  serv->removeProvider(provider1);
  serv->removeProvider(provider2);
  serv->removeProvider(provider3);

  obj = serv->getObject(obj1);
  VERIFY(!obj, "object 1 still returned after removing provider 1");

  obj = serv->getObject(obj2);
  VERIFY(!obj, "object 2 still returned after removing provider 2");

  obj = serv->getObject(obj3);
  VERIFY(!obj, "object 3 still returned after removing provider 3");

  VERIFY(provider1->release() == 0, "incorrect refcount on provider 1");
  VERIFY(provider2->release() == 0, "incorrect refcount on provider 2");
  VERIFY(provider3->release() == 0, "incorrect refcount on provider 3");

  VERIFY(serv->release() == 0, "component manager has non-zero refcount after release");
}
