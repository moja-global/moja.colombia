#pragma once

#include "moja/modules/growth_mai/_modules.growth_mai_exports.h"

#include <moja/flint/iflintdata.h>

#include <moja/dynamic.h>

#include <utility>

namespace moja::modules::growth_mai {

class GROWTH_MAI_API ForestType : public flint::IFlintData {
  public:
   ForestType() = default;
   ~ForestType() override = default;
   ForestType(const ForestType&) = delete;
   ForestType& operator=(const ForestType&) = delete;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;

   DynamicObject exportObject() const override;

   int id;
   std::string name;

   double density, root_to_shoot, carbon_frac, mai, expansion_factor;
   int rotation_length;
};

class Forest : public flint::IFlintData {
  public:
   struct carbon {
      double above_ground, below_ground;
   };
   explicit Forest(std::shared_ptr<ForestType> forest_type) : age(0.0), forest_type(std::move(forest_type)) {}
   Forest() = default;
   ~Forest() override = default;
   carbon grow(double step_len_in_yrs);
   Forest(const ForestType&) = delete;
   Forest& operator=(const Forest&) = delete;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;

   DynamicObject exportObject() const override;

   double stem_mass() const;
   double above_ground() const;
   double below_ground() const;

   double age;
   std::shared_ptr<ForestType> forest_type;
};

class GROWTH_MAI_API ForestTypeList : public flint::IFlintData {
  public:
   typedef std::vector<std::shared_ptr<ForestType>>::value_type value_type;
   typedef std::vector<std::shared_ptr<ForestType>>::iterator iterator;
   typedef std::vector<std::shared_ptr<ForestType>>::const_iterator const_iterator;
   typedef std::vector<std::shared_ptr<ForestType>>::size_type size_type;

   ForestTypeList() = default;
   virtual ~ForestTypeList() = default;
   ForestTypeList(const ForestTypeList&) = delete;
   ForestTypeList& operator=(const ForestTypeList&) = delete;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;

   DynamicObject exportObject() const override;

   iterator begin();
   const_iterator begin() const MOJA_NOEXCEPT;
   iterator end() MOJA_NOEXCEPT;
   const_iterator end() const MOJA_NOEXCEPT;
   void clear();
   size_type size() const MOJA_NOEXCEPT;
   template <class... Args>
   void emplace_back(Args&&... args);

   value_type find(int forest_type_id) const;

  private:
   void add_species(const DynamicObject& spec, const flint::ILandUnitController& landUnitController,
                    datarepository::DataRepository& data_repository);
   std::vector<value_type> list_;
};

inline ForestTypeList::iterator ForestTypeList::begin() { return list_.begin(); }

inline ForestTypeList::const_iterator ForestTypeList::begin() const MOJA_NOEXCEPT { return list_.begin(); }

inline ForestTypeList::iterator ForestTypeList::end() MOJA_NOEXCEPT { return list_.end(); }

inline ForestTypeList::const_iterator ForestTypeList::end() const MOJA_NOEXCEPT { return list_.end(); }

inline void ForestTypeList::clear() { list_.clear(); }

inline ForestTypeList::size_type ForestTypeList::size() const MOJA_NOEXCEPT { return list_.size(); }

template <class... Args>
void ForestTypeList::emplace_back(Args&&... args) {
   list_.emplace_back(std::forward<Args>(args)...);
}

}  // namespace moja::modules::growth_mai
