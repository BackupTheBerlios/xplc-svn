#include <xplc/utils.h>
#include "catmgr.h"

UUID_MAP_BEGIN(CategoryManager)
  UUID_MAP_ENTRY(IObject)
  UUID_MAP_ENTRY(IServiceHandler)
  UUID_MAP_ENTRY(ICategoryManager)
  UUID_MAP_END

CategoryManager* CategoryManager::create() {
  return new GenericComponent<CategoryManager>;
}

IObject* CategoryManager::getObject(const UUID&) {
  return NULL;
}

void CategoryManager::registerComponent(const UUID&, const UUID&) {
}

