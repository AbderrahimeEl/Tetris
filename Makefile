all:
	g++ -g src/*.cpp -Iinclude -o bin/tetris.exe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11