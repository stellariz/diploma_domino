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
CMAKE_COMMAND = /snap/clion/193/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/193/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ruslan/CLionProjects/diplom_domino

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruslan/CLionProjects/diplom_domino/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/diplom_domino.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/diplom_domino.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/diplom_domino.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/diplom_domino.dir/flags.make

CMakeFiles/diplom_domino.dir/main.cpp.o: CMakeFiles/diplom_domino.dir/flags.make
CMakeFiles/diplom_domino.dir/main.cpp.o: ../main.cpp
CMakeFiles/diplom_domino.dir/main.cpp.o: CMakeFiles/diplom_domino.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruslan/CLionProjects/diplom_domino/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/diplom_domino.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/diplom_domino.dir/main.cpp.o -MF CMakeFiles/diplom_domino.dir/main.cpp.o.d -o CMakeFiles/diplom_domino.dir/main.cpp.o -c /home/ruslan/CLionProjects/diplom_domino/main.cpp

CMakeFiles/diplom_domino.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diplom_domino.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruslan/CLionProjects/diplom_domino/main.cpp > CMakeFiles/diplom_domino.dir/main.cpp.i

CMakeFiles/diplom_domino.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diplom_domino.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruslan/CLionProjects/diplom_domino/main.cpp -o CMakeFiles/diplom_domino.dir/main.cpp.s

CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o: CMakeFiles/diplom_domino.dir/flags.make
CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o: ../Cell/Cell.cpp
CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o: CMakeFiles/diplom_domino.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruslan/CLionProjects/diplom_domino/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o -MF CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o.d -o CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o -c /home/ruslan/CLionProjects/diplom_domino/Cell/Cell.cpp

CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruslan/CLionProjects/diplom_domino/Cell/Cell.cpp > CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.i

CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruslan/CLionProjects/diplom_domino/Cell/Cell.cpp -o CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.s

CMakeFiles/diplom_domino.dir/Field/Field.cpp.o: CMakeFiles/diplom_domino.dir/flags.make
CMakeFiles/diplom_domino.dir/Field/Field.cpp.o: ../Field/Field.cpp
CMakeFiles/diplom_domino.dir/Field/Field.cpp.o: CMakeFiles/diplom_domino.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruslan/CLionProjects/diplom_domino/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/diplom_domino.dir/Field/Field.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/diplom_domino.dir/Field/Field.cpp.o -MF CMakeFiles/diplom_domino.dir/Field/Field.cpp.o.d -o CMakeFiles/diplom_domino.dir/Field/Field.cpp.o -c /home/ruslan/CLionProjects/diplom_domino/Field/Field.cpp

CMakeFiles/diplom_domino.dir/Field/Field.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diplom_domino.dir/Field/Field.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruslan/CLionProjects/diplom_domino/Field/Field.cpp > CMakeFiles/diplom_domino.dir/Field/Field.cpp.i

CMakeFiles/diplom_domino.dir/Field/Field.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diplom_domino.dir/Field/Field.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruslan/CLionProjects/diplom_domino/Field/Field.cpp -o CMakeFiles/diplom_domino.dir/Field/Field.cpp.s

# Object files for target diplom_domino
diplom_domino_OBJECTS = \
"CMakeFiles/diplom_domino.dir/main.cpp.o" \
"CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o" \
"CMakeFiles/diplom_domino.dir/Field/Field.cpp.o"

# External object files for target diplom_domino
diplom_domino_EXTERNAL_OBJECTS =

diplom_domino: CMakeFiles/diplom_domino.dir/main.cpp.o
diplom_domino: CMakeFiles/diplom_domino.dir/Cell/Cell.cpp.o
diplom_domino: CMakeFiles/diplom_domino.dir/Field/Field.cpp.o
diplom_domino: CMakeFiles/diplom_domino.dir/build.make
diplom_domino: CMakeFiles/diplom_domino.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruslan/CLionProjects/diplom_domino/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable diplom_domino"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/diplom_domino.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/diplom_domino.dir/build: diplom_domino
.PHONY : CMakeFiles/diplom_domino.dir/build

CMakeFiles/diplom_domino.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/diplom_domino.dir/cmake_clean.cmake
.PHONY : CMakeFiles/diplom_domino.dir/clean

CMakeFiles/diplom_domino.dir/depend:
	cd /home/ruslan/CLionProjects/diplom_domino/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruslan/CLionProjects/diplom_domino /home/ruslan/CLionProjects/diplom_domino /home/ruslan/CLionProjects/diplom_domino/cmake-build-debug /home/ruslan/CLionProjects/diplom_domino/cmake-build-debug /home/ruslan/CLionProjects/diplom_domino/cmake-build-debug/CMakeFiles/diplom_domino.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/diplom_domino.dir/depend

