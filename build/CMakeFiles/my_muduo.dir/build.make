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
CMAKE_SOURCE_DIR = /root/houji_project/webserver/muduo-webserver/my_muduo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/houji_project/webserver/muduo-webserver/my_muduo/build

# Include any dependencies generated for this target.
include CMakeFiles/my_muduo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/my_muduo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/my_muduo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_muduo.dir/flags.make

CMakeFiles/my_muduo.dir/Channel.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Channel.cc.o: ../Channel.cc
CMakeFiles/my_muduo.dir/Channel.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_muduo.dir/Channel.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/Channel.cc.o -MF CMakeFiles/my_muduo.dir/Channel.cc.o.d -o CMakeFiles/my_muduo.dir/Channel.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/Channel.cc

CMakeFiles/my_muduo.dir/Channel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Channel.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/Channel.cc > CMakeFiles/my_muduo.dir/Channel.cc.i

CMakeFiles/my_muduo.dir/Channel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Channel.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/Channel.cc -o CMakeFiles/my_muduo.dir/Channel.cc.s

CMakeFiles/my_muduo.dir/CurrentThread.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/CurrentThread.cc.o: ../CurrentThread.cc
CMakeFiles/my_muduo.dir/CurrentThread.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_muduo.dir/CurrentThread.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/CurrentThread.cc.o -MF CMakeFiles/my_muduo.dir/CurrentThread.cc.o.d -o CMakeFiles/my_muduo.dir/CurrentThread.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/CurrentThread.cc

CMakeFiles/my_muduo.dir/CurrentThread.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/CurrentThread.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/CurrentThread.cc > CMakeFiles/my_muduo.dir/CurrentThread.cc.i

CMakeFiles/my_muduo.dir/CurrentThread.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/CurrentThread.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/CurrentThread.cc -o CMakeFiles/my_muduo.dir/CurrentThread.cc.s

CMakeFiles/my_muduo.dir/DefaultPoller.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/DefaultPoller.cc.o: ../DefaultPoller.cc
CMakeFiles/my_muduo.dir/DefaultPoller.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_muduo.dir/DefaultPoller.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/DefaultPoller.cc.o -MF CMakeFiles/my_muduo.dir/DefaultPoller.cc.o.d -o CMakeFiles/my_muduo.dir/DefaultPoller.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/DefaultPoller.cc

CMakeFiles/my_muduo.dir/DefaultPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/DefaultPoller.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/DefaultPoller.cc > CMakeFiles/my_muduo.dir/DefaultPoller.cc.i

CMakeFiles/my_muduo.dir/DefaultPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/DefaultPoller.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/DefaultPoller.cc -o CMakeFiles/my_muduo.dir/DefaultPoller.cc.s

CMakeFiles/my_muduo.dir/EpollPoller.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EpollPoller.cc.o: ../EpollPoller.cc
CMakeFiles/my_muduo.dir/EpollPoller.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_muduo.dir/EpollPoller.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/EpollPoller.cc.o -MF CMakeFiles/my_muduo.dir/EpollPoller.cc.o.d -o CMakeFiles/my_muduo.dir/EpollPoller.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/EpollPoller.cc

CMakeFiles/my_muduo.dir/EpollPoller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EpollPoller.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/EpollPoller.cc > CMakeFiles/my_muduo.dir/EpollPoller.cc.i

CMakeFiles/my_muduo.dir/EpollPoller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EpollPoller.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/EpollPoller.cc -o CMakeFiles/my_muduo.dir/EpollPoller.cc.s

CMakeFiles/my_muduo.dir/EventLoop.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/EventLoop.cc.o: ../EventLoop.cc
CMakeFiles/my_muduo.dir/EventLoop.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/my_muduo.dir/EventLoop.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/EventLoop.cc.o -MF CMakeFiles/my_muduo.dir/EventLoop.cc.o.d -o CMakeFiles/my_muduo.dir/EventLoop.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/EventLoop.cc

CMakeFiles/my_muduo.dir/EventLoop.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/EventLoop.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/EventLoop.cc > CMakeFiles/my_muduo.dir/EventLoop.cc.i

CMakeFiles/my_muduo.dir/EventLoop.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/EventLoop.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/EventLoop.cc -o CMakeFiles/my_muduo.dir/EventLoop.cc.s

CMakeFiles/my_muduo.dir/InetAddress.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/InetAddress.cc.o: ../InetAddress.cc
CMakeFiles/my_muduo.dir/InetAddress.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/my_muduo.dir/InetAddress.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/InetAddress.cc.o -MF CMakeFiles/my_muduo.dir/InetAddress.cc.o.d -o CMakeFiles/my_muduo.dir/InetAddress.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/InetAddress.cc

