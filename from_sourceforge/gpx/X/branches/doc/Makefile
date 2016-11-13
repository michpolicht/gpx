# Copyright (c) 2010, Michal Policht. This file is dually licensed under terms of 
# either WTFPL or BEER-WARE LICENSE. You may obtain the copy of WTFPL or BEER-WARE
# LICENSE by googling it. NO WARRANTY.

AWK = awk
LIC_QUALIFIER = MP
LIC_DSLASH = LICENSE.MP.dslash.inc

.PHONY: help license

help:
		@echo "This Makefile is responsible for code maintenance, \
not building."
		@echo "No building is required for this module."
		@echo ""
		@echo "Make targets are:"
		@echo "license - append license footer to source and header files."

license: $(LIC_DSLASH)
		@echo "Putting license..."
		@find include/gpx \
		\( -name '*.cpp' -o -name '*.c' -o -name '*.hpp' -o -name '*.h' \) \
		-exec putlic.sh {} $(LIC_DSLASH) dslash $(LIC_QUALIFIER) \;
