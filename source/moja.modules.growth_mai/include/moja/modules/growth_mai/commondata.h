#pragma once

#include "moja/modules/growth_mai/record.h"
#include "moja/modules/growth_mai/simulationunitdata.h"
#include "moja/modules/growth_mai/systemsettings.h"

#include <moja/flint/recordaccumulatorwithmutex.h>

namespace moja::modules::growth_mai {

// Export the class when compiling the DLL,
// otherwise import the class when using the DLL.
class GROWTH_MAI_API ObjectHolder {
  public:
   ObjectHolder() {
      date_dimension = std::make_shared<flint::RecordAccumulatorWithMutex2<DateRow, DateRecord>>();
      date_annual_dimension = std::make_shared<flint::RecordAccumulatorWithMutex2<DateAnnualRow, DateAnnualRecord>>();
      pool_info_dimension = std::make_shared<flint::RecordAccumulatorWithMutex2<PoolInfoRow, PoolInfoRecord>>();
      tile_info_dimension = std::make_shared<flint::RecordAccumulatorWithMutex2<TileInfoRow, TileInfoRecord>>();
      location_non_temporal_dimension =
          std::make_shared<flint::RecordAccumulatorWithMutex2<LocationNonTemporalRow, LocationNonTemporalRecord>>();
      location_temporal_dimension =
          std::make_shared<flint::RecordAccumulatorWithMutex2<LocationTemporalRow, LocationTemporalRecord>>();
      classifier_set_dimension =
          std::make_shared<flint::RecordAccumulatorWithMutex2<ClassifierSetRow, ClassifierSetRecord>>();
      classifier_names = std::make_shared<std::vector<std::string>>();
   }

   static ObjectHolder& Instance();

   // Shared Data
   SystemSettings systemSettings;

   // Collections
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<DateRow, DateRecord>> date_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<DateAnnualRow, DateAnnualRecord>> date_annual_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<PoolInfoRow, PoolInfoRecord>> pool_info_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<TileInfoRow, TileInfoRecord>> tile_info_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<LocationNonTemporalRow, LocationNonTemporalRecord>>
       location_non_temporal_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<LocationTemporalRow, LocationTemporalRecord>>
       location_temporal_dimension;
   std::shared_ptr<flint::RecordAccumulatorWithMutex2<ClassifierSetRow, ClassifierSetRecord>> classifier_set_dimension;
   std::shared_ptr<std::vector<std::string>> classifier_names;
};

}  // namespace moja::modules::growth_mai
