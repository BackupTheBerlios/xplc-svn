/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * This file is example code for XPLC (http://xplc.sourceforge.net/),
 * and is put into the public domain.
 */

#include <stdio.h>
#include <xplc/xplc.h>
#include "IExample.h"
#include "simple.h"

XPLC xplc;

int main() {
  xplc.addModuleDirectory("../simple-module");

  xplc_ptr<IExample> example(xplc.get<IExample>(SimpleComponent_CID));

  if (example) {
    example->sayHello();
  } else {
    printf("SimpleComponent not found\n");
  }

  return 0;
}

