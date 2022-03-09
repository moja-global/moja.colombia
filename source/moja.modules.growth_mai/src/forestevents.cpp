#include "moja/modules/growth_mai/forestevents.h"

#include "moja/modules/growth_mai/disturbanceevents.h"
#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/ilandunitcontroller.h>
#include <moja/flint/ivariable.h>

namespace moja::modules::growth_mai {

// Flint Data Factory
std::shared_ptr<flint::IFlintData> createEventsFactory(const std::string& event_type_str, int id,
                                                       const std::string& name, const DynamicObject& other) {
   if (event_type_str == "growth_mai.PlantEvent") return std::make_shared<PlantEvent>(id, name);
   if (event_type_str == "growth_mai.ClearEvent") return std::make_shared<ClearEvent>(id, name);
   return nullptr;
}

void PlantEvent::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                           datarepository::DataRepository& dataRepository) {
   DisturbanceEventBase::configure(config, landUnitController, dataRepository);
   forest_type_id = config["forest_type_id"];
   const auto forest_types_var = landUnitController.getVariable("forest_types");
   const auto forest_types = std::static_pointer_cast<const ForestTypeList>(
       forest_types_var->value().extract<std::shared_ptr<flint::IFlintData>>());

   forest_type = forest_types->find(forest_type_id);
}

DynamicObject PlantEvent::exportObject() const {
   auto object = DisturbanceEventBase::exportObject();
   object["forest_type_id"] = forest_type_id;
   return object;
}

void PlantEvent::simulate(DisturbanceEventHandler& event_handler) const { event_handler.simulate(*this); }

void ClearEvent::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                           datarepository::DataRepository& dataRepository) {
   DisturbanceEventBase::configure(config, landUnitController, dataRepository);
}

DynamicObject ClearEvent::exportObject() const {
   auto object = DisturbanceEventBase::exportObject();
   return object;
}

void ClearEvent::simulate(DisturbanceEventHandler& event_handler) const { event_handler.simulate(*this); }

bool ClearEvent::is_clearing() const { return true; }

}  // namespace moja::modules::growth_mai
