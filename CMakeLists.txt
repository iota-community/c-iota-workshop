#[[
Copyright (c) 2020 IOTA Stiftung
https://github.com/iota-community/c-iota-workshop

Refer to the LICENSE file for licensing information
]]

cmake_minimum_required(VERSION 3.11)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(c-iota-workshop DESCRIPTION "IOTA C Examples")

enable_language(C)

option(YOCTO "Enable Building in Yocto" OFF)

if(NOT YOCTO)
  include(FetchContent)

  FetchContent_Declare(
    iota.c
    GIT_REPOSITORY http://github.com/iotaledger/iota.c.git
    GIT_TAG ae5a638f04f68f3580eea98bfce09f9fb745cbeb
  )

  if(${CMAKE_VERSION} VERSION_LESS 3.14)
    macro(FetchContent_MakeAvailable NAME)
      FetchContent_GetProperties(${NAME})
      if(NOT ${NAME}_POPULATED)
        FetchContent_Populate(${NAME})
        add_subdirectory(${${NAME}_SOURCE_DIR} ${${NAME}_BINARY_DIR})
      endif()
    endmacro()
  endif()

  message(STATUS "Fetching iota.c")
  FetchContent_MakeAvailable(iota.c)

  # external libs module
  include(ExternalProject)

  link_directories("${CMAKE_INSTALL_PREFIX}/lib")

endif()

set (LIBS
  common
  cclient
  cjson
  http_parser
  logger
  keccak
  mbedtls
  mbedcrypto
  mbedx509
  pthread
)

add_subdirectory (examples)
