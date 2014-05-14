include(Platform/WindowsPaths)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")          # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")          # .so
set(CMAKE_IMPORT_LIBRARY_PREFIX "")
set(CMAKE_IMPORT_LIBRARY_SUFFIX ".lib")
set(CMAKE_EXECUTABLE_SUFFIX ".exe")          # .exe
set(CMAKE_LINK_LIBRARY_SUFFIX ".lib")
set(CMAKE_DL_LIBS "")

set(CMAKE_FIND_LIBRARY_PREFIXES "")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

include (CMakeForceCompiler)
set(CMAKE_XBONE_COMPILER "$ENV{DurangoXDK}/xdk/VC/bin/x86_amd64/cl.exe")
string(REPLACE "\\" "/" CMAKE_XBONE_COMPILER "${CMAKE_XBONE_COMPILER}")
CMAKE_FORCE_C_COMPILER ("${CMAKE_XBONE_COMPILER}" MSVC)
CMAKE_FORCE_CXX_COMPILER ("${CMAKE_XBONE_COMPILER}" MSVC)

set (CMAKE_CXX_COMPILER_ID "MSVC")
set (CMAKE_C_COMPILER_ID "MSVC")

#just skip the compiler check for now.
set (CMAKE_CXX_COMPILER_WORKS TRUE)
set (CMAKE_C_COMPILER_WORKS TRUE)

set (CMAKE_C_COMPILER_VERSION "17.00.65501.17025")
set (CMAKE_CXX_COMPILER_VERSION "17.00.65501.17025")

set (MSVC_C_ARCHITECTURE_ID 64)
set (MSVC_CXX_ARCHITECTURE_ID 64)


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
