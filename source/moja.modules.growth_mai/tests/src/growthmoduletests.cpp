#include <moja/flint/configuration/configuration.h>
#include <moja/flint/configuration/library.h>
#include <moja/flint/configuration/localdomain.h>

#include <moja/flint/localdomaincontrollerbase.h>

#include <moja/datetime.h>

#include <boost/test/unit_test.hpp>

#include <random>

BOOST_AUTO_TEST_SUITE(GROWTHMAIModuleTests);

BOOST_AUTO_TEST_CASE(modules_growth_mai_ForestType_Growth) {
   namespace flint = moja::flint;
   using namespace flint::configuration;

   Configuration config(moja::DateTime(2000, 1, 1), moja::DateTime(2100, 12, 31));

   config.addLibrary("moja.modules.growth_mai", LibraryType::External);

   config.setLocalDomain(LocalDomainType::Point, LocalDomainIterationType::NotAnIteration, true, 1, "internal.flint",
                         "CalendarAndEventFlintDataSequencer", "simulateLandUnit", "landUnitBuildSuccess",
                         moja::DynamicObject());

   config.addModule("internal.flint", "CalendarAndEventFlintDataSequencer", 1, false);
   config.addModule("internal.flint", "TransactionManagerEndOfStepModule", 2, false);
   config.addModule("moja.modules.growth_mai", "ForestGrowthModule", 3, false);
   config.addModule("moja.modules.growth_mai", "DisturbanceEventModule", 5, false);
   config.addModule("internal.flint", "AggregatorStockStep", 6, false);
   config.addModule(
       "internal.flint", "OutputerStream", 7, false,
       moja::DynamicObject({{"output_filename", std::string("Growth_Stock.txt")}, {"output_to_screen", false}}));
   config.addModule(
       "internal.flint", "OutputerStreamFlux", 8, false,
       moja::DynamicObject({{"output_filename", std::string("Growth_Fluxes.txt")}, {"output_to_screen", false}}));

   int poolOrder = 0;

   for (auto pool : {"initialValues", "atmosphereCM", "aboveGroundCM", "belowGroundCM"}) {
      std::string desc(pool);
      desc += " description";
      std::string unit("units for ");
      unit += pool;
      config.addPool(pool, desc, unit, 1.0, poolOrder++);
   }

   config.addVariable("simulateLandUnit", true);
   config.addVariable("landUnitBuildSuccess", true);

   config.addVariable("forestExists", true);
   config.addVariable("forest", 0.0);

   config.addFlintDataVariable("forestType", "moja.modules.growth_mai", "ForestType",
                               moja::DynamicObject({{"id", 3}, {"name", "Acacia mangium"},
                                                    {"density", 0.55},
                                                    {"root_to_shoot", 0.24},
                                                    {"carbon_frac", 0.47},
                                                    {"rotation_length", 15.0},
                                                    {"mai", 18.0},
                                                    {"expansion_factor", 1.5}}));

   config.addFlintDataVariable(
       "eventqueue", "internal.flint", "EventQueue",
       moja::DynamicObject({{"events", moja::DynamicVector({moja::DynamicObject({{"type", "growth_mai.PlantEvent"},
                                                                                 {"id", 1},
                                                                                 {"date", moja::DateTime(2050, 1, 1)},
                                                                                 {"name", "Plant Acacia mangium"},
                                                                                 {"forest_type_id", 3}})})}}));

   flint::LocalDomainControllerBase ldc;

   ldc.configure(config);
   ldc._notificationCenter.postNotification(moja::signals::SystemInit);
   ldc.startup();
   ldc.run();
   ldc.shutdown();
   ldc._notificationCenter.postNotification(moja::signals::SystemShutdown);
}

BOOST_AUTO_TEST_SUITE_END();