#include "moja/modules/growth_mai/buildlandunitmodule.h"

#include "moja/modules/growth_mai/forestevents.h"
#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/eventqueue.h>
#include <moja/flint/flintexceptions.h>
#include <moja/flint/itiming.h>
#include <moja/flint/ivariable.h>
#include <moja/flint/spatiallocationinfo.h>

#include <moja/notificationcenter.h>
#include <moja/signals.h>

#include <fmt/format.h>

namespace moja::modules::growth_mai {

void BuildLandUnitModule::subscribe(NotificationCenter& notificationCenter) {
   notificationCenter.subscribe(signals::LocalDomainInit, &BuildLandUnitModule::onLocalDomainInit, *this);
   notificationCenter.subscribe(signals::PreTimingSequence, &BuildLandUnitModule::onPreTimingSequence, *this);
}

void BuildLandUnitModule::configure(const DynamicObject& config) {}

void BuildLandUnitModule::onLocalDomainInit() {
   try {
      department_id_var_ = _landUnitData->getVariable("department");
      forest_types_var_ = _landUnitData->getVariable("forest_types");
      forest_type_id_var_ = _landUnitData->getVariable("forest_type_id");
      forest_establishment_var_ = _landUnitData->getVariable("forest_establishment");
      spatial_location_info_var_ = _landUnitData->getVariable("spatialLocationInfo");
      land_unit_build_success_var_ = _landUnitData->getVariable("landUnitBuildSuccess");
      forest_exists_var_ = _landUnitData->getVariable("forest_exists");

      simulation_unit_data_ = std::static_pointer_cast<SimulationUnitData>(
          _landUnitData->getVariable("simulationUnitData")->value().extract<std::shared_ptr<flint::IFlintData>>());
      simulation_unit_data_->local_domain_id = _landUnitData->getVariable("localDomainId")->value();
   } catch (flint::VariableNotFoundException& exc) {
      const auto variable_name = *(boost::get_error_info<flint::VariableName>(exc));
      const auto str = fmt::format("Variable not found: {}", variable_name);
      BOOST_THROW_EXCEPTION(flint::LocalDomainError()
                            << flint::Details(str) << flint::LibraryName("moja.modules.growth_mai")
                            << flint::ModuleName(BOOST_CURRENT_FUNCTION) << flint::ErrorCode(1));
   } catch (...) {
      if (_landUnitData->hasVariable("spatialLocationInfo")) {
         auto spatial_location_info = std::static_pointer_cast<flint::SpatialLocationInfo>(
             _landUnitData->getVariable("spatialLocationInfo")->value().extract<std::shared_ptr<flint::IFlintData>>());
         spatial_location_info->_library = "moja.modules.growth_mai";
         // spatial_location_info->_module = BOOST_CURRENT_FUNCTION;
         spatial_location_info->_errorCode = 1;
      }
      throw;
   }
}

void BuildLandUnitModule::onPreTimingSequence() {
   try {
      if (department_id_var_->value().isEmpty() || forest_type_id_var_->value().isEmpty()) {
         land_unit_build_success_var_->set_value(false);
         return;
      }

      const auto forest_establishment = forest_establishment_var_->value();
      const int establishment_year = forest_establishment["establishment_year"];
      const int forest_type_id = forest_establishment["forest_type_id"];

      const auto forest_types = std::static_pointer_cast<ForestTypeList>(
          forest_types_var_->value().extract<std::shared_ptr<flint::IFlintData>>());

      const auto forest_type = forest_types->find(forest_type_id);

      const auto* timing = _landUnitData->timing();

      auto event_queue = std::static_pointer_cast<flint::EventQueue>(
          _landUnitData->getVariable("eventqueue")->value<std::shared_ptr<flint::IFlintData>>());

      event_queue->clear();
      if (forest_exists_var_->value() == true) {
         int i = 42;
      }

      auto event_date = DateTime(establishment_year, 1, 1, 12, 0, 0);
      int event_id = 0;
      while (event_date >= timing->startDate() && event_date < timing->endDate()) {
         auto plant_ev = std::make_shared<PlantEvent>(event_id, "Plant " + forest_type->name);
         plant_ev->forest_type = forest_type;
         plant_ev->forest_type_id = forest_type_id;
         event_queue->emplace_back(flint::EventQueueItem{event_date, plant_ev});
         event_date.addYears(forest_type->rotation_length);
         if (event_date >= timing->startDate() && event_date < timing->endDate()) {
            auto clear_ev = std::make_shared<ClearEvent>(event_id, "Clear " + forest_type->name);
            event_queue->emplace_back(flint::EventQueueItem{event_date, clear_ev});
         }
         event_date.addYears(1);
      }

      land_unit_build_success_var_->set_value(true);
   } catch (...) {
      if (_landUnitData->hasVariable("spatialLocationInfo")) {
         auto spatial_location_info = std::static_pointer_cast<flint::SpatialLocationInfo>(
             _landUnitData->getVariable("spatialLocationInfo")->value().extract<std::shared_ptr<flint::IFlintData>>());
         spatial_location_info->_library = "moja.modules.growth_mai";
         spatial_location_info->_module = BOOST_CURRENT_FUNCTION;
         spatial_location_info->_errorCode = 1;
      }
      throw;
   }
}

}  // namespace moja::modules::growth_mai
