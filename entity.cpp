#include "entity.hpp"

Entity::Entity() {

}

Entity::Entity(float x, float y, int w, int h, int color) :
    x(x), y(y), w(w), h(h), color(color) {
    rect = {(int) x, (int) y, w, h};
}

void Entity::render(SDL_Surface *screen) {
    rect.x = (int) x; rect.y = (int) y;
    rect.w = w;       rect.h = h;
    SDL_FillRect(screen, &rect, color);
}

bool Entity::onScreen() {
    return x+w > 0;
}

void Entity::move(float velocity, int deltat) {
    x -= velocity * deltat;
}

bool Entity::checkCollisionWithPlayer(float playery) {
    if (x > PLAYERX + PLAYERSIZE) return false;
    if (x + w < PLAYERX) return false;
    if (playery > y + h) return false;
    if (playery + PLAYERSIZE < y) return false;
    return true;
}

QueuedEntity::QueuedEntity(int tzero, int time, EType type) :
    type(type), time(tzero+time) {

}

bool QueuedEntity::ready(int t) {
    return t >= time;
}

Entity QueuedEntity::make() {
    switch (type) {
        case EType::TOPSMALL:
            return Entity(startx, GAME_CEIL, 20, 40, 0x603050);
        case EType::BOTSMALL:
            return Entity(startx, GAME_FLOOR-40, 20, 40, 0x603050);
        case EType::TOPBUMP:
            return Entity(startx, GAME_CEIL, 10, 10, 0x703030);
        case EType::BOTBUMP:
            return Entity(startx, GAME_FLOOR-10, 10, 10, 0x703030);
    }
    return Entity();
}

