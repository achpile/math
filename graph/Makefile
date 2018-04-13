PROJECT     = graph
CC          = g++
STRIP       = strip
CLEAN       = rm -f
MAKE        = make -j8 --no-print-directory
INCLUDE_DIR = $(PWD)/include
OBJS        = $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))

LDFLAGS     = -static-libstdc++ \
              -static-libgcc    \
              -lsfml-graphics   \
              -lsfml-window     \
              -lsfml-audio      \
              -lsfml-system

CFLAGS      = -Wall                 \
              -Wextra               \
              -std=c++11            \
              -I$(INCLUDE_DIR)


all:
	$(MAKE) $(PROJECT)


$(PROJECT): $(OBJS)
	$(CC) $(OBJS) -o $(PROJECT) $(LDFLAGS)
	$(STRIP) $(PROJECT)


.cpp.o:
	$(CC) $(CFLAGS) -o $@ -c $<


clean:
	$(CLEAN) $(OBJS) $(PROJECT)
