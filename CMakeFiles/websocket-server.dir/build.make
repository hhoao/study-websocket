# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hhoa/CLionProjects/embedded-final-homework

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hhoa/CLionProjects/embedded-final-homework

# Include any dependencies generated for this target.
include CMakeFiles/websocket-server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/websocket-server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/websocket-server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/websocket-server.dir/flags.make

CMakeFiles/websocket-server.dir/websocket-server/main.c.o: CMakeFiles/websocket-server.dir/flags.make
CMakeFiles/websocket-server.dir/websocket-server/main.c.o: websocket-server/main.c
CMakeFiles/websocket-server.dir/websocket-server/main.c.o: CMakeFiles/websocket-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/websocket-server.dir/websocket-server/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/websocket-server.dir/websocket-server/main.c.o -MF CMakeFiles/websocket-server.dir/websocket-server/main.c.o.d -o CMakeFiles/websocket-server.dir/websocket-server/main.c.o -c /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/main.c

CMakeFiles/websocket-server.dir/websocket-server/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/websocket-server.dir/websocket-server/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/main.c > CMakeFiles/websocket-server.dir/websocket-server/main.c.i

CMakeFiles/websocket-server.dir/websocket-server/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/websocket-server.dir/websocket-server/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/main.c -o CMakeFiles/websocket-server.dir/websocket-server/main.c.s

CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o: CMakeFiles/websocket-server.dir/flags.make
CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o: websocket-server/tcp_epoll.c
CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o: CMakeFiles/websocket-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o -MF CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o.d -o CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o -c /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_epoll.c

CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_epoll.c > CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.i

CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_epoll.c -o CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.s

CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o: CMakeFiles/websocket-server.dir/flags.make
CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o: websocket-server/tcp_ws.c
CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o: CMakeFiles/websocket-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o -MF CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o.d -o CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o -c /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_ws.c

CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_ws.c > CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.i

CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_ws.c -o CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.s

CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o: CMakeFiles/websocket-server.dir/flags.make
CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o: websocket-server/tcp_session.c
CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o: CMakeFiles/websocket-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o -MF CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o.d -o CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o -c /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_session.c

CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_session.c > CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.i

CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhoa/CLionProjects/embedded-final-homework/websocket-server/tcp_session.c -o CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.s

CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o: CMakeFiles/websocket-server.dir/flags.make
CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o: http-parser/http_parser.c
CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o: CMakeFiles/websocket-server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o -MF CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o.d -o CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o -c /home/hhoa/CLionProjects/embedded-final-homework/http-parser/http_parser.c

CMakeFiles/websocket-server.dir/http-parser/http_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/websocket-server.dir/http-parser/http_parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hhoa/CLionProjects/embedded-final-homework/http-parser/http_parser.c > CMakeFiles/websocket-server.dir/http-parser/http_parser.c.i

CMakeFiles/websocket-server.dir/http-parser/http_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/websocket-server.dir/http-parser/http_parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hhoa/CLionProjects/embedded-final-homework/http-parser/http_parser.c -o CMakeFiles/websocket-server.dir/http-parser/http_parser.c.s

# Object files for target websocket-server
websocket__server_OBJECTS = \
"CMakeFiles/websocket-server.dir/websocket-server/main.c.o" \
"CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o" \
"CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o" \
"CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o" \
"CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o"

# External object files for target websocket-server
websocket__server_EXTERNAL_OBJECTS =

websocket-server: CMakeFiles/websocket-server.dir/websocket-server/main.c.o
websocket-server: CMakeFiles/websocket-server.dir/websocket-server/tcp_epoll.c.o
websocket-server: CMakeFiles/websocket-server.dir/websocket-server/tcp_ws.c.o
websocket-server: CMakeFiles/websocket-server.dir/websocket-server/tcp_session.c.o
websocket-server: CMakeFiles/websocket-server.dir/http-parser/http_parser.c.o
websocket-server: CMakeFiles/websocket-server.dir/build.make
websocket-server: b64/libb64c.so
websocket-server: CMakeFiles/websocket-server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable websocket-server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/websocket-server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/websocket-server.dir/build: websocket-server
.PHONY : CMakeFiles/websocket-server.dir/build

CMakeFiles/websocket-server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/websocket-server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/websocket-server.dir/clean

CMakeFiles/websocket-server.dir/depend:
	cd /home/hhoa/CLionProjects/embedded-final-homework && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hhoa/CLionProjects/embedded-final-homework /home/hhoa/CLionProjects/embedded-final-homework /home/hhoa/CLionProjects/embedded-final-homework /home/hhoa/CLionProjects/embedded-final-homework /home/hhoa/CLionProjects/embedded-final-homework/CMakeFiles/websocket-server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/websocket-server.dir/depend

