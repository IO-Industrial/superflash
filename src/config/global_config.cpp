/**
 *  @file: global_config.cpp
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
#include <iostream>
#include <stdio.h>

#include "config/environment.h"
#include "config/global_config.h"
#include "file_utilities.h"

void GlobalConfiguration::load_default_values()
{
    ini.SetValue("transports", "utp", "/dev/sg0");
    ini.SetValue("transports", "serial", "/dev/ttyUSB0");
}

void GlobalConfiguration::save_ini()
{
    if (ini.SaveFile(_config_path.c_str()) < 0) {
        printf("Error, could not save configuration file (%s).", _config_path.c_str());
        return;
    };
}

void GlobalConfiguration::load_ini()
{
    bool ret = false;
    const char* SUPERFLASH_CONFIG = "SUPERFLASH_CONFIG";
    std::string home_path = Environment::home_path() + "/.superflash";
    _config_path = home_path + "/config";

    // Create $HOME/.superflash if it doesn't exist.
    if (!doesDirectoryExist(home_path)) {
#if defined(_WIN32)
        _mkdir(home_path.c_str());
#else
        mkdir(home_path.c_str(), 0755);
#endif

        load_default_values();

        save_ini();
    }

    // env variable can override the configuration
    if (Environment::isExists(SUPERFLASH_CONFIG)) {
        _config_path = Environment::get(SUPERFLASH_CONFIG);
    }

    ini.LoadFile(_config_path.c_str());
    std::cout << "config_path = " << _config_path << std::endl;
}
