#include "moja/modules/growth_mai/forestgrowthmodule.h"

#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/flintexceptions.h>
#include <moja/flint/iflintdata.h>
#include <moja/flint/ioperation.h>
#include <moja/flint/ivariable.h>
#include <moja/flint/operationdatapackage.h>
#include <moja/flint/timing.h>

#include <moja/notificationcenter.h>
#include <moja/signals.h>

namespace moja::modules::growth_mai {

void ForestGrowthModule::configure(const DynamicObject& config) {}

void ForestGrowthModule::subscribe(NotificationCenter& notificationCenter) {
   notificationCenter.subscribe(signals::LocalDomainInit, &ForestGrowthModule::onLocalDomainInit, *this);
   notificationCenter.subscribe(signals::TimingInit, &ForestGrowthModule::onTimingInit, *this);
   notificationCenter.subscribe(signals::TimingStep, &ForestGrowthModule::onTimingStep, *this);
}

ForestGrowthModule::partitioned_biomass ForestGrowthModule::calculate_forest_biomass(const ForestType* forest_type,
                                                                                     double age) {
   partitioned_biomass biomass;
   if (age > 0.0) {
      const auto stem_mass = age * forest_type->mai * forest_type->density;
      biomass.above_ground = stem_mass * forest_type->expansion_factor;
      biomass.below_ground = biomass.above_ground * forest_type->root_to_shoot;
   }
   return biomass;
}

void ForestGrowthModule::onLocalDomainInit() {
   // Pools
   atmosphere_ = _landUnitData->getPool("atmosphereCM");

   above_ground_ = _landUnitData->getPool("aboveGroundCM");
   below_ground_ = _landUnitData->getPool("belowGroundCM");

   initial_values_ = _landUnitData->getPool("initialValues");
}

void ForestGrowthModule::onTimingInit() {
   // Variables
   forest_exists_ = _landUnitData->getVariable("forest_exists");
   forest_ = _landUnitData->getVariable("forest");
}

void ForestGrowthModule::onTimingStep() {
   if (!forest_exists_->value()) return;

   const auto timing = _landUnitData->timing();
   const auto step_len_in_yrs = timing->stepLengthInYears();
   auto forest = std::static_pointer_cast<Forest>(forest_->value().extract<std::shared_ptr<flint::IFlintData>>()).get();

   const auto [above_ground, below_ground] = forest->grow(step_len_in_yrs);

   // Production
   DynamicVar production_data = std::make_shared<flint::OperationDataPackage>(flint::FluxType::NPP);
   auto production = _landUnitData->createStockOperation(production_data);
   production->addTransfer(atmosphere_, above_ground_, above_ground)
       ->addTransfer(atmosphere_, below_ground_, below_ground);
   _landUnitData->submitOperation(production);
}

}  // namespace moja::modules::growth_mai
