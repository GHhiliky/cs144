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
CMAKE_SOURCE_DIR = /home/acat/sponge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/acat/sponge/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/fsm_stream_reassembler_single.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/fsm_stream_reassembler_single.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/fsm_stream_reassembler_single.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/fsm_stream_reassembler_single.dir/flags.make

tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o: tests/CMakeFiles/fsm_stream_reassembler_single.dir/flags.make
tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o: ../tests/fsm_stream_reassembler_single.cc
tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o: tests/CMakeFiles/fsm_stream_reassembler_single.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/acat/sponge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o"
	cd /home/acat/sponge/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o -MF CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o.d -o CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o -c /home/acat/sponge/tests/fsm_stream_reassembler_single.cc

tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.i"
	cd /home/acat/sponge/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/acat/sponge/tests/fsm_stream_reassembler_single.cc > CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.i

tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.s"
	cd /home/acat/sponge/build/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/acat/sponge/tests/fsm_stream_reassembler_single.cc -o CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.s

# Object files for target fsm_stream_reassembler_single
fsm_stream_reassembler_single_OBJECTS = \
"CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o"

# External object files for target fsm_stream_reassembler_single
fsm_stream_reassembler_single_EXTERNAL_OBJECTS =

tests/fsm_stream_reassembler_single: tests/CMakeFiles/fsm_stream_reassembler_single.dir/fsm_stream_reassembler_single.cc.o
tests/fsm_stream_reassembler_single: tests/CMakeFiles/fsm_stream_reassembler_single.dir/build.make
tests/fsm_stream_reassembler_single: tests/libspongechecks.a
tests/fsm_stream_reassembler_single: libsponge/libsponge.a
tests/fsm_stream_reassembler_single: tests/CMakeFiles/fsm_stream_reassembler_single.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/acat/sponge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fsm_stream_reassembler_single"
	cd /home/acat/sponge/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fsm_stream_reassembler_single.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/fsm_stream_reassembler_single.dir/build: tests/fsm_stream_reassembler_single
.PHONY : tests/CMakeFiles/fsm_stream_reassembler_single.dir/build

tests/CMakeFiles/fsm_stream_reassembler_single.dir/clean:
	cd /home/acat/sponge/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/fsm_stream_reassembler_single.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/fsm_stream_reassembler_single.dir/clean

tests/CMakeFiles/fsm_stream_reassembler_single.dir/depend:
	cd /home/acat/sponge/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/acat/sponge /home/acat/sponge/tests /home/acat/sponge/build /home/acat/sponge/build/tests /home/acat/sponge/build/tests/CMakeFiles/fsm_stream_reassembler_single.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/fsm_stream_reassembler_single.dir/depend

