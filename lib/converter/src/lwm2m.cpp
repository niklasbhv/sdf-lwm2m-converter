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

Resource Resource::Parse(pugi::xml_node& resource_node) {
    Resource resource;

    return resource;
}

void Resource::Serialize() {

}

Object Object::Parse(pugi::xml_node& object_node) {
    Object object;

    return object;
}

void Object::Serialize() {

}

}