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

#ifndef __XPLC_HANDLERNODE_H__
#define __XPLC_HANDLERNODE_H__

#include <xplc/IServiceHandler.h>

class HandlerNode {
public:
  HandlerNode* next;
  IServiceHandler* handler;
  HandlerNode(IServiceHandler* aHandler,
              HandlerNode* aNext): next(aNext),
                                   handler(aHandler) {
    handler->addRef();
  }

  ~HandlerNode() {
    handler->release();
  }
};

#endif /* __XPLC_HANDLERNODE_H__ */