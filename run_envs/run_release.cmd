SET PATH=C:\Development\moja-global\moja.colombia\source\build\bin\Release;C:\Development\moja-global\FLINT\Source\build\bin\Release;C:\Development\moja-global\vcpkg\installed\x64-windows\bin;%PATH%
SET GDAL_DATA=C:\Development\moja-global\vcpkg\installed\x64-windows\share\gdal
SET LOCAL_LIBS=C:\Development\moja-global\moja.colombia\source\build\bin\Release\
SET MOJA_LIBS=C:\Development\moja-global\FLINT\Source\build\bin\Release\

moja.cli --config growth_mai.json --config growth_mai_all_blocks.json --config Release/libs.win.json --config_provider growth_mai_provider.json