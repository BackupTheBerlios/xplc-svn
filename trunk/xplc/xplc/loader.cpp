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

#ifndef WIN32
#include <xplc/autoconf.h>
#ifdef HAVE_DLFCN_H
#include <dlfcn.h>
#endif
#endif

#ifdef WIN32
#include <windows.h>
#endif

#include "loader.h"

#ifdef HAVE_DLFCN_H
const char* loaderOpen(const char* aFilename,
		       void** aHandle) {
  const char* rv = 0;

  /* clear out dl error */
  static_cast<void>(dlerror());
  
  *aHandle = dlopen(aFilename, RTLD_NOW);

  if(!*aHandle)
    rv = dlerror();

  return rv;
}

const char* loaderSymbol(void* aHandle,
			 const char* aSymbol,
			 void** aPointer) {
  /* clear out dl error */
  static_cast<void>(dlerror());

  *aPointer = dlsym(aHandle, aSymbol);

  return dlerror();
}

bool loaderClose(void* aHandle) {
  return dlclose(aHandle) == 0;
}

#endif

#ifdef WIN32

const char* getErrorMessage() {
  static char error[1024];
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, GetLastError(), 0, error, sizeof(error), 0);
  return error;
}

const char* loaderOpen(const char* aFilename,
		       void** aHandle) {
  const char* rv = 0;

  UINT oldErrorMode = SetErrorMode(0);
  SetErrorMode(oldErrorMode | SEM_FAILCRITICALERRORS);
  *aHandle = LoadLibrary(aFilename);
  SetErrorMode(oldErrorMode);

  if(!*aHandle)
    rv = getErrorMessage();

  return rv;
}

const char* loaderSymbol(void* aHandle,
			 const char* aSymbol,
			 void** aPointer) {
  const char* rv = 0;

  *aPointer = GetProcAddress(static_cast<HMODULE>(aHandle), aSymbol);

  if(!aPointer)
    rv = getErrorMessage();

  return rv;
}

bool loaderClose(void* aHandle) {
  return FreeLibrary(static_cast<HMODULE>(aHandle)) != 0;
}

#endif
