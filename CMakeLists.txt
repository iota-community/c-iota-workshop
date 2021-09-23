cmake_minimum_required(VERSION 3.11)

cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})

project(iota_examples DESCRIPTION "IOTA examples")

enable_language(C)
enable_testing()

# fetch iota.c
include(FetchContent)
FetchContent_Declare(
  iota.c
  GIT_REPOSITORY http://github.com/iotaledger/iota.c.git
  GIT_TAG 34514eecaf6f75c31c35f9128a1156ea65086a75
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

# libs in the sandbox
link_directories("${CMAKE_INSTALL_PREFIX}/lib")

# function for building example binaries
function(add_example example_name example_src)
  add_executable(${example_name} "${example_src}")
  set_target_properties(${example_name} PROPERTIES C_STANDARD_REQUIRED NO C_STANDARD 99)
  target_include_directories(${example_name} PRIVATE ${PROJECT_SOURCE_DIR}/examples ${CMAKE_INSTALL_PREFIX}/include)
  add_dependencies(${example_name} iota_wallet)
  target_link_libraries(${example_name} PRIVATE iota_wallet)
endfunction(add_example)


# examples
add_example(e01_hello_world "examples/e01_hello_world.c")
add_example(e02_send_fetch_hello "examples/e02_send_fetch_hello.c")
add_example(e03_fetch_message "examples/e03_fetch_message.c")
add_example(e04_generate_address "examples/e04_generate_address.c")
add_example(e05_check_balance "examples/e05_check_balance.c")
add_example(e06_send_tokens "examples/e06_send_tokens.c")
