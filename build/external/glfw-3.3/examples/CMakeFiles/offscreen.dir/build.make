# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lyy/workspace/Cpp/cg_learning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lyy/workspace/Cpp/cg_learning/build

# Include any dependencies generated for this target.
include external/glfw-3.3/examples/CMakeFiles/offscreen.dir/depend.make

# Include the progress variables for this target.
include external/glfw-3.3/examples/CMakeFiles/offscreen.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.3/examples/CMakeFiles/offscreen.dir/flags.make

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.o: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/flags.make
external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.o: ../external/glfw-3.3/examples/offscreen.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyy/workspace/Cpp/cg_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.o"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/offscreen.dir/offscreen.c.o   -c /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/examples/offscreen.c

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/offscreen.c.i"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/examples/offscreen.c > CMakeFiles/offscreen.dir/offscreen.c.i

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/offscreen.c.s"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/examples/offscreen.c -o CMakeFiles/offscreen.dir/offscreen.c.s

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/flags.make
external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o: ../external/glfw-3.3/deps/glad_gl.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lyy/workspace/Cpp/cg_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o   -c /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/deps/glad_gl.c

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/deps/glad_gl.c > CMakeFiles/offscreen.dir/__/deps/glad_gl.c.i

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/deps/glad_gl.c -o CMakeFiles/offscreen.dir/__/deps/glad_gl.c.s

# Object files for target offscreen
offscreen_OBJECTS = \
"CMakeFiles/offscreen.dir/offscreen.c.o" \
"CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o"

# External object files for target offscreen
offscreen_EXTERNAL_OBJECTS =

external/glfw-3.3/examples/offscreen: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/offscreen.c.o
external/glfw-3.3/examples/offscreen: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/__/deps/glad_gl.c.o
external/glfw-3.3/examples/offscreen: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/build.make
external/glfw-3.3/examples/offscreen: external/glfw-3.3/src/libglfw3.a
external/glfw-3.3/examples/offscreen: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.3/examples/offscreen: /usr/lib/x86_64-linux-gnu/librt.so
external/glfw-3.3/examples/offscreen: /usr/lib/x86_64-linux-gnu/libm.so
external/glfw-3.3/examples/offscreen: /usr/lib/x86_64-linux-gnu/libX11.so
external/glfw-3.3/examples/offscreen: external/glfw-3.3/examples/CMakeFiles/offscreen.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lyy/workspace/Cpp/cg_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable offscreen"
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/offscreen.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.3/examples/CMakeFiles/offscreen.dir/build: external/glfw-3.3/examples/offscreen

.PHONY : external/glfw-3.3/examples/CMakeFiles/offscreen.dir/build

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/clean:
	cd /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples && $(CMAKE_COMMAND) -P CMakeFiles/offscreen.dir/cmake_clean.cmake
.PHONY : external/glfw-3.3/examples/CMakeFiles/offscreen.dir/clean

external/glfw-3.3/examples/CMakeFiles/offscreen.dir/depend:
	cd /home/lyy/workspace/Cpp/cg_learning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lyy/workspace/Cpp/cg_learning /home/lyy/workspace/Cpp/cg_learning/external/glfw-3.3/examples /home/lyy/workspace/Cpp/cg_learning/build /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples /home/lyy/workspace/Cpp/cg_learning/build/external/glfw-3.3/examples/CMakeFiles/offscreen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.3/examples/CMakeFiles/offscreen.dir/depend

