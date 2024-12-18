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

#include <iostream>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <pugixml.hpp>
#include <argparse/argparse.hpp>
#include <converter.h>
#include "main.h"

using json = nlohmann::ordered_json;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

//! Helper function that generates sdf-model and sdf-mapping filenames
//! Generates filenames of the format "path/to/file[-model|-mapping].json"
void GenerateSdfFilenames(const std::string& input, std::string& sdf_model_name, std::string& sdf_mapping_name){
    auto last_dot = input.find_last_of('.');

    sdf_model_name.append(input.substr(0, last_dot));
    sdf_model_name.append("-model");
    sdf_model_name.append(input.substr(last_dot));

    sdf_mapping_name.append(input.substr(0, last_dot));
    sdf_mapping_name.append("-mapping");
    sdf_mapping_name.append(input.substr(last_dot));
}

//! Helper function that generates device and cluster filenames
//! Generates filenames of the format "path/to/file[-device|-cluster].xml"
void GenerateLwm2mFilenames(const std::string& input, std::string& device_xml_name, std::string& cluster_xml_name){
    auto last_dot = input.find_last_of('.');

    device_xml_name.append(input.substr(0, last_dot));
    device_xml_name.append("-device");
    device_xml_name.append(input.substr(last_dot));

    cluster_xml_name.append(input.substr(0, last_dot));
    cluster_xml_name.append("-cluster");
    cluster_xml_name.append(input.substr(last_dot));
}

