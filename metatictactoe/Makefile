CC = g++
LD = g++
CPPFLAGS = -std=c++0x -g -Wall -pedantic
LDFLAGS =

# Add any extra .cpp files to this line to
# have them compiled automatically.
SRCS = metatictactoe.cpp metagame.cpp metaboard.cpp board.cpp game.cpp

OBJS = $(SRCS:.cpp=.o)

all: metatictactoe

metatictactoe: $(OBJS)
	g++ -o $@ $^ $(LDFLAGS)

%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean :
	rm -f metatictactoe *.o
