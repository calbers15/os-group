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
include CMakeFiles/t2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/t2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/t2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/t2.dir/flags.make

CMakeFiles/t2.dir/test2.c.o: CMakeFiles/t2.dir/flags.make
CMakeFiles/t2.dir/test2.c.o: ../test2.c
CMakeFiles/t2.dir/test2.c.o: CMakeFiles/t2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/calbers15/eece-4811/os-group/p1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/t2.dir/test2.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/t2.dir/test2.c.o -MF CMakeFiles/t2.dir/test2.c.o.d -o CMakeFiles/t2.dir/test2.c.o -c /home/calbers15/eece-4811/os-group/p1/test2.c

CMakeFiles/t2.dir/test2.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/t2.dir/test2.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/calbers15/eece-4811/os-group/p1/test2.c > CMakeFiles/t2.dir/test2.c.i

CMakeFiles/t2.dir/test2.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/t2.dir/test2.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/calbers15/eece-4811/os-group/p1/test2.c -o CMakeFiles/t2.dir/test2.c.s

# Object files for target t2
t2_OBJECTS = \
"CMakeFiles/t2.dir/test2.c.o"

# External object files for target t2
t2_EXTERNAL_OBJECTS =

t2: CMakeFiles/t2.dir/test2.c.o
t2: CMakeFiles/t2.dir/build.make
t2: CMakeFiles/t2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/calbers15/eece-4811/os-group/p1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable t2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/t2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/t2.dir/build: t2
.PHONY : CMakeFiles/t2.dir/build

CMakeFiles/t2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/t2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/t2.dir/clean

CMakeFiles/t2.dir/depend:
	cd /home/calbers15/eece-4811/os-group/p1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/calbers15/eece-4811/os-group/p1 /home/calbers15/eece-4811/os-group/p1 /home/calbers15/eece-4811/os-group/p1/build /home/calbers15/eece-4811/os-group/p1/build /home/calbers15/eece-4811/os-group/p1/build/CMakeFiles/t2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/t2.dir/depend

