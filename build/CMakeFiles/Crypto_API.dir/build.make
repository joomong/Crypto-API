# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.25.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/joomong/project/Crypto-API

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/joomong/project/Crypto-API/build

# Include any dependencies generated for this target.
include CMakeFiles/Crypto_API.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Crypto_API.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Crypto_API.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Crypto_API.dir/flags.make

CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o: CMakeFiles/Crypto_API.dir/flags.make
CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o: /Users/joomong/project/Crypto-API/rest/src/binance.cpp
CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o: CMakeFiles/Crypto_API.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joomong/project/Crypto-API/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o -MF CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o.d -o CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o -c /Users/joomong/project/Crypto-API/rest/src/binance.cpp

CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joomong/project/Crypto-API/rest/src/binance.cpp > CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.i

CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joomong/project/Crypto-API/rest/src/binance.cpp -o CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.s

CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o: CMakeFiles/Crypto_API.dir/flags.make
CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o: /Users/joomong/project/Crypto-API/rest/src/exchange.cpp
CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o: CMakeFiles/Crypto_API.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joomong/project/Crypto-API/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o -MF CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o.d -o CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o -c /Users/joomong/project/Crypto-API/rest/src/exchange.cpp

CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joomong/project/Crypto-API/rest/src/exchange.cpp > CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.i

CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joomong/project/Crypto-API/rest/src/exchange.cpp -o CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.s

CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o: CMakeFiles/Crypto_API.dir/flags.make
CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o: /Users/joomong/project/Crypto-API/rest/test/test-binance.cpp
CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o: CMakeFiles/Crypto_API.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/joomong/project/Crypto-API/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o -MF CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o.d -o CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o -c /Users/joomong/project/Crypto-API/rest/test/test-binance.cpp

CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/joomong/project/Crypto-API/rest/test/test-binance.cpp > CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.i

CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/joomong/project/Crypto-API/rest/test/test-binance.cpp -o CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.s

# Object files for target Crypto_API
Crypto_API_OBJECTS = \
"CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o" \
"CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o" \
"CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o"

# External object files for target Crypto_API
Crypto_API_EXTERNAL_OBJECTS =

Crypto_API: CMakeFiles/Crypto_API.dir/rest/src/binance.cpp.o
Crypto_API: CMakeFiles/Crypto_API.dir/rest/src/exchange.cpp.o
Crypto_API: CMakeFiles/Crypto_API.dir/rest/test/test-binance.cpp.o
Crypto_API: CMakeFiles/Crypto_API.dir/build.make
Crypto_API: /opt/homebrew/opt/curl/lib/libcurl.dylib
Crypto_API: /opt/homebrew/opt/openssl@1.1/lib/libssl.dylib
Crypto_API: CMakeFiles/Crypto_API.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/joomong/project/Crypto-API/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Crypto_API"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Crypto_API.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Crypto_API.dir/build: Crypto_API
.PHONY : CMakeFiles/Crypto_API.dir/build

CMakeFiles/Crypto_API.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Crypto_API.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Crypto_API.dir/clean

CMakeFiles/Crypto_API.dir/depend:
	cd /Users/joomong/project/Crypto-API/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/joomong/project/Crypto-API /Users/joomong/project/Crypto-API /Users/joomong/project/Crypto-API/build /Users/joomong/project/Crypto-API/build /Users/joomong/project/Crypto-API/build/CMakeFiles/Crypto_API.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Crypto_API.dir/depend
