# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/misile/siderepos/dpkgpromax/frontend

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/misile/siderepos/dpkgpromax/frontend

# Include any dependencies generated for this target.
include CMakeFiles/MyExecutable.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyExecutable.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyExecutable.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyExecutable.dir/flags.make

CMakeFiles/MyExecutable.dir/lib.c.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/lib.c.o: lib.c
CMakeFiles/MyExecutable.dir/lib.c.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/misile/siderepos/dpkgpromax/frontend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MyExecutable.dir/lib.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/lib.c.o -MF CMakeFiles/MyExecutable.dir/lib.c.o.d -o CMakeFiles/MyExecutable.dir/lib.c.o -c /home/misile/siderepos/dpkgpromax/frontend/lib.c

CMakeFiles/MyExecutable.dir/lib.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyExecutable.dir/lib.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/misile/siderepos/dpkgpromax/frontend/lib.c > CMakeFiles/MyExecutable.dir/lib.c.i

CMakeFiles/MyExecutable.dir/lib.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyExecutable.dir/lib.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/misile/siderepos/dpkgpromax/frontend/lib.c -o CMakeFiles/MyExecutable.dir/lib.c.s

CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o: microtar/src/microtar.c
CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/misile/siderepos/dpkgpromax/frontend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o -MF CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o.d -o CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o -c /home/misile/siderepos/dpkgpromax/frontend/microtar/src/microtar.c

CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/misile/siderepos/dpkgpromax/frontend/microtar/src/microtar.c > CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.i

CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/misile/siderepos/dpkgpromax/frontend/microtar/src/microtar.c -o CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.s

CMakeFiles/MyExecutable.dir/main.c.o: CMakeFiles/MyExecutable.dir/flags.make
CMakeFiles/MyExecutable.dir/main.c.o: main.c
CMakeFiles/MyExecutable.dir/main.c.o: CMakeFiles/MyExecutable.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/misile/siderepos/dpkgpromax/frontend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MyExecutable.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/MyExecutable.dir/main.c.o -MF CMakeFiles/MyExecutable.dir/main.c.o.d -o CMakeFiles/MyExecutable.dir/main.c.o -c /home/misile/siderepos/dpkgpromax/frontend/main.c

CMakeFiles/MyExecutable.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/MyExecutable.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/misile/siderepos/dpkgpromax/frontend/main.c > CMakeFiles/MyExecutable.dir/main.c.i

CMakeFiles/MyExecutable.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/MyExecutable.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/misile/siderepos/dpkgpromax/frontend/main.c -o CMakeFiles/MyExecutable.dir/main.c.s

# Object files for target MyExecutable
MyExecutable_OBJECTS = \
"CMakeFiles/MyExecutable.dir/lib.c.o" \
"CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o" \
"CMakeFiles/MyExecutable.dir/main.c.o"

# External object files for target MyExecutable
MyExecutable_EXTERNAL_OBJECTS =

MyExecutable: CMakeFiles/MyExecutable.dir/lib.c.o
MyExecutable: CMakeFiles/MyExecutable.dir/microtar/src/microtar.c.o
MyExecutable: CMakeFiles/MyExecutable.dir/main.c.o
MyExecutable: CMakeFiles/MyExecutable.dir/build.make
MyExecutable: /usr/lib64/libcurl.so
MyExecutable: /usr/lib64/libarchive.so
MyExecutable: CMakeFiles/MyExecutable.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/misile/siderepos/dpkgpromax/frontend/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable MyExecutable"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyExecutable.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyExecutable.dir/build: MyExecutable
.PHONY : CMakeFiles/MyExecutable.dir/build

CMakeFiles/MyExecutable.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyExecutable.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyExecutable.dir/clean

CMakeFiles/MyExecutable.dir/depend:
	cd /home/misile/siderepos/dpkgpromax/frontend && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/misile/siderepos/dpkgpromax/frontend /home/misile/siderepos/dpkgpromax/frontend /home/misile/siderepos/dpkgpromax/frontend /home/misile/siderepos/dpkgpromax/frontend /home/misile/siderepos/dpkgpromax/frontend/CMakeFiles/MyExecutable.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/MyExecutable.dir/depend

