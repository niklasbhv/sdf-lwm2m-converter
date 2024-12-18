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
 * Functions to convert between sdf and matter.
 */

#ifndef SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_CONVERTER_H_
#define SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_CONVERTER_H_

#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include <list>
#include "lwm2m_to_sdf.h"
#include "sdf_to_lwm2m.h"

//! @brief Convert sdf to lwm2m.
//!
//! This function converts a given sdf-model and sdf-mapping into the lwm2m format.
//!
//! @param sdf_model The input lwm2m definition.
//! @param sdf_mapping The input sdf-mapping.
//! @param lwm2m_xml The output lwm2m definition.
//! @return 0 on success, negative on failure.
int ConvertSdfToLwm2m(nlohmann::ordered_json& sdf_model_json, nlohmann::ordered_json& sdf_mapping_json,
                       pugi::xml_document& lwm2m_xml);

//! @brief Convert lwm2m to sdf.
//!
//! This function converts a given sdf-model and sdf-mapping into the lwm2m format.
//!
//! @param lwm2m_xml The input lwm2m.
//! @param sdf_model_json The output sdf-model.
//! @param sdf_mapping_json The output sdf-mapping.
//! @return 0 on success, negative on failure.
int ConvertLwm2mToSdf(const pugi::xml_document& lwm2m_xml, nlohmann::ordered_json& sdf_model_json,
                      nlohmann::ordered_json& sdf_mapping_json);

#endif //SDF_LWM2M_CONVERTER_LIB_CONVERTER_INCLUDE_CONVERTER_H_
