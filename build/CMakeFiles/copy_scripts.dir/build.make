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

# Utility rule file for copy_scripts.

# Include the progress variables for this target.
include CMakeFiles/copy_scripts.dir/progress.make

copy_scripts: CMakeFiles/copy_scripts.dir/build.make
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_printtable /apps/software/relion-2.1_gaoxing/build/bin/relion_star_printtable
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_plottable /apps/software/relion-2.1_gaoxing/build/bin/relion_star_plottable
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_loopheader /apps/software/relion-2.1_gaoxing/build/bin/relion_star_loopheader
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_datablock_stack /apps/software/relion-2.1_gaoxing/build/bin/relion_star_datablock_stack
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_datablock_singlefiles /apps/software/relion-2.1_gaoxing/build/bin/relion_star_datablock_singlefiles
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/star_datablock_ctfdat /apps/software/relion-2.1_gaoxing/build/bin/relion_star_datablock_ctfdat
	/apps/software/cmake/3.13.2/bin/cmake -E copy /apps/software/relion-2.1_gaoxing/scripts/qsub.csh /apps/software/relion-2.1_gaoxing/build/bin/relion_qsub.csh
.PHONY : copy_scripts

# Rule to build all files generated by this target.
CMakeFiles/copy_scripts.dir/build: copy_scripts

.PHONY : CMakeFiles/copy_scripts.dir/build

CMakeFiles/copy_scripts.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/copy_scripts.dir/cmake_clean.cmake
.PHONY : CMakeFiles/copy_scripts.dir/clean

CMakeFiles/copy_scripts.dir/depend:
	cd /apps/software/relion-2.1_gaoxing/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /apps/software/relion-2.1_gaoxing /apps/software/relion-2.1_gaoxing /apps/software/relion-2.1_gaoxing/build /apps/software/relion-2.1_gaoxing/build /apps/software/relion-2.1_gaoxing/build/CMakeFiles/copy_scripts.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/copy_scripts.dir/depend
