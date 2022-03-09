#pragma once
#include "moja/modules/growth_mai/disturbanceevents.h"

#include <moja/flint/iflintdata.h>

#include <moja/dynamic.h>

namespace moja::modules::growth_mai {

class ForestType;

std::shared_ptr<flint::IFlintData> createEventsFactory(const std::string& event_type_str, int id,
                                                       const std::string& name, const DynamicObject& other);

class PlantEvent final : public DisturbanceEventBase {
  public:
   PlantEvent(int id, const std::string& name) : DisturbanceEventBase(id, "growth_mai.PlantEvent", name) {}
   virtual ~PlantEvent() = default;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;
   DynamicObject exportObject() const override;
   void simulate(DisturbanceEventHandler& event_handler) const override;

   bool is_clearing() const override { return false; }
   std::shared_ptr<ForestType> forest_type;
   int forest_type_id;
};

class ClearEvent final : public DisturbanceEventBase {
  public:
   ClearEvent(int id, const std::string& name) : DisturbanceEventBase(id, "growth_mai.ClearEvent", name) {}
   virtual ~ClearEvent() = default;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;
   DynamicObject exportObject() const override;
   void simulate(DisturbanceEventHandler& event_handler) const override;

   bool is_clearing() const override;
};

}  // namespace moja::modules::growth_mai
