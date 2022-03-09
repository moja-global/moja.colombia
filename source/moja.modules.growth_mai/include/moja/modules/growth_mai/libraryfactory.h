#pragma once

#include <moja/flint/librarymanager.h>

namespace moja::modules::growth_mai {

extern "C" MOJA_LIB_API int getModuleRegistrations(moja::flint::ModuleRegistration* registrations);
extern "C" MOJA_LIB_API int getTransformRegistrations(moja::flint::TransformRegistration* registrations);
extern "C" MOJA_LIB_API int getFlintDataRegistrations(moja::flint::FlintDataRegistration* registrations);
extern "C" MOJA_LIB_API int getFlintDataFactoryRegistrations(moja::flint::FlintDataFactoryRegistration* registrations);

}  // namespace moja::modules::growth_mai
