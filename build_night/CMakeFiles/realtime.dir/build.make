# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zhou/Desktop/code/git/ctp_trader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zhou/Desktop/code/git/ctp_trader/build_night

# Include any dependencies generated for this target.
include CMakeFiles/realtime.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/realtime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/realtime.dir/flags.make

CMakeFiles/realtime.dir/src/tools/realtime.cpp.o: CMakeFiles/realtime.dir/flags.make
CMakeFiles/realtime.dir/src/tools/realtime.cpp.o: ../src/tools/realtime.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zhou/Desktop/code/git/ctp_trader/build_night/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/realtime.dir/src/tools/realtime.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/realtime.dir/src/tools/realtime.cpp.o -c /home/zhou/Desktop/code/git/ctp_trader/src/tools/realtime.cpp

CMakeFiles/realtime.dir/src/tools/realtime.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/realtime.dir/src/tools/realtime.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zhou/Desktop/code/git/ctp_trader/src/tools/realtime.cpp > CMakeFiles/realtime.dir/src/tools/realtime.cpp.i

CMakeFiles/realtime.dir/src/tools/realtime.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/realtime.dir/src/tools/realtime.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zhou/Desktop/code/git/ctp_trader/src/tools/realtime.cpp -o CMakeFiles/realtime.dir/src/tools/realtime.cpp.s

# Object files for target realtime
realtime_OBJECTS = \
"CMakeFiles/realtime.dir/src/tools/realtime.cpp.o"

# External object files for target realtime
realtime_EXTERNAL_OBJECTS =

realtime: CMakeFiles/realtime.dir/src/tools/realtime.cpp.o
realtime: CMakeFiles/realtime.dir/build.make
realtime: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
realtime: CMakeFiles/realtime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zhou/Desktop/code/git/ctp_trader/build_night/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable realtime"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/realtime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/realtime.dir/build: realtime

.PHONY : CMakeFiles/realtime.dir/build

CMakeFiles/realtime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/realtime.dir/cmake_clean.cmake
.PHONY : CMakeFiles/realtime.dir/clean

CMakeFiles/realtime.dir/depend:
	cd /home/zhou/Desktop/code/git/ctp_trader/build_night && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zhou/Desktop/code/git/ctp_trader /home/zhou/Desktop/code/git/ctp_trader /home/zhou/Desktop/code/git/ctp_trader/build_night /home/zhou/Desktop/code/git/ctp_trader/build_night /home/zhou/Desktop/code/git/ctp_trader/build_night/CMakeFiles/realtime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/realtime.dir/depend

