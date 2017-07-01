#include "Game.h"

#include<iostream>

int main(int argc,char* args[]){
	Game g;
	
	if (g.initSDL() == true) {
		std::cout << "Init successful!" << std::endl;
		if (g.initGame() == true) {
			g.mainLoop();
			g.endGame();
		}
		return 0;
	}
}




