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
 * Functions to load and save xml and json files.
 */

#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include "validator.h"

#ifndef SDF_LWM2M_CONVERTER_SRC_MAIN_H_
#define SDF_LWM2M_CONVERTER_SRC_MAIN_H_

//! @brief Load a json file.
//!
//! This function loads the json file for a given path.
//!
//!@param path The path to the file.
//!@param json_file The resulting json object.
//!@return 0 on success, negative on failure,
static inline int LoadJsonFile(const char* path, nlohmann::ordered_json& json_file)
{
    try {
        std::ifstream f(path);
        json_file = nlohmann::ordered_json::parse(f);
    }
    catch (const std::exception& err) {
        std::cerr << "Failed to load JSON file: " << path << std::endl;
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}

//! @brief Save a json object into a json file.
//!
//! This function saves a json object into a new json file.
//!
//! @param path The path to the file.
//! @param json_file The input json file.
//! @return 0 on success, negative on failure.
static inline int SaveJsonFile(const char* path, const nlohmann::ordered_json& json_file)
{
    try {
        std::ofstream f(path);
        f << json_file.dump(4);
    }
    catch (const std::exception& err) {
        std::cerr << "Failed to save JSON file: " << path << std::endl;
        std::cerr << err.what() << std::endl;
        return -1;
    }
    return 0;
}

//!@brief Load a xml file.
//!
//! This function loads the xml file for a given path.
//!
//! @param path The path to the file.
//! @param xml_file The resulting xml file.
//! @return 0 on success, negative on failure.
static inline int LoadXmlFile(const char* path, pugi::xml_document& xml_file)
{
    pugi::xml_parse_result result = xml_file.load_file(path);
    if (!result){
        std::cerr << "Failed to load XML file: " << path << std::endl;
        return -1;
    }
    return 0;
}

//! @brief Save a xml object into a xml file.
//!
//! The function saves a xml object into a xml file.
//!
//! @param path The path to the file.
//! @param xml_file The input xml file.
//! @return 0 on success, negative on failure.
static inline int SaveXmlFile(const char* path, const pugi::xml_document& xml_file)
{
    return xml_file.save_file(path);
}

#endif //SDF_LWM2M_CONVERTER_SRC_MAIN_H_
