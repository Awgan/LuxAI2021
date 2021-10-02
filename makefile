
main: ./lux-lib/lib.hpp ./lux-lib/lib.o ./lux-lib/map_terminal.hpp ./lux-lib/map_terminal.o
	g++ -O3 -std=c++11 -o main.out bot_002.cpp ./lux-lib/map_terminal.o ./lux-lib/lib.o ./lux-lib/mission_register.o -I. -I./lux-lib/

lib.o: ./lux-lib/lib.hpp ./lux-lib/lib.cpp ./lux-lib/map_terminal.cpp ./lux-lib/map_terminal.o
	g++ -c -o ./lux-lib/lib.o ./lux-lib/lib.cpp -I. -I./lux-lib/

map_terminal.o: ./lux-lib/map_terminal.hpp ./lux-lib/map_terminal.cpp
	g++ -c -o ./lux-lib/map_terminal.o ./lux-lib/map_terminal.cpp -I. -I./lux-lib/
	
mission_register.o: ./lux-lib/mission_register.hpp ./lux-lib/mission_register.cpp
	g++ -c -o ./lux-lib/mission_register.o ./lux-lib/mission_register.cpp

clean:
	rm lux-lib/*.s lux-lib/*.o lux-lib/*.gch *.s replays/* errorlogs/* submission.tar.gz lux/*.s lux/*.gch
