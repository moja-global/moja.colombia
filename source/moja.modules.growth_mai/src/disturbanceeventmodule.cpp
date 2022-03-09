#include "moja/modules/growth_mai/disturbanceeventmodule.h"

#include "moja/modules/growth_mai/disturbanceevents.h"
#include "moja/modules/growth_mai/forestevents.h"
#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/eventqueue.h>
#include <moja/flint/flintexceptions.h>
#include <moja/flint/iflintdata.h>
#include <moja/flint/ioperation.h>
#include <moja/flint/ivariable.h>

#include <moja/notificationcenter.h>
#include <moja/signals.h>

namespace moja::modules::growth_mai {

void DisturbanceEventModule::configure(const DynamicObject& config) {}

void DisturbanceEventModule::subscribe(NotificationCenter& notificationCenter) {
   notificationCenter.subscribe(signals::TimingInit, &DisturbanceEventModule::onTimingInit, *this);
   notificationCenter.subscribe(signals::DisturbanceEvent, &DisturbanceEventModule::disturbanceEventHandler, *this);
}

void DisturbanceEventModule::onTimingInit() {
   atmosphere_ = _landUnitData->getPool("atmosphereCM");
   above_ground_ = _landUnitData->getPool("aboveGroundCM");
   below_ground_ = _landUnitData->getPool("belowGroundCM");

   forest_exists_ = _landUnitData->getVariable("forest_exists");
   forest_var_ = _landUnitData->getVariable("forest");
}

template <typename T>
std::shared_ptr<T> extract_flint_data(flint::IVariable* var) {
   return std::dynamic_pointer_cast<T>(var->value().extract<std::shared_ptr<flint::IFlintData>>());
}

void DisturbanceEventModule::simulate(const PlantEvent& plant) {
   const bool forest_exists = forest_exists_->value();

   if (forest_exists) {
      BOOST_THROW_EXCEPTION(flint::SimulationError()
                            << flint::Details("Planting occured when forest present.")
                            << flint::LibraryName("moja.modules.growth_mai")
                            << flint::ModuleName(BOOST_CURRENT_FUNCTION) << flint::ErrorCode(1));
   }
   auto forest_types = extract_flint_data<ForestTypeList>(_landUnitData->getVariable("forest_types"));

   auto forest_type = forest_types->find(plant.forest_type_id);

   auto forest = std::make_shared<Forest>(forest_type);
   forest_var_->set_value(std::static_pointer_cast<flint::IFlintData>(forest));
   forest_exists_->set_value(true);
}

void DisturbanceEventModule::simulate(const ClearEvent& thin) {
   const bool forest_exists = forest_exists_->value();

   if (!forest_exists) {
      BOOST_THROW_EXCEPTION(flint::SimulationError()
                            << flint::Details("Clearing occurred when no forest present.")
                            << flint::LibraryName("moja.modules.growth_mai")
                            << flint::ModuleName(BOOST_CURRENT_FUNCTION) << flint::ErrorCode(1));
   }

   if (thin.is_clearing()) {
      forest_exists_->set_value(false);  //	Clearing Thin
      forest_var_->set_value({});
   }

   auto operation = _landUnitData->createProportionalOperation();
   operation->addTransfer(above_ground_, atmosphere_, 1.0)->addTransfer(below_ground_, atmosphere_, 1.0);

   _landUnitData->submitOperation(operation);
}

void DisturbanceEventModule::disturbanceEventHandler(const flint::EventQueueItem* event) {
   auto disturbance_event = std::static_pointer_cast<const DisturbanceEventBase>(event->_event);
   disturbance_event->simulate(*this);
}

}  // namespace moja::modules::growth_mai
