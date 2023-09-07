cmake_minimum_required(VERSION 3.24)

include(CMakeDependentOption)
include(FetchContent)

# proj

set(vProjName "AnyLeNum")
set(vProjVnum "0.0")
set(vProjDesc "Any Length Number")
set(vProjPath "${CMAKE_SOURCE_DIR}/..")

project(${vProjName} VERSION ${vProjVnum} DESCRIPTION ${vProjDesc})

# lang

enable_language(CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# tool

set(vToolGnuccFlag "$<COMPILE_LANG_AND_ID:CXX,GNU>")
set(vToolClangFlag "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang>")
set(vToolMsvccFlag "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

# code

set(vCodePath "${vProjPath}/code")
set(vCodeList "${vCodePath}/${vProjName}.cpp")

# make

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(vCdefName "d${vProjName}_")
set(vMoptName "o${vProjName}_")

##lib

set(vTlibName "t${vProjName}Lib")

add_library(${vTlibName} INTERFACE)
target_compile_definitions(${vTlibName} INTERFACE ${vCdefName}MakeTlib)
target_compile_definitions(${vTlibName} INTERFACE
  ${vCdefName}ProjName="${vProjName}"
  ${vCdefName}ProjVnum="${vProjVnum}"
  ${vCdefName}ProjPath="${vProjPath}"
  "$<${vToolGnuccFlag}:${vCdefName}ToolGnuccFlag>"
  "$<${vToolClangFlag}:${vCdefName}ToolClangFlag>"
  "$<${vToolMsvccFlag}:${vCdefName}ToolMsvccFlag>"
  ) # target_compile_definitions
target_compile_options(${vTlibName} INTERFACE
  "$<${vToolGnuccFlag}:>"
  "$<${vToolClangFlag}:>"
  "$<${vToolMsvccFlag}:>"
  ) # target_compile_options
target_include_directories(${vTlibName} INTERFACE ${vCodePath})

FetchContent_Declare(fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt.git"
  GIT_TAG "10.0.0"
  OVERRIDE_FIND_PACKAGE)
FetchContent_MakeAvailable(fmt)
find_package(fmt 10.0.0 REQUIRED)
target_link_libraries(${vTlibName} INTERFACE fmt::fmt)

##dll

set(vTdllName "t${vProjName}Dll")

option(${vMoptName}MakeTdll "build shared library target" TRUE)
if(${vMoptName}MakeTdll)

  add_library(${vTdllName} SHARED ${vCodeList})
  target_compile_definitions(${vTdllName} PRIVATE ${vCdefName}MakeTdll)
  target_link_libraries(${vTdllName} PRIVATE ${vTlibName})

endif(${vMoptName}MakeTdll)

##sll

set(vTsllName "t${vProjName}Sll")

option(${vMoptName}MakeTsll "build static library target" TRUE)
if(${vMoptName}MakeTsll)

  add_library(${vTsllName} STATIC ${vCodeList})
  target_compile_definitions(${vTsllName} PRIVATE ${vCdefName}MakeTsll)
  target_link_libraries(${vTsllName} PRIVATE ${vTlibName})

endif(${vMoptName}MakeTsll)

##exe

set(vTexeName "t${vProjName}Exe")
set(vTexePath "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(vTexeFile "${vTexePath}/${vTexeName}")

option(${vMoptName}MakeTexe "build executable target" TRUE)
if(${vMoptName}MakeTexe)

  add_executable(${vTexeName} ${vCodeList})
  target_compile_definitions(${vTexeName} PRIVATE ${vCdefName}MakeTexe)
  target_link_libraries(${vTexeName} PRIVATE ${vTlibName})

endif(${vMoptName}MakeTexe)

cmake_dependent_option(${vMoptName}MakeTest "build with testing" TRUE
  ${vMoptName}MakeTexe FALSE)
if(${vMoptName}MakeTest)

  include(CTest)
  enable_testing()

  function(fMakeTest vName vText)
    add_test(NAME ${vName} COMMAND ${vTexeFile} "test" ${vName})
    set_tests_properties(${vName} PROPERTIES PASS_REGULAR_EXPRESSION  ${vText})
  endfunction(fMakeTest)

  fMakeTest("TestingArg" "test was not found ! TestingArg")
  fMakeTest("HelloWorld" "HelloWorld")

endif(${vMoptName}MakeTest)