//! Main function
int main(int argc, char *argv[]) {
    // Define the program name
    argparse::ArgumentParser program("sdf-lwm2m-converter");

    // Define the set of possible arguments
    program.add_argument("--lwm2m-to-sdf")
        .help("Convert from LwM2M to SDF")
        .default_value(false);

    program.add_argument("--sdf-to-lwm2m")
        .help("Convert from SDF to LwM2M")
        .default_value(false);

    program.add_argument("--roundtrip")
        .help("Use round-tripping to convert from one format to the other and back to the original format")
        .default_value(false);

    program.add_argument("-sdf-model")
        .help("Path to the input JSON containing the SDF Model, required for conversion to LwM2M");

    program.add_argument("-sdf-mapping")
        .help("Path tp the input JSON containing the SDF Mapping, required for conversion to LwM2M");

    program.add_argument("-device-xml")
        .help("Path to a input XML containing the Device Type definition\n"
              "Requires specified clusters to be inside the given cluster folder");

    program.add_argument("-cluster-xml")
        .help("Path to a input XML containing a Cluster definition\n"
              "Used without a Device Type definition to create a Model with a single sdf_object");

    program.add_argument("-validate")
        .help("Validate the output files\n"
              "Requires the path to the schema for the output files as an input");

    program.add_argument("-o", "-output")
        .required()
        .help("Specify the output file\n"
              "For the LwM2M to SDF conversion, this will get split up into -model and -mapping\n"
              "For the SDF to LwM2M conversion, this will get split up into -device and -clusters");

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &err) {
        std::cerr << err.what() << std::endl;
        std::cerr << program;
        std::exit(1);
    }

    // Check if the conversion direction is lwm2m to sdf
    if (program.is_used("--lwm2m-to-sdf")) {
        // Check if the result should be validated
        bool validate = program.is_used("-validate");

        // Check if the path to a device type definition was given
        std::string path_device_xml;
        if (program.is_used("-device-xml")) {
            path_device_xml = program.get<std::string>("-device-xml");
        }

        // Check if the path to one or more cluster definitions was given
        if (program.is_used("-cluster-xml")) {
            auto path_cluster_xml = program.get<std::string>("-cluster-xml");
            std::list<pugi::xml_document> cluster_xml_list;
            // Check if the given path points onto a folder or a file
            json sdf_model;
            json sdf_mapping;
            // Check if the given -cluster-xml value is a path or a file
            if (std::filesystem::is_directory(path_cluster_xml)) {
                std::cout << "Loading and Parsing every Cluster XML of the given path" << std::endl;
                for (const auto &dir_entry: recursive_directory_iterator(path_cluster_xml)) {
                    pugi::xml_document cluster_xml;
                    LoadXmlFile(dir_entry.path().c_str(), cluster_xml);
                    cluster_xml_list.push_back(std::move(cluster_xml));
                }
            } else {
                std::cout << "Loading Cluster XML" << std::endl;
                pugi::xml_document cluster_xml;
                LoadXmlFile(path_cluster_xml.c_str(), cluster_xml);
                cluster_xml_list.push_back(std::move(cluster_xml));
            }
            // If a device type definition was loaded, convert both of the files
            if (!path_device_xml.empty()) {
                std::cout << "Loading Device XML" << std::endl;
                pugi::xml_document device_xml;
                LoadXmlFile(path_device_xml.c_str(), device_xml);
                std::cout << "Converting LwM2M to SDF" << std::endl;
                //ConvertLwm2mToSdf(std::move(device_xml), cluster_xml_list, sdf_model, sdf_mapping);
            }
                // Otherwise we just convert the list of clusters
            else {
                std::cout << "Converting LwM2M to SDF" << std::endl;
                //ConvertLwm2mToSdf(std::nullopt, cluster_xml_list, sdf_model, sdf_mapping);
            }

            // Check if round-tripping was selected
            if (program.is_used("--roundtrip")) {
                std::cout << "Round-tripping flag was set!" << std::endl;
                std::cout << "Converting SDF to LwM2M..." << std::endl;

                std::optional<pugi::xml_document> optional_device_xml;
                cluster_xml_list.clear();

                // Convert SDF back to LwM2M
                //ConvertSdfToLwm2m(sdf_model, sdf_mapping, optional_device_xml, cluster_xml_list);
                std::cout << "Successfully converted SDF to LwM2M!" << std::endl;

                // Generate the output file path
                std::string path_output_device_xml;
                std::string path_output_cluster_xml;
                GenerateLwm2mFilenames(program.get<std::string>("-output"), path_output_device_xml,
                                        path_output_cluster_xml);

                if (optional_device_xml.has_value()) {
                    std::cout << "Saving Device XML..." << std::endl;
                    SaveXmlFile(path_output_device_xml.c_str(), optional_device_xml.value());
                    std::cout << "Successfully saved Device XML!" << std::endl;
                    if (validate) {
                        if (ValidateLwm2m(path_device_xml.c_str(), program.get<std::string>("-validate").c_str()) ==
                            0) {
                            std::cout << "Device XML valid!..." << std::endl;
                        } else {
                            std::cout << "Device not valid!..." << std::endl;
                        }
                    }
                }

                std::cout << "Saving Cluster XML..." << std::endl;
                int counter = 0;
                for (const auto &cluster_xml: cluster_xml_list) {
                    // Generate a filename for each cluster by numbering them
                    std::string path = path_output_cluster_xml + "_" + std::to_string(counter) + ".xml";
                    SaveXmlFile(path.c_str(), cluster_xml);
                    // If the validation flag was set we try to validate the xml against a xsd schema
                    if (validate) {
                        if (ValidateLwm2m(path.c_str(), program.get<std::string>("-validate").c_str())) {
                            std::cout << "Cluster XML" << path << "valid!..." << std::endl;
                        } else {
                            std::cout << "Cluster XML" << path << "not valid!..." << std::endl;
                        }
                    }
                    counter++;
                }

                std::cout << "Successfully saved Cluster XML!" << std::endl;

            }
                // If the round-tripping flag was not set, we can just save the result
            else {
                // Generate filenames for SDF based on the -output parameter
                std::string path_sdf_model;
                std::string path_sdf_mapping;
                GenerateSdfFilenames(program.get<std::string>("-output"), path_sdf_model, path_sdf_mapping);

                std::cout << "Saving JSON files...." << std::endl;
                SaveJsonFile(path_sdf_model.c_str(), sdf_model);
                std::cout << "Successfully saved SDF-Model!" << std::endl;
                if (validate) {
                    if (ValidateSdf(path_sdf_model.c_str(), program.get<std::string>("-validate").c_str()) == 0) {
                        std::cout << "SDF-model valid!..." << std::endl;
                    } else {
                        std::cout << "SDF-model not valid!..." << std::endl;
                    }
                }

                SaveJsonFile(path_sdf_mapping.c_str(), sdf_mapping);
                std::cout << "Successfully saved SDF-Mapping!" << std::endl;
                if (validate) {
                    if (ValidateSdf(path_sdf_mapping.c_str(), program.get<std::string>("-validate").c_str()) == 0) {
                        std::cout << "SDF-mapping valid!..." << std::endl;
                    } else {
                        std::cout << "SDF-mapping not valid!..." << std::endl;
                    }
                }
            }
        }
            // If no path to one or more cluster definitions is given we exit the program
        else {
            std::cerr << "No valid combination of input parameters used" << std::endl;
            std::exit(1);
        }
    }
        // Check if the conversion direction is sdf to lwm2m
    else if(program.is_used("--sdf-to-lwm2m")) {
        bool validate = program.is_used("-validate");
        if (!(program.is_used("-sdf-model") and program.is_used("-sdf-mapping"))) {
            std::cerr << "SDF Model or SDF Mapping missing as an input argument" << std::endl;
            std::exit(1);
        }

        auto path_sdf_model = program.get<std::string>("-sdf-model");
        auto path_sdf_mapping = program.get<std::string>("-sdf-mapping");

        std::cout << "Loading SDF-Model..." << std::endl;
        json sdf_model_json;
        LoadJsonFile(path_sdf_model.c_str(), sdf_model_json);

        std::cout << "Loading SDF-Mapping..." << std::endl;
        json sdf_mapping_json;
        LoadJsonFile(path_sdf_mapping.c_str(), sdf_mapping_json);

        std::optional<pugi::xml_document> optional_device_xml;
        std::list<pugi::xml_document> cluster_xml_list;
        //ConvertSdfToLwm2m(sdf_model_json, sdf_mapping_json, optional_device_xml, cluster_xml_list);

        // Check if the round-tripping flag was set
        if (program.is_used("--roundtrip")) {
            std::cout << "Round-tripping flag was set!" << std::endl;
            std::cout << "Converting LwM2M to SDF..." << std::endl;
            sdf_model_json.clear();
            sdf_mapping_json.clear();

            // Convert LwM2M back to SDF
            //ConvertLwm2mToSdf(optional_device_xml, cluster_xml_list, sdf_model_json, sdf_mapping_json);
            std::cout << "Successfully converted LwM2M to SDF!" << std::endl;

            // Generate filenames for SDF based on the -output parameter
            std::string path_output_sdf_model;
            std::string path_output_sdf_mapping;
            GenerateSdfFilenames(program.get<std::string>("-output"), path_sdf_model, path_sdf_mapping);

            std::cout << "Saving JSON files...." << std::endl;
            SaveJsonFile(path_output_sdf_model.c_str(), sdf_model_json);
            std::cout << "Successfully saved SDF-Model!" << std::endl;
            if (validate) {
                if (ValidateSdf(path_output_sdf_model.c_str(), program.get<std::string>("-validate").c_str()) == 0) {
                    std::cout << "SDF-model valid!..." << std::endl;
                } else {
                    std::cout << "SDF-model not valid!..." << std::endl;
                }
            }

            SaveJsonFile(path_output_sdf_mapping.c_str(), sdf_mapping_json);
            std::cout << "Successfully saved SDF-Mapping!" << std::endl;
            if (validate) {
                if (ValidateSdf(path_output_sdf_mapping.c_str(), program.get<std::string>("-validate").c_str()) == 0) {
                    std::cout << "SDF-mapping valid!..." << std::endl;
                } else {
                    std::cout << "SDF-mapping not valid!..." << std::endl;
                }
            }
        }
        else {
            std::string path_device_xml;
            std::string path_cluster_xml;
            GenerateLwm2mFilenames(program.get<std::string>("-output"), path_device_xml, path_cluster_xml);

            if (optional_device_xml.has_value()) {
                std::cout << "Saving Device XML..." << std::endl;
                SaveXmlFile(path_device_xml.c_str(), optional_device_xml.value());
                if (validate) {
                    if (ValidateLwm2m(path_device_xml.c_str(), program.get<std::string>("-validate").c_str()) == 0) {
                        std::cout << "Device XML valid!..." << std::endl;
                    } else {
                        std::cout << "Device not valid!..." << std::endl;
                    }
                }
            }

            std::cout << "Saving Cluster XML..." << std::endl;
            int counter = 0;
            for (const auto& cluster_xml : cluster_xml_list) {
                // Generate a filename for each cluster by numbering them
                std::string path = path_cluster_xml + "_" + std::to_string(counter) + ".xml";
                SaveXmlFile(path.c_str(), cluster_xml);
                if (validate) {
                    if (ValidateLwm2m(path.c_str(), program.get<std::string>("-validate").c_str())) {
                        std::cout << "Cluster XML" << path << "valid!..." << std::endl;
                    } else {
                        std::cout << "Cluster XML" << path << "not valid!..." << std::endl;
                    }
                }
                counter ++;
            }
        }
    }
        // Print help of neither convert-to-sdf nor convert-to-lwm2m are given
    else{
        std::cout << program;
    }

    return 0;
}
