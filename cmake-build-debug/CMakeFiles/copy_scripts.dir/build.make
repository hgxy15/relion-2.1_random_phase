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

# Utility rule file for copy_scripts.

# Include the progress variables for this target.
include CMakeFiles/copy_scripts.dir/progress.make

copy_scripts: CMakeFiles/copy_scripts.dir/build.make
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_printtable /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_printtable
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_plottable /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_plottable
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_loopheader /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_loopheader
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_datablock_stack /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_datablock_stack
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_datablock_singlefiles /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_datablock_singlefiles
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/star_datablock_ctfdat /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_star_datablock_ctfdat
	/software/clion-2017.3.1/bin/cmake/bin/cmake -E copy /software/relion-2.1_gaoxing/scripts/qsub.csh /software/relion-2.1_gaoxing/cmake-build-debug/bin/relion_qsub.csh
.PHONY : copy_scripts

# Rule to build all files generated by this target.
CMakeFiles/copy_scripts.dir/build: copy_scripts

.PHONY : CMakeFiles/copy_scripts.dir/build

CMakeFiles/copy_scripts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/copy_scripts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/copy_scripts.dir/clean

CMakeFiles/copy_scripts.dir/depend:
	cd /software/relion-2.1_gaoxing/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /software/relion-2.1_gaoxing /software/relion-2.1_gaoxing /software/relion-2.1_gaoxing/cmake-build-debug /software/relion-2.1_gaoxing/cmake-build-debug /software/relion-2.1_gaoxing/cmake-build-debug/CMakeFiles/copy_scripts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/copy_scripts.dir/depend

