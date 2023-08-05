cmake_minimum_required(VERSION 3.3...3.8)
# proj
set(vProjName "AnyLeNum")
set(vProjNameLib "l${vProjName}")
set(vProjNameDll "${vProjNameLib}Shared")
set(vProjNameSll "${vProjNameLib}Static")
set(vProjNameExe "e${vProjName}")
set(vProjNameDef "d${vProjName}")
set(vProjVnumMaj 0)
set(vProjVnumMin 0)
set(vProjVnum "${vProjVnumMaj}.${vProjVnumMin}")
set(vProjDesc "Any Length Number")
project(${vProjName} VERSION ${vProjVnum} DESCRIPTION ${vProjDesc})
# osys
mark_as_advanced(FORCE CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(FORCE CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(FORCE CMAKE_OSX_SYSROOT)
# lang
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# tool
set(vToolGnuccFlag "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(vToolClangFlag "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang>")
set(vToolMsvccFlag "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
# file
set(vFileDirMainRoot "${PROJECT_SOURCE_DIR}/..")
set(vFileDirMainCode "${vFileDirMainRoot}/code")
set(vFileSetMainCode "${vFileDirMainCode}/${vProjName}.cpp")
set(vFileDirMainHead "${vFileDirMainRoot}/code")
set(vFileSetMainHead "${vFileDirMainHead}/${vProjName}.hpp")
set(vFileDirMainBins "${PROJECT_BINARY_DIR}")
set(vFileSetMainBins "${vFileDirMainBins}/${vProjNameExe}")
set(vFileDirMainData "${vFileDirMainRoot}/data")
set(vFileDirDestRoot "$ENV{HOME}$ENV{UserProfile}/.local")
set(vFileDirDestHead "${vFileDirDestRoot}/include")
set(CMAKE_PREFIX_PATH "${vFileDirDestRoot}" CACHE PATH "destination prefix" FORCE)
set(CMAKE_INSTALL_PREFIX "" CACHE PATH "install prefix" FORCE)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# lib
option(oMakeLib "make project library" TRUE)
if(oMakeLib)
  add_library(${vProjNameLib} INTERFACE)
  target_compile_definitions(${vProjNameLib} INTERFACE ${vProjNameDef}MakeLib)
  target_compile_definitions(${vProjNameLib} INTERFACE
    ${vProjNameDef}ProjName="${vProjName}"
    ${vProjNameDef}ProjVnum="${vProjVnumWhole}"
    ${vProjNameDef}FileRoot="${vFileDirMainRoot}"
    ${vProjNameDef}FileData="${vFileDirMainData}"
    "$<${vToolGnuccFlag}:${vProjNameDef}ToolGnuccFlag>"
    "$<${vToolClangFlag}:${vProjNameDef}ToolClangFlag>"
    "$<${vToolMsvccFlag}:${vProjNameDef}ToolMsvccFlag>"
    ) # target_compile_definitions
  target_compile_options(${vProjNameLib} INTERFACE
    "$<${vToolGnuccFlag}:>"
    "$<${vToolClangFlag}:>"
    "$<${vToolMsvccFlag}:>"
    ) # target_compile_options
  target_include_directories(${vProjNameLib} INTERFACE
    "$<BUILD_INTERFACE:${vFileDirMainCode}>;"
    "$<INSTALL_INTERFACE:${vFileDirDestHead}>;"
    ) # target_include_directories
  find_package(fmt 10.0.0 REQUIRED)
  target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt)
  mark_as_advanced(FORCE fmt_DIR)
  # dll
  option(oMakeDll "make project shared library" TRUE)
  if(oMakeDll)
    add_library(${vProjNameDll} SHARED ${vFileSetMainCode})
    target_compile_definitions(${vProjNameDll} PRIVATE ${vProjNameDef}MakeDll)
    target_link_libraries(${vProjNameDll} PRIVATE ${vProjNameLib})
  endif(oMakeDll)
  # sll
  option(oMakeSll "make project static library" TRUE)
  if(oMakeSll)
    add_library(${vProjNameSll} STATIC ${vFileSetMainCode})
    target_compile_definitions(${vProjNameSll} PRIVATE ${vProjNameDef}MakeSll)
    target_link_libraries(${vProjNameSll} PRIVATE ${vProjNameLib})
  endif(oMakeSll)
  # exe
  option(oMakeExe "make project executable" TRUE)
  if(oMakeExe)
    add_executable(${vProjNameExe} ${vFileSetMainCode})
    target_compile_definitions(${vProjNameExe} PRIVATE ${vProjNameDef}MakeExe)
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    find_package(pTermAPar 4.2.1 REQUIRED)
    target_link_libraries(${vProjNameExe} PRIVATE pTermAPar::lTermAPar)
    mark_as_advanced(FORCE pTermAPar_DIR)
    # test
    include(CTest)
    enable_testing()
    #
    set(vTestName "tHello")
    add_test(NAME ${vTestName}
      COMMAND ${vFileSetMainBins} ${vTestName}
      ) # add_test
    set_tests_properties(${vTestName} PROPERTIES
      PASS_REGULAR_EXPRESSION  "HelloWorld"
      ) # set_tests_properties
    #
  endif(oMakeExe)
endif(oMakeLib)
