# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/tranmachsohan/Desktop/Store

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/tranmachsohan/Desktop/Store/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Store.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Store.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Store.dir/flags.make

CMakeFiles/Store.dir/main.cpp.o: CMakeFiles/Store.dir/flags.make
CMakeFiles/Store.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tranmachsohan/Desktop/Store/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Store.dir/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Store.dir/main.cpp.o -c /Users/tranmachsohan/Desktop/Store/main.cpp

CMakeFiles/Store.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Store.dir/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tranmachsohan/Desktop/Store/main.cpp > CMakeFiles/Store.dir/main.cpp.i

CMakeFiles/Store.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Store.dir/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tranmachsohan/Desktop/Store/main.cpp -o CMakeFiles/Store.dir/main.cpp.s

CMakeFiles/Store.dir/item.cpp.o: CMakeFiles/Store.dir/flags.make
CMakeFiles/Store.dir/item.cpp.o: ../item.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/tranmachsohan/Desktop/Store/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Store.dir/item.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Store.dir/item.cpp.o -c /Users/tranmachsohan/Desktop/Store/item.cpp

CMakeFiles/Store.dir/item.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Store.dir/item.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/tranmachsohan/Desktop/Store/item.cpp > CMakeFiles/Store.dir/item.cpp.i

CMakeFiles/Store.dir/item.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Store.dir/item.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/tranmachsohan/Desktop/Store/item.cpp -o CMakeFiles/Store.dir/item.cpp.s

# Object files for target Store
Store_OBJECTS = \
"CMakeFiles/Store.dir/main.cpp.o" \
"CMakeFiles/Store.dir/item.cpp.o"

# External object files for target Store
Store_EXTERNAL_OBJECTS =

Store: CMakeFiles/Store.dir/main.cpp.o
Store: CMakeFiles/Store.dir/item.cpp.o
Store: CMakeFiles/Store.dir/build.make
Store: CMakeFiles/Store.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/tranmachsohan/Desktop/Store/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Store"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Store.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Store.dir/build: Store

.PHONY : CMakeFiles/Store.dir/build

CMakeFiles/Store.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Store.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Store.dir/clean

CMakeFiles/Store.dir/depend:
	cd /Users/tranmachsohan/Desktop/Store/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/tranmachsohan/Desktop/Store /Users/tranmachsohan/Desktop/Store /Users/tranmachsohan/Desktop/Store/cmake-build-debug /Users/tranmachsohan/Desktop/Store/cmake-build-debug /Users/tranmachsohan/Desktop/Store/cmake-build-debug/CMakeFiles/Store.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Store.dir/depend

