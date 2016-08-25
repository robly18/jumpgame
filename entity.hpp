#include <SDL2/SDL.h>

#define GAME_FLOOR 130
#define GAME_CEIL 30

#define PLAYERSIZE 30
#define PLAYERX 50
//todo move these to a const header file

class Entity {
    SDL_Rect    rect;
public:
                Entity();
                Entity(float x, float y, int w, int h, int color = 0xFFFF00);

    void        render(SDL_Surface*);
    bool        onScreen();
    
    void        move(float velocity, int deltat);
    bool        checkCollisionWithPlayer(float);

    float       x, y;
    int         w, h;

    int         color = 0xFFFF00;
};

enum class EType {
    TOPSMALL, BOTSMALL,
    TOPBUMP,  BOTBUMP
};

class QueuedEntity {
    EType type;
    int time;
public:
    QueuedEntity(int tzero, int time, EType type);
    Entity      make();

    bool        ready(int time);

    const float startx = 600;
};
