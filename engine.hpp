#include <SDL2/SDL.h>
#include "game.hpp"

#define WINDOW_TITLE "Test title"
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 300


class Engine { //holds data about window and etc. there shouldnt be more than one, huh

private:
    SDL_Window *window;
    SDL_Surface *screen;

    Game game;
public:
    void    init();

    bool    checkInput();
    void    tick();
    void    render();

    void    quit();
};

