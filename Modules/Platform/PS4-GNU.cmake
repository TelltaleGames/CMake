if(__PS4_GNU)
  return()
endif()
set(__PS4_GNU 1)

set(CMAKE_DL_LIBS "")
set(CMAKE_LIBRARY_PATH_FLAG "-L")
set(CMAKE_LINK_LIBRARY_FLAG "-l")
set(CMAKE_LINK_DEF_FILE_FLAG "") # Empty string: passing the file is enough
set(CMAKE_LINK_LIBRARY_SUFFIX "")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING
 "Semicolon separated list of supported configuration types, only supports Debug, Release, MinSizeRel, and RelWithDebInfo, anything else will be ignored.")
mark_as_advanced(CMAKE_CONFIGURATION_TYPES)

# if(NOT DEFINED CMAKE_LINKER)
   # set(CMAKE_LINKER link)
# endif()

macro(__ps4_compiler_gnu lang)
  # Feature flags.
  set(CMAKE_${lang}_VERBOSE_FLAG "-v")
  set(CMAKE_${lang}_COMPILE_OPTIONS_PIC "-fPIC")
  if(NOT CMAKE_${lang}_COMPILER_VERSION VERSION_LESS 3.4)
    set(CMAKE_${lang}_COMPILE_OPTIONS_PIE "-fPIE")
  endif()
  set(CMAKE_SHARED_LIBRARY_${lang}_FLAGS "-fPIC")
  set(CMAKE_SHARED_LIBRARY_CREATE_${lang}_FLAGS "-shared")

  # Initial configuration flags.
  set(CMAKE_${lang}_FLAGS_INIT "")
  set(CMAKE_${lang}_FLAGS_DEBUG_INIT "-g")
  set(CMAKE_${lang}_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
  set(CMAKE_${lang}_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")
  set(CMAKE_${lang}_FLAGS_RELWITHDEBINFO_INIT "-O2 -g -DNDEBUG")
  set(CMAKE_${lang}_CREATE_PREPROCESSED_SOURCE "<CMAKE_${lang}_COMPILER> <DEFINES> <FLAGS> -E <SOURCE> > <PREPROCESSED_SOURCE>")
  set(CMAKE_${lang}_CREATE_ASSEMBLY_SOURCE "<CMAKE_${lang}_COMPILER> <DEFINES> <FLAGS> -S <SOURCE> -o <ASSEMBLY_SOURCE>")

endmacro()
