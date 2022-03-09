SET PATH=C:\Development\moja-global\moja.colombia\source\build\bin\Debug;C:\Development\moja-global\FLINT\Source\build\bin\Debug;C:\Development\moja-global\vcpkg\installed\x64-windows\debug\bin;%PATH%
SET GDAL_DATA=C:\Development\moja-global\vcpkg\installed\x64-windows\share\gdal
SET LOCAL_LIBS=C:\Development\moja-global\moja.colombia\source\build\bin\Debug\
SET MOJA_LIBS=C:\Development\moja-global\FLINT\Source\build\bin\Debug\

moja.cli --config growth_mai.json --config growth_mai_test_block.json --config Debug/libs.win.json --config_provider growth_mai_provider.json