#include "moja/modules/growth_mai/libraryfactory.h"

#include "moja/modules/growth_mai/aggregatorerror.h"
#include "moja/modules/growth_mai/aggregatorlandunit.h"
#include "moja/modules/growth_mai/buildlandunitmodule.h"
#include "moja/modules/growth_mai/commondata.h"
#include "moja/modules/growth_mai/disturbanceeventmodule.h"
#include "moja/modules/growth_mai/forestevents.h"
#include "moja/modules/growth_mai/forestgrowthmodule.h"
#include "moja/modules/growth_mai/foresttype.h"
#include "moja/modules/growth_mai/foresttypestransform.h"
#include "moja/modules/growth_mai/landunitsqlitewriter.h"
#include "moja/modules/growth_mai/runstatistics.h"

#include <moja/flint/imodule.h>
#include <moja/flint/mojalibapi.h>

namespace moja::modules::growth_mai {

extern "C" {
// Flint Data

MOJA_LIB_API int getModuleRegistrations(flint::ModuleRegistration* registrations) {
   auto index = 0;
   registrations[index++] = flint::ModuleRegistration{
       "AggregatorError",
       []() -> flint::IModule* { return new AggregatorError(ObjectHolder::Instance().systemSettings); }};
   registrations[index++] = flint::ModuleRegistration{
       "AggregatorLandUnit", []() -> flint::IModule* { return new AggregatorLandUnit(ObjectHolder::Instance()); }};
   registrations[index++] = flint::ModuleRegistration{
       "LandUnitSQLiteWriter", []() -> flint::IModule* { return new LandUnitSQLiteWriter(ObjectHolder::Instance()); }};
   registrations[index++] =
       flint::ModuleRegistration{"ForestGrowthModule", []() -> flint::IModule* { return new ForestGrowthModule(); }};
   registrations[index++] = flint::ModuleRegistration{"DisturbanceEventModule",
                                                      []() -> flint::IModule* { return new DisturbanceEventModule(); }};
   registrations[index++] = flint::ModuleRegistration{
       "BuildLandUnitModule",
       []() -> flint::IModule* { return new BuildLandUnitModule(ObjectHolder::Instance().systemSettings); }};

   return index;
}

MOJA_LIB_API int getTransformRegistrations(flint::TransformRegistration* registrations) {
   auto index = 0;
   registrations[index++] = flint::TransformRegistration{
       "ForestTypesTransform", []() -> flint::ITransform* { return new ForestTypesTransform(); }};
   return index;
}

MOJA_LIB_API int getFlintDataRegistrations(flint::FlintDataRegistration* registrations) {
   auto index = 0;
   registrations[index++] =
       flint::FlintDataRegistration{"ForestType", []() -> flint::IFlintData* { return new ForestType(); }};
   registrations[index++] =
       flint::FlintDataRegistration{"ForestTypeList", []() -> flint::IFlintData* { return new ForestTypeList(); }};
   registrations[index++] = flint::FlintDataRegistration{
       "SimulationUnitData", []() -> flint::IFlintData* { return new SimulationUnitData(); }};
   registrations[index++] =
       flint::FlintDataRegistration{"RunStatistics", []() -> flint::IFlintData* { return new RunStatistics(); }};

   return index;
}

MOJA_LIB_API int getFlintDataFactoryRegistrations(flint::FlintDataFactoryRegistration* registrations) {
   auto index = 0;
   registrations[index++] = flint::FlintDataFactoryRegistration{"internal.flint", "EventQueue", &createEventsFactory};
   return index;
}
}

}  // namespace moja::modules::growth_mai
