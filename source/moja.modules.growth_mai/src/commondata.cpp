#include "moja/modules/growth_mai/commondata.h"

namespace moja::modules::growth_mai {

ObjectHolder& ObjectHolder::Instance() {
   static ObjectHolder instance;
   return instance;
}
}  // namespace moja::modules::growth_mai
