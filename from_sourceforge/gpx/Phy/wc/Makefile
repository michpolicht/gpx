# Copyright (c) 2010, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY.

AWK = awk
LIC_QUALIFIER = MP
LIC_DSLASH = LICENSE.MP.dslash.inc
LIC_HASH = LICENSE.MP.hash.inc

.PHONY: help sources license

help:
		@echo "This Makefile is responsible for code maintenance, \
not building."
		@echo "Use CMake if you wish to build the software."
		@echo ""
		@echo "Make targets are:"
		@echo "sources - generate list of sources and put them into CMakeLists.txt".
		@echo "license - append license footer to source and header files."

sources:
		@echo "Generating list of sources..."
		$(AWK) -v src_dirs="src" -v src_files="*.cpp;*.c" -f cmakesrcs.awk CMakeLists.txt > CMakeLists.txt.new
		mv CMakeLists.txt.new CMakeLists.txt

license:
		@echo "Putting license..."
		@find src/gpx include/gpx cmake \
		\( -name '*.cpp' -o -name '*.c' -o -name '*.hpp' -o -name '*.h' -o -name '*.cpp.in' -o -name '*.hpp.in' \) \
		-exec putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) \;
		@find cmake \
		\( -name '*.cmake' \) \
		-exec putlic.sh {} $(LIC_HASH) hash $(LIC_QUALIFIER) \;
		@putlic.sh CMakeLists.txt $(LIC_HASH) hash $(LIC_QUALIFIER)
