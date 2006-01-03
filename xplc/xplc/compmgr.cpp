/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2006, Pierre Phaneuf
 * Copyright (C) 2000, Stéphane Lajoie
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

#include <xplc/core.h>
#include <xplc/utils.h>
#include <xplc/factory.h>
#include "compmgr.h"
#include "catmgr.h"
#include "staticprovider.h"
#include "moduleloader.h"
#include "monikers.h"
#include "new.h"
#include "modulemgr.h"

UUID_MAP_BEGIN(ComponentManager)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IComponentManager)
  UUID_MAP_END

static ComponentManager* singleton;

IComponentManager* XPLC_getComponentManager() {
  if(singleton)
    singleton->addRef();
  else {
    IStaticComponentProvider* provider;
    IStaticComponentProvider* provider2;
    IMonikerService* monikers;
    IObject* obj;

    singleton = new ComponentManager;

    if(!singleton)
      return 0;

    provider = new StaticComponentProvider;
    if(!provider) {
      singleton->release();
      return 0;
    }

    /*
     * Populate the static component provider.
     */

    provider2 = new StaticComponentProvider;
    if(provider2) {
      provider->addObject(XPLC_staticComponentProvider, provider2);
      singleton->addProvider(provider2);
      provider2->release();
    } else {
      singleton->release();
      return 0;
    }

    obj = new NewMoniker;
    if(obj) {
      provider->addObject(XPLC_newMoniker, obj);
      obj->release();
    }

    obj = new CategoryManager;
    if(obj) {
      provider->addObject(XPLC_categoryManager, obj);
      obj->release();
    }

    obj = new ModuleLoader;
    if(obj) {
      provider->addObject(XPLC_moduleLoader, obj);
      obj->release();
    }

    obj = new ModuleManagerFactory;
    if(obj) {
      provider->addObject(XPLC_moduleManagerFactory, obj);
      obj->release();
    }

    monikers = new MonikerService;
    if(monikers) {
      monikers->registerObject("new", XPLC_newMoniker);
      provider->addObject(XPLC_monikers, monikers);
      monikers->release();
    }

    singleton->addProvider(provider);

    provider->release();
  }

  return singleton;
}

ComponentManager::~ComponentManager() {
  ProviderNode* next;

  while(providers) {
    next = providers->next;
    delete providers;
    providers = next;
  }

  if(singleton == this)
    singleton = 0;
}

void ComponentManager::addProvider(IComponentProvider* aProvider) {
  ProviderNode* node;
  ProviderNode** ptr;

  ptr = &providers;
  node = *ptr;
  while(node) {
    if(node->provider == aProvider)
      break;

    if(node->intercept) {
      ptr = &node->next;
    }
    node = node->next;
  }

  /*
   * The provider is already there.
   */
  if(node)
    return;

  node = new ProviderNode(aProvider, *ptr, false);
  *ptr = node;
}

void ComponentManager::addFirstProvider(IComponentProvider* aProvider) {
  ProviderNode* node;

  node = providers;
  while(node) {
    if(node->provider == aProvider)
      break;

    node = node->next;
  }

  /*
   * The provider is already there.
   */
  if(node)
    return;

  node = new ProviderNode(aProvider, providers, true);
  providers = node;
}

void ComponentManager::addLastProvider(IComponentProvider* aProvider) {
  ProviderNode* node;
  ProviderNode** ptr;

  ptr = &providers;
  node = *ptr;
  while(node) {
    if(node->provider == aProvider)
      break;

    ptr = &node->next;
    node = *ptr;
  }

  /*
   * The provider is already there.
   */
  if(node)
    return;

  node = new ProviderNode(aProvider, *ptr, false);
  *ptr = node;
}

void ComponentManager::removeProvider(IComponentProvider* aProvider) {
  ProviderNode* node;
  ProviderNode** ptr;

  node = providers;
  ptr = &providers;
  while(node) {
    if(node->provider == aProvider) {
      *ptr = node->next;
      delete node;
      break;
    }

    ptr = &node->next;
    node = *ptr;
  }
}

IObject* ComponentManager::getObject(const UUID& aUuid) {
  IObject* obj;
  ProviderNode* provider;

  provider = providers;
  while(provider) {
    obj = provider->provider->getObject(aUuid);

    /*
     * No need to addRef the object, the provider did it for us.
     */
    if(obj)
      return obj;

    provider = provider->next;
  }

  return 0;
}

