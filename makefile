CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf
output: main.o readGameInfo.o model.o gameEngine.o rsdl.o
	g++ main.o readGameInfo.o model.o gameEngine.o rsdl.o $(CCFLAGS) -o   output

main.o: main.cpp
	g++ -c main.cpp

readGameInfo.o: readGameInfo.cpp readGameInfo.h
	g++ -c readGameInfo.cpp

model.o: model.cpp model.h
	g++ -c model.cpp

gameEngine.o: gameEngine.cpp gameEngine.h
	g++ -c gameEngine.cpp

rsdl.o: rsdl.cpp rsdl.hpp
	g++ -c rsdl.cpp

clean:
	rm *.o output