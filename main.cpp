#include <iostream>
#include <SDL2/SDL.h>
#include "engine.hpp"



int main(int argc, char *argv[]) {
    Engine engine;

    engine.init();

    while (engine.checkInput()) {
        engine.tick();
        engine.render();
    }

    engine.quit();

}
