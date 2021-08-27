main.exe: main.o Game.o Timer.o Pse.o
	g++ -o main.exe main.cpp Game.o Timer.o Pse.o -lncurses

main.o: main.cpp Game.h Timer.h
	g++ -c main.cpp -lncurses

Game.o: Game.cpp Game.h
	g++ -c Game.cpp -lncurses

Timer.o: Timer.cpp Timer.h
	g++ -c Timer.cpp -lncurses

Pse.o: Pse.cpp Pse.h
	g++ -c Pse.cpp -lncurses
clean:
	rm *.o
