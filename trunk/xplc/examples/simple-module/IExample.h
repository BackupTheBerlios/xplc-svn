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

#ifndef __EXAMPLE_EXAMPLE_H__
#define __EXAMPLE_EXAMPLE_H__

#include <xplc/IObject.h>

/* Interfaces can only derive from exactly one interface. They must
 * ultimately be derived from IObject. Since we do not derive from
 * anything else useful here, we derive from IObject directly.
 */
class IExample: public IObject {

  /* This is to indicate that this interface has not been released in
   * a final version, and is subject to disappear or be changed. When
   * you use an interface marked in this manner, you have to indicate
   * your acceptance of this unstable condition by defining the
   * UNSTABLE pre-processor symbol (see the Makefile).
   *
   * Once this marker is removed, an interface cannot be changed ever
   * again, neither in syntax (adding/removing methods) or in
   * semantics (changing the meaning of methods).
   *
   * You are allowed to change the name of the interface, if you want,
   * because the real identifier of the interface is the IID (defined
   * at the bottom). For example, you might create a new version of
   * the interface someday and rename this one to IExampleOld.
   *
   * This is how you can have progress in XPLC: instead of changing
   * existing interfaces, you create new ones. A new version of
   * IExample could derive from IExampleOld, if you only wanted to add
   * some methods, thus making it easy to stay compatible (any code
   * that wanted an IExampleOld will work with the new IExample).
   */
  UNSTABLE_INTERFACE

public:
  /* Here are some of the most important rules for an XPLC interface:
   *
   *  - It can only have public members.
   *  - Non-method members are not allowed (you cannot have variables).
   *  - All methods must be pure virtual.
   */

  virtual void sayHello() = 0;
};

/* These numbers are obtained using "uuidgen" or "guidgen.exe". The
 * "uuid2cdef.pl" script can be used to fix the formatting of the
 * "uuidgen" program.
 *
 * This is the ultimate identifier for this interface. Changing either
 * the syntax or the semantics of an interface without changing this
 * identifier would be Bad.
 */
DEFINE_IID(IExample, {0x86c3a2d0, 0xe19b, 0x49d0,
  {0xb2, 0x84, 0x67, 0xc1, 0x11, 0x4a, 0x9d, 0x79}});

#endif /* __EXAMPLE_EXAMPLE_H__ */
