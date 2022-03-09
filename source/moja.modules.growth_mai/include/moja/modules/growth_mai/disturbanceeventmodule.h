#pragma once

#include "moja/modules/growth_mai/_modules.growth_mai_exports.h"
#include "moja/modules/growth_mai/disturbanceevents.h"

#include <moja/flint/modulebase.h>

namespace moja::flint {
class IPool;
class IVariable;
}  // namespace moja::flint

namespace moja::modules::growth_mai {
class ForestFireEvent;

class GROWTH_MAI_API DisturbanceEventModule : public flint::ModuleBase, DisturbanceEventHandler {
  public:
   DisturbanceEventModule() = default;
   virtual ~DisturbanceEventModule() = default;

   void configure(const DynamicObject& config) override;
   void subscribe(NotificationCenter& notificationCenter) override;

   void onTimingInit() override;

   void disturbanceEventHandler(const flint::EventQueueItem* event);  // special handler for events

  private:
   void simulate(const PlantEvent& plant) override;
   void simulate(const ClearEvent& thin) override;

   const flint::IPool* atmosphere_;

   const flint::IPool* above_ground_ = nullptr;
   const flint::IPool* below_ground_ = nullptr;

   flint::IVariable* forest_exists_;
   flint::IVariable* forest_var_;
};

}  // namespace moja::modules::growth_mai
