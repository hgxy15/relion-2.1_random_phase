# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /apps/software/cmake/3.13.2/bin/cmake

# The command to remove a file.
RM = /apps/software/cmake/3.13.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /apps/software/relion-2.1_gaoxing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /apps/software/relion-2.1_gaoxing/build

# Include any dependencies generated for this target.
include src/apps/CMakeFiles/preprocess.dir/depend.make

# Include the progress variables for this target.
include src/apps/CMakeFiles/preprocess.dir/progress.make

# Include the compile flags for this target's objects.
include src/apps/CMakeFiles/preprocess.dir/flags.make

src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.o: src/apps/CMakeFiles/preprocess.dir/flags.make
src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.o: ../src/apps/preprocess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/apps/software/relion-2.1_gaoxing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.o"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/preprocess.dir/preprocess.cpp.o -c /apps/software/relion-2.1_gaoxing/src/apps/preprocess.cpp

src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/preprocess.dir/preprocess.cpp.i"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /apps/software/relion-2.1_gaoxing/src/apps/preprocess.cpp > CMakeFiles/preprocess.dir/preprocess.cpp.i

src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/preprocess.dir/preprocess.cpp.s"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /apps/software/relion-2.1_gaoxing/src/apps/preprocess.cpp -o CMakeFiles/preprocess.dir/preprocess.cpp.s

# Object files for target preprocess
preprocess_OBJECTS = \
"CMakeFiles/preprocess.dir/preprocess.cpp.o"

# External object files for target preprocess
preprocess_EXTERNAL_OBJECTS =

bin/relion_preprocess: src/apps/CMakeFiles/preprocess.dir/preprocess.cpp.o
bin/relion_preprocess: src/apps/CMakeFiles/preprocess.dir/build.make
bin/relion_preprocess: lib/librelion_lib.so
bin/relion_preprocess: ../external/fftw/lib/libfftw3.so
bin/relion_preprocess: /usr/local/cuda/lib64/libcufft.so
bin/relion_preprocess: /sddn/inspur/ompi31/lib/libmpi.so
bin/relion_preprocess: lib/librelion_gpu_util.so
bin/relion_preprocess: ../external/fltk/lib/libfltk.so
bin/relion_preprocess: /usr/local/cuda/lib64/libcudart_static.a
bin/relion_preprocess: /usr/lib64/librt.so
bin/relion_preprocess: src/apps/CMakeFiles/preprocess.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/apps/software/relion-2.1_gaoxing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/relion_preprocess"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/preprocess.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/apps/CMakeFiles/preprocess.dir/build: bin/relion_preprocess

.PHONY : src/apps/CMakeFiles/preprocess.dir/build

src/apps/CMakeFiles/preprocess.dir/clean:
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && $(CMAKE_COMMAND) -P CMakeFiles/preprocess.dir/cmake_clean.cmake
.PHONY : src/apps/CMakeFiles/preprocess.dir/clean

src/apps/CMakeFiles/preprocess.dir/depend:
	cd /apps/software/relion-2.1_gaoxing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /apps/software/relion-2.1_gaoxing /apps/software/relion-2.1_gaoxing/src/apps /apps/software/relion-2.1_gaoxing/build /apps/software/relion-2.1_gaoxing/build/src/apps /apps/software/relion-2.1_gaoxing/build/src/apps/CMakeFiles/preprocess.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/apps/CMakeFiles/preprocess.dir/depend

