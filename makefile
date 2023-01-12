all:
	g++ -c source/scene.cpp -I includes -o build/scene.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	g++ -c source/gui.cpp -I includes -o build/gui.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

	g++ -c source/collide.cpp -I includes -o build/collide.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	g++ -c source/game.cpp -I includes -o build/game.o -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	
	g++ source/main.cpp -I includes build/*.o -o build/flappy -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
	rm -r build/*.o
