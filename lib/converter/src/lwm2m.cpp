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

#include "lwm2m.h"
#include <pugixml.hpp>

namespace lwm2m {

Resource Resource::Parse(const pugi::xml_node& resource_node) {
    Resource resource;

    return resource;
}

void Resource::Serialize() {

}

Object Object::Parse(const pugi::xml_node& object_node) {
    Object object;
    object.name = object_node.child("Name").value();
    object.object_type = object_node.attribute("ObjectType").value();
    object.description_1 = object_node.child("Description1").value();
    object.description_2 = object_node.child("Description2").value();
    object.object_id = atoi(object_node.child("ObjectID").value());
    object.object_urn = object_node.child("ObjectURN").value();
    object.lwm2m_version = atof(object_node.child("LWM2MVersion").value());
    object.object_version = atof(object_node.child("ObjectVersion").value());
    if (object_node.child("MultipleInstances").value() == "Single") {
        object.multiple_instances = false;
    } else {
        object.multiple_instances = true;
    }
    if (object_node.child("Mandatory").value() == "Optional") {
        object.mandatory = false;
    } else {
        object.mandatory = true;
    }
    for (const auto child_node : object_node.child("Resource").children()) {
        object.resources[child_node.attribute("ID").as_int()] = Resource(child_node);
    }
    return object;
}

void Object::Serialize() {

}

}