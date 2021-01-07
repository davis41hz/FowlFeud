make:
	g++ *.cpp -w `sdl2-config --libs` -lSDL2_mixer
