#pragma once

#include "moja/modules/growth_mai/_modules.growth_mai_exports.h"
#include "moja/modules/growth_mai/simulationunitdata.h"
#include "moja/modules/growth_mai/systemsettings.h"

#include <moja/flint/modulebase.h>

namespace moja::flint {
class SpatialLocationInfo;
}  // namespace moja::flint

namespace moja::modules::growth_mai {

class GROWTH_MAI_API AggregatorError : public flint::ModuleBase {
  public:
   AggregatorError(SystemSettings& systemSettings) : ModuleBase(), system_settings_(systemSettings) {}

   virtual ~AggregatorError() = default;

   void configure(const DynamicObject& config) override;
   void subscribe(NotificationCenter& notificationCenter) override;
   flint::ModuleTypes moduleType() override { return flint::ModuleTypes::Aggregator; };

   void onLocalDomainInit() override;
   void onLocalDomainProcessingUnitInit() override;
   void onError(std::string msg) override;

  private:
   // -- Shared Data
   SystemSettings& system_settings_;

   // -- flintdata objects data
   std::shared_ptr<SimulationUnitData> simulation_unit_data_;
   std::shared_ptr<const flint::SpatialLocationInfo> spatial_location_info_;
};

}  // namespace moja::modules::growth_mai
