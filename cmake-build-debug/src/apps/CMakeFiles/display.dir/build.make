# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /software/clion-2017.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /software/clion-2017.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /software/relion-2.1_gaoxing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /software/relion-2.1_gaoxing/cmake-build-debug

# Include any dependencies generated for this target.
include src/apps/CMakeFiles/display.dir/depend.make

# Include the progress variables for this target.
include src/apps/CMakeFiles/display.dir/progress.make

# Include the compile flags for this target's objects.
include src/apps/CMakeFiles/display.dir/flags.make

src/apps/CMakeFiles/display.dir/display.cpp.o: src/apps/CMakeFiles/display.dir/flags.make
src/apps/CMakeFiles/display.dir/display.cpp.o: ../src/apps/display.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/software/relion-2.1_gaoxing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/apps/CMakeFiles/display.dir/display.cpp.o"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/display.dir/display.cpp.o -c /software/relion-2.1_gaoxing/src/apps/display.cpp

src/apps/CMakeFiles/display.dir/display.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/display.dir/display.cpp.i"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /software/relion-2.1_gaoxing/src/apps/display.cpp > CMakeFiles/display.dir/display.cpp.i

src/apps/CMakeFiles/display.dir/display.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/display.dir/display.cpp.s"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /software/relion-2.1_gaoxing/src/apps/display.cpp -o CMakeFiles/display.dir/display.cpp.s

src/apps/CMakeFiles/display.dir/display.cpp.o.requires:

.PHONY : src/apps/CMakeFiles/display.dir/display.cpp.o.requires

src/apps/CMakeFiles/display.dir/display.cpp.o.provides: src/apps/CMakeFiles/display.dir/display.cpp.o.requires
	$(MAKE) -f src/apps/CMakeFiles/display.dir/build.make src/apps/CMakeFiles/display.dir/display.cpp.o.provides.build
.PHONY : src/apps/CMakeFiles/display.dir/display.cpp.o.provides

src/apps/CMakeFiles/display.dir/display.cpp.o.provides.build: src/apps/CMakeFiles/display.dir/display.cpp.o


# Object files for target display
display_OBJECTS = \
"CMakeFiles/display.dir/display.cpp.o"

# External object files for target display
display_EXTERNAL_OBJECTS =

bin/relion_display: src/apps/CMakeFiles/display.dir/display.cpp.o
bin/relion_display: src/apps/CMakeFiles/display.dir/build.make
bin/relion_display: lib/librelion_lib.so
bin/relion_display: ../external/fftw/lib/libfftw3.so
bin/relion_display: /usr/local/cuda-8.0/lib64/libcufft.so
bin/relion_display: /usr/local/lib/libmpi_cxx.so
bin/relion_display: /usr/local/lib/libmpi.so
bin/relion_display: lib/librelion_gpu_util.so
bin/relion_display: ../external/fltk/lib/libfltk.so
bin/relion_display: /usr/local/cuda-8.0/lib64/libcudart_static.a
bin/relion_display: /usr/lib64/librt.so
bin/relion_display: src/apps/CMakeFiles/display.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/software/relion-2.1_gaoxing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/relion_display"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/display.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/apps/CMakeFiles/display.dir/build: bin/relion_display

.PHONY : src/apps/CMakeFiles/display.dir/build

src/apps/CMakeFiles/display.dir/requires: src/apps/CMakeFiles/display.dir/display.cpp.o.requires

.PHONY : src/apps/CMakeFiles/display.dir/requires

src/apps/CMakeFiles/display.dir/clean:
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && $(CMAKE_COMMAND) -P CMakeFiles/display.dir/cmake_clean.cmake
.PHONY : src/apps/CMakeFiles/display.dir/clean

src/apps/CMakeFiles/display.dir/depend:
	cd /software/relion-2.1_gaoxing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /software/relion-2.1_gaoxing /software/relion-2.1_gaoxing/src/apps /software/relion-2.1_gaoxing/cmake-build-debug /software/relion-2.1_gaoxing/cmake-build-debug/src/apps /software/relion-2.1_gaoxing/cmake-build-debug/src/apps/CMakeFiles/display.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/apps/CMakeFiles/display.dir/depend
