# Set the project name
project(converter)

# Add a library with the above sources
add_library(${PROJECT_NAME} src/converter.cpp
        src/lwm2m.cpp
        src/sdf.cpp
        src/sdf_to_lwm2m.cpp
        src/lwm2m_to_sdf.cpp
        include/mapping.h
        include/lwm2m.h
        include/sdf.h
        include/sdf_to_lwm2m.h
        include/lwm2m_to_sdf.h)

# add dependencies
include(../../cmake/CPM.cmake)

CPMAddPackage("gh:nlohmann/json@3.11.3")
CPMAddPackage("gh:zeux/pugixml@1.14")

target_include_directories( ${PROJECT_NAME}
        PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(converter nlohmann_json::nlohmann_json pugixml::pugixml)
