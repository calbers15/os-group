# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/calbers15/eece-4811/os-group/p1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/calbers15/eece-4811/os-group/p1/build

# Include any dependencies generated for this target.
include CMakeFiles/p1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/p1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/p1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p1.dir/flags.make

CMakeFiles/p1.dir/main.c.o: CMakeFiles/p1.dir/flags.make
CMakeFiles/p1.dir/main.c.o: ../main.c
CMakeFiles/p1.dir/main.c.o: CMakeFiles/p1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calbers15/eece-4811/os-group/p1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/p1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/p1.dir/main.c.o -MF CMakeFiles/p1.dir/main.c.o.d -o CMakeFiles/p1.dir/main.c.o -c /home/calbers15/eece-4811/os-group/p1/main.c

CMakeFiles/p1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/p1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/calbers15/eece-4811/os-group/p1/main.c > CMakeFiles/p1.dir/main.c.i

CMakeFiles/p1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/p1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/calbers15/eece-4811/os-group/p1/main.c -o CMakeFiles/p1.dir/main.c.s

# Object files for target p1
p1_OBJECTS = \
"CMakeFiles/p1.dir/main.c.o"

# External object files for target p1
p1_EXTERNAL_OBJECTS =

p1: CMakeFiles/p1.dir/main.c.o
p1: CMakeFiles/p1.dir/build.make
p1: CMakeFiles/p1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calbers15/eece-4811/os-group/p1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable p1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p1.dir/build: p1
.PHONY : CMakeFiles/p1.dir/build

CMakeFiles/p1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p1.dir/clean

CMakeFiles/p1.dir/depend:
	cd /home/calbers15/eece-4811/os-group/p1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calbers15/eece-4811/os-group/p1 /home/calbers15/eece-4811/os-group/p1 /home/calbers15/eece-4811/os-group/p1/build /home/calbers15/eece-4811/os-group/p1/build /home/calbers15/eece-4811/os-group/p1/build/CMakeFiles/p1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p1.dir/depend

