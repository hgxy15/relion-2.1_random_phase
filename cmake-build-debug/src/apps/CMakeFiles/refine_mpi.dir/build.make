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
include src/apps/CMakeFiles/refine_mpi.dir/depend.make

# Include the progress variables for this target.
include src/apps/CMakeFiles/refine_mpi.dir/progress.make

# Include the compile flags for this target's objects.
include src/apps/CMakeFiles/refine_mpi.dir/flags.make

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o: src/apps/CMakeFiles/refine_mpi.dir/flags.make
src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o: ../src/apps/refine_mpi.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/software/relion-2.1_gaoxing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o -c /software/relion-2.1_gaoxing/src/apps/refine_mpi.cpp

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/refine_mpi.dir/refine_mpi.cpp.i"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /software/relion-2.1_gaoxing/src/apps/refine_mpi.cpp > CMakeFiles/refine_mpi.dir/refine_mpi.cpp.i

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/refine_mpi.dir/refine_mpi.cpp.s"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && /usr/local/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /software/relion-2.1_gaoxing/src/apps/refine_mpi.cpp -o CMakeFiles/refine_mpi.dir/refine_mpi.cpp.s

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.requires:

.PHONY : src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.requires

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.provides: src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.requires
	$(MAKE) -f src/apps/CMakeFiles/refine_mpi.dir/build.make src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.provides.build
.PHONY : src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.provides

src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.provides.build: src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o


# Object files for target refine_mpi
refine_mpi_OBJECTS = \
"CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o"

# External object files for target refine_mpi
refine_mpi_EXTERNAL_OBJECTS =

bin/relion_refine_mpi: src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o
bin/relion_refine_mpi: src/apps/CMakeFiles/refine_mpi.dir/build.make
bin/relion_refine_mpi: lib/librelion_lib.so
bin/relion_refine_mpi: ../external/fftw/lib/libfftw3.so
bin/relion_refine_mpi: /usr/local/cuda-8.0/lib64/libcufft.so
bin/relion_refine_mpi: /usr/local/lib/libmpi_cxx.so
bin/relion_refine_mpi: /usr/local/lib/libmpi.so
bin/relion_refine_mpi: lib/librelion_gpu_util.so
bin/relion_refine_mpi: ../external/fltk/lib/libfltk.so
bin/relion_refine_mpi: /usr/local/cuda-8.0/lib64/libcudart_static.a
bin/relion_refine_mpi: /usr/lib64/librt.so
bin/relion_refine_mpi: src/apps/CMakeFiles/refine_mpi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/software/relion-2.1_gaoxing/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/relion_refine_mpi"
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/refine_mpi.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/apps/CMakeFiles/refine_mpi.dir/build: bin/relion_refine_mpi

.PHONY : src/apps/CMakeFiles/refine_mpi.dir/build

src/apps/CMakeFiles/refine_mpi.dir/requires: src/apps/CMakeFiles/refine_mpi.dir/refine_mpi.cpp.o.requires

.PHONY : src/apps/CMakeFiles/refine_mpi.dir/requires

src/apps/CMakeFiles/refine_mpi.dir/clean:
	cd /software/relion-2.1_gaoxing/cmake-build-debug/src/apps && $(CMAKE_COMMAND) -P CMakeFiles/refine_mpi.dir/cmake_clean.cmake
.PHONY : src/apps/CMakeFiles/refine_mpi.dir/clean

src/apps/CMakeFiles/refine_mpi.dir/depend:
	cd /software/relion-2.1_gaoxing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /software/relion-2.1_gaoxing /software/relion-2.1_gaoxing/src/apps /software/relion-2.1_gaoxing/cmake-build-debug /software/relion-2.1_gaoxing/cmake-build-debug/src/apps /software/relion-2.1_gaoxing/cmake-build-debug/src/apps/CMakeFiles/refine_mpi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/apps/CMakeFiles/refine_mpi.dir/depend

