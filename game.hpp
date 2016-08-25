#include <SDL2/SDL.h>
#include "entity.hpp"
#include <vector>
#include <queue>
#include <deque>
#include <random>

enum class Message {
    JUMP,
    LOST
};

class Game {
    int     lastTick;

    int     gravity = 1; //1 down, -1 up
    float   airpos = 0;
    bool    grounded = false;

    Entity  player;

    const static int floor = GAME_FLOOR;
    const static int ceiling = GAME_CEIL;
    float   velocity = 0.6;

    float   obstaclex = 800;

    std::queue<QueuedEntity>
            queued;
    std::deque<Entity>
            onScreen;
public:
    void    init(int time);

    void    tick(int time);
    void    render(SDL_Surface*);
    
    void    sendMessage(Message, int = 0);

    void    restart(int);
};

void makeLevel(std::queue<QueuedEntity>&, int);
