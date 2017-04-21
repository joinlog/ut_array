CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

project(ut_array CXX C)
set(CMAKE_INSTALL_PREFIX ./)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/)

#ADD_SUBDIRECTORY(src)

set(srcpath ../src/)
include_directories(${srcpath})
AUX_SOURCE_DIRECTORY(${srcpath} SRC_FILES)
#link_directories(../build)

function(cxx_executable_unit name)
  set(demopath ${name}/)
  include_directories (${demopath})
  AUX_SOURCE_DIRECTORY(${demopath} DEMO_FILES)
  add_executable(${name} ${SRC_FILES} ${DEMO_FILES})
  install(TARGETS ${name}
        RUNTIME DESTINATION .
        LIBRARY DESTINATION .
        ARCHIVE DESTINATION .
        PUBLIC_HEADER DESTINATION include
        )
endfunction()


cxx_executable_unit(demo_basic_function)
