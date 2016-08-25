#include "game.hpp"

void Game::init(int time) {
    lastTick = time;

    player = Entity(50, floor, 30, 30);
    player.color = 0x00FF00;

    makeLevel(queued, time);
}

void Game::tick(int time) {

    float &airpos = player.y;
    airpos += gravity * (float) (time-lastTick) * 0.6;
    if (airpos + player.h >= floor) {airpos=floor - player.h; grounded=true;}
    if (airpos         <= ceiling ) {airpos=ceiling;          grounded=true;}

    obstaclex -= (time-lastTick) * 0.015;
    
    while (!queued.empty() && queued.front().ready(time)) {
        onScreen.push_back(queued.front().make());
        queued.pop();
    }
    while (!onScreen.empty() && !onScreen.front().onScreen()) {
        onScreen.pop_front();
    }
    for (auto &entity : onScreen) {
        entity.move(velocity, time-lastTick);
        if (entity.checkCollisionWithPlayer(player.y)) {
            sendMessage(Message::LOST, time);
            break;
        }
    }

    lastTick = time;
}

void Game::render(SDL_Surface *screen) {
    player.render(screen);

    for (auto &entity : onScreen) {
        entity.render(screen);
    }

    SDL_Rect obstaclerect = {(int) obstaclex, 300, 60, 15};
    SDL_FillRect(screen, &obstaclerect, 0xFF5050);
}

void Game::sendMessage(Message msg, int time) {
    if (msg == Message::JUMP) {
        if (grounded) {
            gravity *= -1;
            grounded = false;
        }
    } else if (msg == Message::LOST) {
        restart(time);
    }
}

void Game::restart(int time) {
    lastTick = time;

    player = Entity(50, floor, 30, 30);
    player.color = 0x00FF00;
    gravity = 1;

    queued = std::queue<QueuedEntity>();
    onScreen.clear();
    obstaclex = 800;
    makeLevel(queued, time);
}

#define PUSH(t, type) queue.push(QueuedEntity(tzero, t, EType::type))
#define TOP(t) PUSH(t, TOPSMALL)
#define BOT(t) PUSH(t, BOTSMALL)
#define UPBUMP(t) PUSH(t, TOPBUMP); PUSH(t+400, BOTBUMP)
#define BOTBUMP(t) PUSH(t, BOTBUMP); PUSH(t+400, TOPBUMP)

void makeLevel(std::queue<QueuedEntity> &queue, int tzero) {
    for (int i = 0; i != 64; i++) {
        int type = std::rand() % 4;
        int time = i*800;
        switch (type) {
            case 1:
                TOP(time);
                break;
            case 2:
                BOT(time);
                break;
            case 0:
                UPBUMP(time);
                break;
            case 3:
                BOTBUMP(time);
                break;
        }
    }    
}
