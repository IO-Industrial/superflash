/**
 *  @file: sdp.cpp
 *
 *  Copyright (C) 2020  Joe Turner <joe@agavemountain.com>
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
#include <getopt.h>
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "errors.h"
#include "commands/sdp_command.h"
#include "version.h"
#include "config/global_config.h"

using namespace std;
// using namespace spdlog;

const char *usage[] = {
    "Usage: sdp [options]",
	""
};

void print_usage()
{
    for (int i=0; *usage[i]; i++)
    {
        printf("%s\n", usage[i]);
    }
}

int main(int argc, char **argv)
{
    int c;
    std::string device_name = "";
	std::string command = "";
	char *file_name = NULL;
	char *file_data = NULL;
	
    printf("SDP utility %s\n", SUPER_FLASH_RELEASE);

    GlobalConfiguration &config  = GlobalConfiguration::instance();

    // Parse parameters
	while ((c = getopt(argc, argv, "c:d:f:")) != -1)
	{
		switch (c)
		{
			default:
				print_usage();
				return 1;
		}
	}

   
    printf("Done.\n");

    return 0;
}


