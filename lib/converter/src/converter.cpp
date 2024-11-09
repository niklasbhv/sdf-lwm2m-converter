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

#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include <sdf/sdf_cpp_core.h>
#include "lwm2m.h"
#include "converter.h"

using json = nlohmann::ordered_json;

//! Function used to convert sdf to lwm2m
int ConvertSdfToLwm2m(json& sdf_model_json, json& sdf_mapping_json, pugi::xml_document& lwm2m_xml)
{
    // Parse the sdf-model and the sdf-mapping
    sdf::SdfModel sdf_model = sdf::ParseSdfModel(sdf_model_json);
    sdf::SdfMapping sdf_mapping = sdf::ParseSdfMapping(sdf_mapping_json);

    return 0;
}

//! Function used to convert the Matter data model to sdf
int ConvertLwm2mToSdf(const pugi::xml_document& lwm2m_xml, json& sdf_model_json, json& sdf_mapping_json)
{
    return 0;
}
