
main: ./lux-lib/lib.hpp ./lux-lib/lib.o ./lux-lib/map_terminal.hpp ./lux-lib/map_terminal.o
	g++ -O0 -std=c++11 -o bot_002.out bot_002.cpp ./lux-lib/map_terminal.cpp ./lux-lib/lib.cpp -I. -I./lux-lib/

lib.o: ./lux-lib/lib.hpp ./lux-lib/lib.cpp ./lux-lib/map_terminal.cpp ./lux-lib/map_terminal.o
	g++ -c -o ./lux-lib/lib.o ./lux-lib/lib.cpp -I. -I./lux-lib/

map_terminal.o: ./lux-lib/map_terminal.hpp ./lux-lib/map_terminal.cpp
	g++ -c -o ./lux-lib/map_terminal.o ./lux-lib/map_terminal.cpp -I. -I./lux-lib/