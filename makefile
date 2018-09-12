MODULES:=$(wildcard src/*)

# this must remain the first target in the makefile
.PHONY: default
default: build

.PHONY: clean
clean: 
	rm -rf inc lib bin

.PHONY: test
test: build
	./gui_test/

.PHONY: build
build: create_directory_structure \
       build_all_mdules


.PHONY: create_directory_structure
create_directory_structure:
	mkdir -p inc lib bin


.PHONY: build_all_mdules 
build_all_mdules : $(MODULES)


.PHONY: $(MODULES)
$(MODULES) :
	make -C $@

# dependency tree between projects:
src/gui : src/database \
	  src/tcl_interface \
	  src/javascript_interface \
	  src/python_interface

src/tcl_interface : src/database

src/unit_tests : src/database

src/javascript_interface : src/database

src/python_interface : src/database

