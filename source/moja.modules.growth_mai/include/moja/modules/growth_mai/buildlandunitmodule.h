#pragma once

#include "moja/modules/growth_mai/simulationunitdata.h"
#include "moja/modules/growth_mai/systemsettings.h"

#include <moja/flint/modulebase.h>

namespace moja::flint {
class EventQueue;
}  // namespace moja::flint

namespace moja::modules::growth_mai {

class GROWTH_MAI_API BuildLandUnitModule : public flint::ModuleBase {
  public:
   explicit BuildLandUnitModule(SystemSettings& system_settings) : system_settings_(system_settings) {}

   ~BuildLandUnitModule() override = default;

   void configure(const DynamicObject&) override;
   void subscribe(NotificationCenter& notificationCenter) override;

   // Notification handlers
   void onLocalDomainInit() override;
   void onPreTimingSequence() override;

  private:
   // -- Shared Data
   SystemSettings& system_settings_;

   // Variable handles
   const flint::IVariable* department_id_var_{};
   const flint::IVariable* forest_establishment_var_{};
   const flint::IVariable* forest_type_id_var_{};
   const flint::IVariable* forest_types_var_{};
   const flint::IVariable* spatial_location_info_var_{};

   flint::IVariable* land_unit_build_success_var_{};
   flint::IVariable* forest_exists_var_{};

   // FlintData
   std::shared_ptr<SimulationUnitData> simulation_unit_data_;
};

}  // namespace moja::modules::growth_mai
