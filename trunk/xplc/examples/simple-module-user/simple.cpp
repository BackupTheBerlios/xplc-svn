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

