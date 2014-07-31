set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set(CMAKE_SHARED_LIBRARY_PREFIX "")          # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".suprx")          # .so
set(CMAKE_IMPORT_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_SUFFIX ".suprx")
set(CMAKE_EXECUTABLE_SUFFIX ".self")          # .exe
set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_DL_LIBS "")

set(CMAKE_FIND_LIBRARY_PREFIXES "")
set(CMAKE_FIND_LIBRARY_SUFFIXES "")

include (CMakeForceCompiler)
set(CMAKE_PS4_COMPILER "$ENV{SCE_ORBIS_SDK_DIR}/host_tools/bin/orbis-clang++.exe")
string(REPLACE "\\" "/" CMAKE_PS4_COMPILER "${CMAKE_PS4_COMPILER}")
CMAKE_FORCE_C_COMPILER ("${CMAKE_PS4_COMPILER}" GNU)
CMAKE_FORCE_CXX_COMPILER ("${CMAKE_PS4_COMPILER}" GNU)

set (CMAKE_CXX_COMPILER_ID "GNU")
set (CMAKE_C_COMPILER_ID "GNU")


#just skip the compiler check for now.
set (CMAKE_CXX_COMPILER_WORKS TRUE)
set (CMAKE_C_COMPILER_WORKS TRUE)

# for borland make long command lines are redirected to a file
# with the following syntax, see Windows-bcc32.cmake for use
if(CMAKE_GENERATOR MATCHES "Borland")
  set(CMAKE_START_TEMP_FILE "@&&|\n")
  set(CMAKE_END_TEMP_FILE "\n|")
endif()

# for nmake make long command lines are redirected to a file
# with the following syntax, see Windows-bcc32.cmake for use
if(CMAKE_GENERATOR MATCHES "NMake")
  set(CMAKE_START_TEMP_FILE "@<<\n")
  set(CMAKE_END_TEMP_FILE "\n<<")
endif()
