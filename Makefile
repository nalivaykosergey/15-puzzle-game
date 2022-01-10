CC = g++
CFLAGS=-Wall -c -Ilibs/SFML/include/
LFLAGS=-Llibs/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
SRCDIR = src
BINDIR = bin
SOURCES=main.cpp table.cpp watch.cpp game.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=game


all:
	@$(CC) $(CFLAGS) $(SOURCES:%=$(SRCDIR)/%)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $(BINDIR)/$(EXEC)
	@make clear

clear:
	@rm -rf *.o