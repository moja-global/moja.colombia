#include "moja/modules/growth_mai/foresttypestransform.h"

#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/flintexceptions.h>
#include <moja/flint/iflintdata.h>
#include <moja/flint/ivariable.h>

#include <boost/algorithm/string.hpp>
#include <fmt/format.h>

namespace moja::modules::growth_mai {

ForestTypesTransform::ForestTypesTransform()
    : _landUnitController(nullptr), _dataRepository(nullptr), _dataLoaded(false) {}

void ForestTypesTransform::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                                     datarepository::DataRepository& dataRepository) {
   _landUnitController = &landUnitController;
   _dataRepository = &dataRepository;
}

void ForestTypesTransform::controllerChanged(const flint::ILandUnitController& controller) {}

const DynamicVar& ForestTypesTransform::value() const {
   if (!_dataLoaded) {
      // Data to be cached
      const auto var = _landUnitController->getVariable("forest_type_records");
      DynamicObject config;
      auto forest_types = std::make_shared<ForestTypeList>();
      config["items"] = var->value().extract<std::vector<DynamicObject>>();
      forest_types->configure(config, *_landUnitController, *_dataRepository);
      _cached_value = std::static_pointer_cast<flint::IFlintData>(forest_types);
      _dataLoaded = true;
   }
   return _cached_value;
}
}  // namespace moja::modules::growth_mai
