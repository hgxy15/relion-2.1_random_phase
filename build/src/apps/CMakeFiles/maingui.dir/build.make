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
include src/apps/CMakeFiles/maingui.dir/depend.make

# Include the progress variables for this target.
include src/apps/CMakeFiles/maingui.dir/progress.make

# Include the compile flags for this target's objects.
include src/apps/CMakeFiles/maingui.dir/flags.make

src/apps/CMakeFiles/maingui.dir/maingui.cpp.o: src/apps/CMakeFiles/maingui.dir/flags.make
src/apps/CMakeFiles/maingui.dir/maingui.cpp.o: ../src/apps/maingui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/apps/software/relion-2.1_gaoxing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/apps/CMakeFiles/maingui.dir/maingui.cpp.o"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/maingui.dir/maingui.cpp.o -c /apps/software/relion-2.1_gaoxing/src/apps/maingui.cpp

src/apps/CMakeFiles/maingui.dir/maingui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/maingui.dir/maingui.cpp.i"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /apps/software/relion-2.1_gaoxing/src/apps/maingui.cpp > CMakeFiles/maingui.dir/maingui.cpp.i

src/apps/CMakeFiles/maingui.dir/maingui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/maingui.dir/maingui.cpp.s"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /sddn/inspur/ompi31/bin/mpicxx $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /apps/software/relion-2.1_gaoxing/src/apps/maingui.cpp -o CMakeFiles/maingui.dir/maingui.cpp.s

# Object files for target maingui
maingui_OBJECTS = \
"CMakeFiles/maingui.dir/maingui.cpp.o"

# External object files for target maingui
maingui_EXTERNAL_OBJECTS =

bin/relion_maingui: src/apps/CMakeFiles/maingui.dir/maingui.cpp.o
bin/relion_maingui: src/apps/CMakeFiles/maingui.dir/build.make
bin/relion_maingui: lib/librelion_lib.so
bin/relion_maingui: ../external/fftw/lib/libfftw3.so
bin/relion_maingui: /usr/local/cuda/lib64/libcufft.so
bin/relion_maingui: /sddn/inspur/ompi31/lib/libmpi.so
bin/relion_maingui: lib/librelion_gpu_util.so
bin/relion_maingui: ../external/fltk/lib/libfltk.so
bin/relion_maingui: /usr/local/cuda/lib64/libcudart_static.a
bin/relion_maingui: /usr/lib64/librt.so
bin/relion_maingui: src/apps/CMakeFiles/maingui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/apps/software/relion-2.1_gaoxing/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/relion_maingui"
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/maingui.dir/link.txt --verbose=$(VERBOSE)
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/build/bin/relion_maingui /apps/software/relion-2.1_gaoxing/build/bin/relion
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && /apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/build/bin/relion_qsub.csh /apps/software/relion-2.1_gaoxing/build/bin/qsub.csh

# Rule to build all files generated by this target.
src/apps/CMakeFiles/maingui.dir/build: bin/relion_maingui

.PHONY : src/apps/CMakeFiles/maingui.dir/build

src/apps/CMakeFiles/maingui.dir/clean:
	cd /apps/software/relion-2.1_gaoxing/build/src/apps && $(CMAKE_COMMAND) -P CMakeFiles/maingui.dir/cmake_clean.cmake
.PHONY : src/apps/CMakeFiles/maingui.dir/clean

src/apps/CMakeFiles/maingui.dir/depend:
	cd /apps/software/relion-2.1_gaoxing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /apps/software/relion-2.1_gaoxing /apps/software/relion-2.1_gaoxing/src/apps /apps/software/relion-2.1_gaoxing/build /apps/software/relion-2.1_gaoxing/build/src/apps /apps/software/relion-2.1_gaoxing/build/src/apps/CMakeFiles/maingui.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/apps/CMakeFiles/maingui.dir/depend

