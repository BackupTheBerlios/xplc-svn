/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000-2003, Pierre Phaneuf
 * Copyright (C) 2001, St�phane Lajoie
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

#ifndef __XPLC_UTILS_H__
#define __XPLC_UTILS_H__

/** \file
 *
 * Various utility functions, macros and templates.
 */

#include <stddef.h>
#include <xplc/IWeakRef.h>
#include <xplc/IFactory.h>

/**
 * Utility structure used for the interface map.
 */
struct UUID_Info {
  //@{
  const UUID* iid;
  ptrdiff_t delta;
  //@}
};

/**
 * Start the interface map for "component".
 */
#define UUID_MAP_BEGIN(component) const UUID_Info component::xplc_iobject_uuids[] = {

/**
 * Add an entry to an interface map.
 */
#define UUID_MAP_ENTRY(iface) { &iface##_IID, reinterpret_cast<ptrdiff_t>(static_cast<iface*>(reinterpret_cast<ThisXPLCComponent*>(1))) - 1 },

/**
 * Add an entry to an interface map for an ambiguous interface. The
 * second parameter is the interface that should be used to
 * disambiguate.
 */
#define UUID_MAP_ENTRY_2(iface, iface2) { &iface##_IID, reinterpret_cast<ptrdiff_t>(static_cast<iface2*>(reinterpret_cast<ThisXPLCComponent*>(1))) - 1 },

/**
 * Marks the end of an interface map.
 */
#define UUID_MAP_END { 0, 0 } };

class WeakRef;

/**
 * Helper internal structure. Used for implementing IMPLEMENT_IOBJECT.
 */
struct IObjectImplementationInternal {
  /**
   * Holds the reference count.
   */
  unsigned int refcount;
  /**
   * Pointer to a weak reference object. This object is lazily
   * instantiated, so the pointer is NULL until a weak reference is
   * needed.
   */
  WeakRef* weakref;
  IObjectImplementationInternal(): refcount(1), weakref(0) {
  }
};

/**
 * Helper macro to implement the IObject methods automatically. Put
 * this at the beginning of your class, specifiying the class name as
 * the parameter, and it will automatically implement all the IObject
 * methods. You also need to define an interface map.
 *
 * \sa UUID_MAP_BEGIN, UUID_MAP_ENTRY, UUID_MAP_ENTRY_2, UUID_MAP_END
 */
#define IMPLEMENT_IOBJECT(component) \
private: \
  IObjectImplementationInternal xplc_iobject_internal; \
  static const UUID_Info xplc_iobject_uuids[]; \
  typedef component ThisXPLCComponent; \
public: \
  virtual unsigned int addRef() { \
    return ++xplc_iobject_internal.refcount; \
  } \
  virtual unsigned int release() { \
    if(--xplc_iobject_internal.refcount) \
      return xplc_iobject_internal.refcount; \
    /* protect against re-entering the destructor */ \
    xplc_iobject_internal.refcount = 1; \
    if(xplc_iobject_internal.weakref) \
      xplc_iobject_internal.weakref->object = 0; \
    delete this; \
    return 0; \
  } \
  virtual IObject* getInterface(const UUID& uuid) { \
    return XPLC_getInterface_real(this, uuid, xplc_iobject_uuids); \
  } \
  virtual IWeakRef* getWeakRef() { \
    if(!xplc_iobject_internal.weakref) { \
      xplc_iobject_internal.weakref = new WeakRef; \
      /* FIXME: why not just assign "this"? */ \
      xplc_iobject_internal.weakref->object = this->getInterface(IObject_IID); \
      this->release(); \
    } \
    return xplc_iobject_internal.weakref; \
  }

/**
 * Internal function used by the IMPLEMENT_IOBJECT macro to implement
 * IObject::getInterface().
 */
IObject* XPLC_getInterface_real(void* self, const UUID& uuid,
                                const UUID_Info* uuidlist);

/** \class WeakRef
 *
 * Common implementation of a weak reference.
 */
class WeakRef: public IWeakRef {
  IMPLEMENT_IOBJECT(WeakRef);
public:
  /** The object that the weak reference is pointing at. */
  IObject* object;
  virtual IObject* getObject() {
    if(object)
      object->addRef();

    return object;
  }
};

/**
 * %XPLC equivalent to dynamic_cast.  This templated function is a
 * typesafe way to call the getInterface method of a component and
 * cast it properly.  If the component does not support the interface,
 * a NULL pointer will be returned.
 */
template<class Interface>
Interface* get(IObject* aObj) {
  if(!aObj)
    return 0;

  return static_cast<Interface*>(aObj->getInterface(IID<Interface>::get()));
}

/**
 * A version of get() that releases its parameter.  This templated
 * function is very similar to the "get" one, except that it
 * automatically releases the inbound reference, without regard
 * whether the getInterface actually yielded something.
 */
template<class Interface>
Interface* mutate(IObject* aObj) {
  Interface* rv;

  if(!aObj)
    return 0;

  rv = static_cast<Interface*>(aObj->getInterface(IID<Interface>::get()));

  aObj->release();

  return rv;
}

/**
 * Shorthand to get a factory, create an object and get an interface.
 */
template<class Interface>
Interface* create(const UUID& cid) {
  IServiceManager* servmgr;
  IFactory* factory;
  Interface* rv;

  servmgr = XPLC_getServiceManager();
  if(!servmgr)
    return 0;

  factory = mutate<IFactory>(servmgr->getObject(cid));
  servmgr->release();
  if(!factory)
    return 0;

  rv = mutate<Interface>(factory->createObject());

  factory->release();

  return rv;
}

#endif /* __XPLC_UTILS_H__ */
