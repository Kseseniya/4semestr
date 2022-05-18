OBJ = Main.o Pacman.o MapCollision.o DrawMap.o ConvertSketch.o
PROG = pacman
LIBS =-lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS +=-Wall -Wextra -g -std=c++17

$(PROG): $(OBJ)
	$(CXX) -o $(PROG) $(OBJ) $(LIBS)

clean:
	-rm *.o

depend:
	$(CXX) -MM $(OBJ:.o=.cc) > .depend
-include .depend