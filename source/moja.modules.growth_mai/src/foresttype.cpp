#include "moja/modules/growth_mai/foresttype.h"

#include <moja/flint/ilandunitcontroller.h>
#include <moja/flint/ivariable.h>

#include <moja/logging.h>

namespace moja::modules::growth_mai {

void ForestType::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                           datarepository::DataRepository& dataRepository) {
   if (config.empty()) return;
   id = config["id"];
   name = config["name"].extract<const std::string>();
   density = config["density"];
   root_to_shoot = config["root_to_shoot"];
   carbon_frac = config["carbon_frac"];
   rotation_length = config["rotation_length"];
   mai = config["mai"];
   expansion_factor = config["expansion_factor"];
}

DynamicObject ForestType::exportObject() const {
   DynamicObject object;

   object["id"] = id;
   object["name"] = name;

   object["density"] = density;
   object["root_to_shoot"] = root_to_shoot;
   object["carbon_frac"] = carbon_frac;
   object["rotation_length"] = rotation_length;
   object["mai"] = mai;
   object["expansion_factor"] = expansion_factor;

   return object;
}

double Forest::stem_mass() const {
   if (forest_type == nullptr) return 0.0;
   return age * forest_type->mai * forest_type->density;
}

double Forest::above_ground() const {
   if (forest_type == nullptr) return 0.0;
   return stem_mass() * forest_type->expansion_factor;
}

double Forest::below_ground() const {
   if (forest_type == nullptr) return 0.0;
   return above_ground() * forest_type->root_to_shoot;
}

Forest::carbon Forest::grow(double step_len_in_yrs) {
   carbon carbon_mass = {0.0, 0.0};

   if (step_len_in_yrs > 0.0) {
      const auto starting_above_ground = above_ground();
      const auto starting_below_ground = below_ground();
      age += step_len_in_yrs;
      const auto ending_above_ground = above_ground();
      const auto ending_below_ground = below_ground();
      carbon_mass.above_ground = (ending_above_ground - starting_above_ground) * forest_type->carbon_frac;
      carbon_mass.below_ground = (ending_below_ground - starting_below_ground) * forest_type->carbon_frac;
   }
   return carbon_mass;
}

void Forest::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                       datarepository::DataRepository& dataRepository) {
   if (config.empty()) return;

   const auto* forest_types_var = landUnitController.getVariable("forest_types");
   const auto forest_types = std::static_pointer_cast<const ForestTypeList>(
       forest_types_var->value().extract<std::shared_ptr<flint::IFlintData>>());

   forest_type = forest_types->find(config["forest_type_id"]);

   auto forest_type_id = config["forest_type_id"];
   age = config["age"];
}

DynamicObject Forest::exportObject() const {
   DynamicObject object;
   if (forest_type != nullptr) object["forest_type_id"] = forest_type->id;
   object["age"] = age;
   return object;
}

void ForestTypeList::configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                               datarepository::DataRepository& dataRepository) {
   list_.clear();
   if (!config.contains("items")) return;

   if (config["items"].type() == typeid(std::vector<DynamicObject>)) {
      const auto& species_list = config["items"].extract<const std::vector<DynamicObject>>();
      for (const auto& spec : species_list) {
         add_species(spec, landUnitController, dataRepository);
      }
   } else {
      const auto& species_list = config["items"].extract<const DynamicVector>();
      for (const auto& spec_dyn : species_list) {
         const auto& spec = spec_dyn.extract<const DynamicObject>();
         add_species(spec, landUnitController, dataRepository);
      }
   }
}

void ForestTypeList::add_species(const DynamicObject& spec, const flint::ILandUnitController& landUnitController,
                                 datarepository::DataRepository& data_repository) {
   std::shared_ptr<ForestType> tree = nullptr;
   const std::string type = spec["type"];
   if (type == "growth_mai.ForestType") {
      tree = std::make_shared<ForestType>();
   } else {
      throw std::runtime_error("Unknown Forest type");
   }
   tree->configure(spec, landUnitController, data_repository);
   list_.push_back(tree);
}

DynamicObject ForestTypeList::exportObject() const {
   DynamicObject object;
   return object;
}

ForestTypeList::value_type ForestTypeList::find(int id) const {
   const auto tree_species =
       std::find_if(begin(), end(), [&id](std::shared_ptr<const ForestType> item) { return item->id == id; });
   return tree_species == end() ? nullptr : *tree_species;
}
}  // namespace moja::modules::growth_mai
