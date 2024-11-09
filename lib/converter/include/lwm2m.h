/**
 *  Copyright 2024 Niklas Meyer
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * @file
 * @author Niklas Meyer <nik_mey@uni-bremen.de>
 *
 * @section Description
 *
 * Structs which contain parsed information for lwm2m and functions to parse from xml files.
 */

#ifndef SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_LWM2M_H_
#define SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_LWM2M_H_

#include <string>
#include <map>
#include <pugixml.hpp>

namespace lwm2m {

enum Type {
    String,
    Integer,
    Float,
    Boolean,
    Opaque,
    Time,
    ObjectLink,
    UndefinedType
};

enum Operations {
    Read,
    Write,
    ReadWrite,
    Execute,
    UndefinedOperation
};

struct Resource {
    std::string name;
    Operations operations;
    bool multiple_instances;
    bool mandatory;
    Type type;
    std::string range_enumeration;
    std::string units;
    std::string description;

    static Resource Parse(const pugi::xml_node& resource_node);
    void Serialize();
};

struct Object {
    std::string name;
    std::string object_type;
    std::string description_1;
    std::string description_2;
    int object_id;
    std::string object_urn;
    float lwm2m_version;
    float object_version;
    bool multiple_instances;
    bool mandatory;
    std::map<int, Resource> resources;

    static Object Parse(const pugi::xml_node& object_node);
    void Serialize();
};

}

#endif //SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_LWM2M_H_
