SOURCES=$(wildcard src/*.cpp)
OBJS=$(SOURCES:.cpp=.o)
CC=g++
INC=-Iinclude
# compiler options : add debug information in debug mode
# optimize speed and size in release mode
ifneq (,$(findstring debug,$(MAKECMDGOALS)))
	CFLAGS=-g
else
	CFLAGS=-O2 -s
endif

# linker options : OS dependant
#ifeq ($(shell sh -c 'uname -s'),Linux)
#	LIBFLAGS=-L. -ltcod_debug -ltcodxx_debug -Wl,-rpath=.
#else
#	LIBFLAGS=-Llib -ltcod-mingw-debug -static-libgcc -static-libstdc++ -mwindows
#endif
LIBFLAGS=-L. -ltcod -ltcodxx

debug : roguehacker
release : roguehacker

roguehacker : $(OBJS)
	$(CC) $(OBJS) -o roguehacker $(INC) -Wall $(LIBFLAGS) $(CFLAGS)

src/main.hpp.gch : include/*.hpp
	$(CC) include/main.hpp $(INC) -Wall

src/%.o : src/%.cpp include/main.hpp.gch
	$(CC) $< -c -o $@ $(INC) -Wall $(CFLAGS)

clean :
	rm -f include/main.hpp.gch $(OBJS)