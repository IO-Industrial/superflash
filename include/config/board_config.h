/**
 *  @file: board_config.h
 *
 *  Copyright (C) 2018  Joe Turner <joe@agavemountain.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once
#include <string>
#include <iostream>
#include "yaml-cpp/yaml.h"

class BoardConfig
{
public:
    void load(std::string &filename)
    {
        try {

            YAML::Node config = YAML::LoadFile(filename);

            if (config["transport"]) {
                which_transport = config["transport"].as<std::string>();
                std::cout << "Transport: " << which_transport << "\n";
            }

            std::string transport = which_transport + "_transport";
            if (config[transport.c_str()]) {
                std::cout << "Transport found: " << transport << "\n";
            }

            const YAML::Node& device = config["device"];
            name = device["name"].as<std::string>();
            std::cout << "device name: " << name << "\n";
        

        } catch(const YAML::ParserException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }

    std::string which_transport;
    std::string name;
};
