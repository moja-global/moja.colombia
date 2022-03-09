#pragma once

#include "moja/modules/growth_mai/_modules.growth_mai_exports.h"

#include <moja/flint/ilandunitcontroller.h>
#include <moja/flint/itransform.h>

#include <moja/datarepository/iproviderrelationalinterface.h>

namespace moja::modules::growth_mai {

class GROWTH_MAI_API ForestTypesTransform : public flint::ITransform {
  public:
   ForestTypesTransform();
   ForestTypesTransform(const ForestTypesTransform&) = delete;
   ForestTypesTransform& operator=(const ForestTypesTransform&) = delete;

   void configure(DynamicObject config, const flint::ILandUnitController& landUnitController,
                  datarepository::DataRepository& dataRepository) override;

   void controllerChanged(const flint::ILandUnitController& controller) override;
   const DynamicVar& value() const override;

  private:
   DynamicObject _config;
   const flint::ILandUnitController* _landUnitController;
   datarepository::DataRepository* _dataRepository;
   std::shared_ptr<datarepository::IProviderRelationalInterface> _provider;

   mutable DynamicVar _cached_value;
   mutable bool _dataLoaded;
};

}  // namespace moja::modules::growth_mai
