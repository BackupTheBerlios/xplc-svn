/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Net Integration Technologies, Inc.
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

#include <xplc/xplc.h>
#include <xplc/utils.h>
#include "monikers.h"

MonikerService* MonikerService::create() {
  return new GenericComponent<MonikerService>;
}

MonikerService::~MonikerService() {
  MonikerNode* node;
  MonikerNode* ptr;

  node = monikers;

  while(node) {
    ptr = node;
    node = node->next;
    delete ptr;
  }

  monikers = 0;
}

IObject* MonikerService::getInterface(const UUID& uuid) {
  for(;;) {
    if(uuid.equals(IObject::IID))
      break;

    if(uuid.equals(IMoniker::IID))
      break;

    if(uuid.equals(IMonikerService::IID))
      break;

    return 0;
  }

  addRef();
  return this;
}

IObject* MonikerService::resolve(const char* aName) {
  MonikerNode* node;
  IServiceManager* servmgr;
  IObject* obj = 0;

  node = monikers;

  while(node) {
    if(strcmp(aName, node->name) == 0) {
      servmgr = XPLC::getServiceManager();
      if(servmgr) {
        obj = servmgr->getObject(node->uuid);
        servmgr->release();
      }
      return obj;
    }

    node = node->next;
  }

  /*
   * No match was found, we return empty-handed.
   */
  return 0;
}

void MonikerService::registerObject(const char* aName, const UUID& aUuid) {
  MonikerNode* node;

  node = monikers;

  while(node) {
    if(strcmp(aName, node->name) == 0)
      break;

    node = node->next;
  }

  /*
   * FIXME: maybe add a "replace" bool parameter? Or would this
   * encourage UUID hijacking too much?
   */
  if(node)
    return;

  node = new MonikerNode(aName, aUuid, monikers);
  monikers = node;
}

