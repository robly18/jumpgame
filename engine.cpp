#include "engine.hpp"

void Engine::init() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    screen = SDL_GetWindowSurface(window);
    game.init(SDL_GetTicks());
}

bool Engine::checkInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN: //todo prevent just holding
                if (e.key.keysym.sym == SDLK_SPACE) {
                    game.sendMessage(Message::JUMP);
                }
            default:
                //... do stuff
            break;
        }
    } 

    return true;
}

void Engine::tick() {
    game.tick(SDL_GetTicks());
}

void Engine::render() {
    SDL_FillRect(screen, NULL, 0x0000FF);
    game.render(screen);
    SDL_UpdateWindowSurface(window);
}

void Engine::quit() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}
