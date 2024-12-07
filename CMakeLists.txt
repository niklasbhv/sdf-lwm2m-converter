cmake_minimum_required(VERSION 3.22.1)
project(sdf_lwm2m_converter)

set(CMAKE_CXX_STANDARD 17)

add_executable(sdf_lwm2m_converter src/main.cpp
        lib/converter/src/converter.cpp
        lib/validator/src/validator.cpp
        lib/converter/src/lwm2m_to_sdf.cpp
        lib/converter/src/sdf_to_lwm2m.cpp
        lib/converter/include/converter.h
        lib/validator/include/validator.h
        lib/converter/src/lwm2m.cpp
        lib/converter/include/lwm2m.h
        lib/converter/include/mapping.h
        src/main.h)

# add dependencies
include(cmake/CPM.cmake)

add_subdirectory(lib/converter)
add_subdirectory(lib/validator)

CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:zeux/pugixml@1.14")
CPMAddPackage("gh:p-ranav/argparse@3.0")
CPMAddPackage("gh:niklasbhv/sdf-cpp-core@0.1.0")

target_link_libraries(sdf_lwm2m_converter validator converter nlohmann_json::nlohmann_json pugixml::pugixml argparse::argparse sdf_cpp_core)