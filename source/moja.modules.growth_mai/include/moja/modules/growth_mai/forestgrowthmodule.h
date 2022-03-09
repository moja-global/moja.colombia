#pragma once
#include "moja/modules/growth_mai/_modules.growth_mai_exports.h"

#include <moja/flint/modulebase.h>

namespace moja::flint {
class IPool;
class IVariable;
}  // namespace moja::flint

namespace moja::modules::growth_mai {

class ForestType;

class GROWTH_MAI_API ForestGrowthModule : public moja::flint::ModuleBase {
  public:
   ForestGrowthModule() = default;

   virtual ~ForestGrowthModule() = default;

   void configure(const DynamicObject& config) override;
   void subscribe(NotificationCenter& notificationCenter) override;

   void onLocalDomainInit() override;
   void onTimingInit() override;
   void onTimingStep() override;

   static double calculate_above_ground_biomass(double age, double max, double k, double m);

  private:
   struct partitioned_biomass {
      double above_ground = 0.0, below_ground = 0.0;
   };
   static partitioned_biomass calculate_forest_biomass(const ForestType* forest_type, double age);

   // Growth
   const flint::IPool* atmosphere_ = nullptr;
   const flint::IPool* initial_values_ = nullptr;
   const flint::IPool* above_ground_ = nullptr;
   const flint::IPool* below_ground_ = nullptr;

   flint::IVariable* forest_exists_ = nullptr;
   const flint::IVariable* forest_ = nullptr;
};

}  // namespace moja::modules::growth_mai
