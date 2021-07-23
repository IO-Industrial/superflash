#!/bin/bash
#
# This script will automatically reformat all of the source code files
# into the proper style.
#
find . -iname *.h -o -iname *.cpp -o -iname *.hpp | xargs clang-format -style=WebKit -i