CMakeFiles/my_muduo.dir/InetAddress.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/InetAddress.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/InetAddress.cc > CMakeFiles/my_muduo.dir/InetAddress.cc.i

CMakeFiles/my_muduo.dir/InetAddress.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/InetAddress.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/InetAddress.cc -o CMakeFiles/my_muduo.dir/InetAddress.cc.s

CMakeFiles/my_muduo.dir/Log.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Log.cc.o: ../Log.cc
CMakeFiles/my_muduo.dir/Log.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/my_muduo.dir/Log.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/Log.cc.o -MF CMakeFiles/my_muduo.dir/Log.cc.o.d -o CMakeFiles/my_muduo.dir/Log.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/Log.cc

CMakeFiles/my_muduo.dir/Log.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Log.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/Log.cc > CMakeFiles/my_muduo.dir/Log.cc.i

CMakeFiles/my_muduo.dir/Log.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Log.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/Log.cc -o CMakeFiles/my_muduo.dir/Log.cc.s

CMakeFiles/my_muduo.dir/Poller.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Poller.cc.o: ../Poller.cc
CMakeFiles/my_muduo.dir/Poller.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/my_muduo.dir/Poller.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/Poller.cc.o -MF CMakeFiles/my_muduo.dir/Poller.cc.o.d -o CMakeFiles/my_muduo.dir/Poller.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/Poller.cc

CMakeFiles/my_muduo.dir/Poller.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Poller.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/Poller.cc > CMakeFiles/my_muduo.dir/Poller.cc.i

CMakeFiles/my_muduo.dir/Poller.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Poller.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/Poller.cc -o CMakeFiles/my_muduo.dir/Poller.cc.s

CMakeFiles/my_muduo.dir/Timestamp.cc.o: CMakeFiles/my_muduo.dir/flags.make
CMakeFiles/my_muduo.dir/Timestamp.cc.o: ../Timestamp.cc
CMakeFiles/my_muduo.dir/Timestamp.cc.o: CMakeFiles/my_muduo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/my_muduo.dir/Timestamp.cc.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/my_muduo.dir/Timestamp.cc.o -MF CMakeFiles/my_muduo.dir/Timestamp.cc.o.d -o CMakeFiles/my_muduo.dir/Timestamp.cc.o -c /root/houji_project/webserver/muduo-webserver/my_muduo/Timestamp.cc

CMakeFiles/my_muduo.dir/Timestamp.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_muduo.dir/Timestamp.cc.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/houji_project/webserver/muduo-webserver/my_muduo/Timestamp.cc > CMakeFiles/my_muduo.dir/Timestamp.cc.i

CMakeFiles/my_muduo.dir/Timestamp.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_muduo.dir/Timestamp.cc.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/houji_project/webserver/muduo-webserver/my_muduo/Timestamp.cc -o CMakeFiles/my_muduo.dir/Timestamp.cc.s

# Object files for target my_muduo
my_muduo_OBJECTS = \
"CMakeFiles/my_muduo.dir/Channel.cc.o" \
"CMakeFiles/my_muduo.dir/CurrentThread.cc.o" \
"CMakeFiles/my_muduo.dir/DefaultPoller.cc.o" \
"CMakeFiles/my_muduo.dir/EpollPoller.cc.o" \
"CMakeFiles/my_muduo.dir/EventLoop.cc.o" \
"CMakeFiles/my_muduo.dir/InetAddress.cc.o" \
"CMakeFiles/my_muduo.dir/Log.cc.o" \
"CMakeFiles/my_muduo.dir/Poller.cc.o" \
"CMakeFiles/my_muduo.dir/Timestamp.cc.o"

# External object files for target my_muduo
my_muduo_EXTERNAL_OBJECTS =

../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Channel.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/CurrentThread.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/DefaultPoller.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EpollPoller.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/EventLoop.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/InetAddress.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Log.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Poller.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/Timestamp.cc.o
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/build.make
../lib/libmy_muduo.so: CMakeFiles/my_muduo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX shared library ../lib/libmy_muduo.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_muduo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_muduo.dir/build: ../lib/libmy_muduo.so
.PHONY : CMakeFiles/my_muduo.dir/build

CMakeFiles/my_muduo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_muduo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_muduo.dir/clean

CMakeFiles/my_muduo.dir/depend:
	cd /root/houji_project/webserver/muduo-webserver/my_muduo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/houji_project/webserver/muduo-webserver/my_muduo /root/houji_project/webserver/muduo-webserver/my_muduo /root/houji_project/webserver/muduo-webserver/my_muduo/build /root/houji_project/webserver/muduo-webserver/my_muduo/build /root/houji_project/webserver/muduo-webserver/my_muduo/build/CMakeFiles/my_muduo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_muduo.dir/depend

