#[[
Copyright (c) 2020 IOTA Stiftung
https://github.com/iota-community/c-iota-workshop

Refer to the LICENSE file for licensing information
]]

cmake_minimum_required(VERSION 3.11)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

include(GNUInstallDirs)

# fetch external libs
include(ExternalProject)
project (examples)

enable_language(C)

add_executable (iota_c_hello_world e01_hello_world.c)
add_executable (iota_c_send_hello e02_send_hello.c)
add_executable (iota_c_receive_hello e03_receive_hello.c)
add_executable (iota_c_generate_address e04_generate_address.c)
add_executable (iota_c_check_balance e05_check_balance.c)
add_executable (iota_c_send_tokens e06_send_tokens.c)

set (TOP_DIR ${PROJECT_SOURCE_DIR}/../)

target_include_directories(iota_c_hello_world PRIVATE 
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_include_directories(iota_c_send_hello PRIVATE
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_include_directories(iota_c_receive_hello PRIVATE
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_include_directories(iota_c_generate_address PRIVATE
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_include_directories(iota_c_check_balance PRIVATE
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_include_directories(iota_c_send_tokens PRIVATE
  ${TOP_DIR}
  ${CMAKE_INSTALL_PREFIX}/include
  ${CMAKE_INSTALL_PREFIX}/include/cjson
  ${iota.c_SOURCE_DIR}
)

target_link_libraries (iota_c_hello_world PUBLIC ${LIBS})
target_link_libraries (iota_c_send_hello PUBLIC ${LIBS} m)
target_link_libraries (iota_c_receive_hello PUBLIC ${LIBS})
target_link_libraries (iota_c_generate_address PUBLIC ${LIBS})
target_link_libraries (iota_c_check_balance PUBLIC ${LIBS})
target_link_libraries (iota_c_send_tokens PUBLIC ${LIBS} m)

install (TARGETS iota_c_hello_world RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install (TARGETS iota_c_send_hello RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install (TARGETS iota_c_receive_hello RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install (TARGETS iota_c_generate_address RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install (TARGETS iota_c_check_balance RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
install (TARGETS iota_c_send_tokens RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

