/**
 *  @file: global_config.h
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
#include "simpleini/SimpleIni.h"

/**
 * \brief Global Configuration
 * 
 * This class represents the configuration file stored in the user's home
 * diretory.  This can hold various configuration options to make the
 * superflash utility easier to use.
 * 
 * The default location is $HOME/.superflash/config
 */
class GlobalConfiguration {
public:
    static GlobalConfiguration& instance()
    {
        static GlobalConfiguration s;
        return s;
    }

private:
    GlobalConfiguration()
    {
        load_ini();
    }

    //! \brief Load global configuration ini file
    //!
    //! This function will load the global configuration file.
    //! This file is stored in $HOME/.superflash/config.ini
    //! If the $HOME/.superflash directory does not exist, it is
    //! created, and a configuration file with default values
    //! saved.
    //!
    //! The environment variable "SUPERFLASH_CONFIG" is defined,
    //! it will be used instead.
    //!
    void load_ini();

    //! \brief Load default configuration values
    //!
    void load_default_values();

    void save_ini();

    CSimpleIniA ini;
    std::string _config_path;
};
