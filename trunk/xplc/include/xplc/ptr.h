/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2002, Pierre Phaneuf
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

#ifndef __XPLC_PTR_H__
#define __XPLC_PTR_H__


#ifndef UNSTABLE
#error "xplc_ptr is experimental!"
#endif

class already_addrefed {
public:
  IObject* ptr;
  already_addrefed(IObject* obj): ptr(obj) {}
};


template<class T> already_addrefed dont_addref(T* obj) {
  return already_addrefed(obj);
}


template<class T> class xplc_ptr {
private:
  T* ptr;

  class Protected: public T {
  private:
    virtual unsigned int addRef() = 0;
    virtual unsigned int release() = 0;
  };

  void set(IObject* obj) {
    if(ptr)
      ptr->release();

    if(!obj) {
      ptr = 0;
      return;
    }

    ptr = static_cast<T*>(obj->getInterface(T::IID));
  }

  T**& operator&();

public:
  xplc_ptr(): ptr(0) {}

  xplc_ptr(const xplc_ptr<T>& obj) {
    set(obj.ptr);
  }

  xplc_ptr(IObject* obj): ptr(0) {
    set(obj);
  }

  ~xplc_ptr() {
    if(ptr)
      ptr->release();
  }

  xplc_ptr<T>& operator=(IObject* obj) {
    set(obj);
    return *this;
  }

  xplc_ptr<T>& operator=(already_addrefed obj) {
    set(obj.ptr);
    if(ptr)
      ptr->release();
    return *this;
  }

  Protected* operator->() {
    assert(ptr);
    return static_cast<Protected*>(ptr);
  }

  T* getRaw() {
    if(ptr)
      ptr->addRef();

    return ptr;
  }

  operator already_addrefed() {
    if(ptr)
      ptr->addRef();

    return already_addrefed(ptr);
  }
};


#endif /* __XPLC_PTR_H__ */
