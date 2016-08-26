#include "game.hpp"

void Game::init(int time) {
    lastTick = time;

    player = Entity(50, floor, 30, 30);
    player.color = 0x00FF00;

    makeLevel(queued, timeTotal, time);
    timeLeft = timeTotal;
}

void Game::tick(int time) {

    float &airpos = player.y;
    airpos += gravity * (float) (time-lastTick) * 0.6;
    if (airpos + player.h >= floor) {airpos=floor - player.h; grounded=true;}
    if (airpos         <= ceiling ) {airpos=ceiling;          grounded=true;}

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

    timeLeft -= time - lastTick;
    lastTick = time;
}

void Game::render(SDL_Surface *screen) {
    SDL_FillRect(screen,NULL,0x303050);
    SDL_Rect board = {0, GAME_CEIL, 500, GAME_FLOOR - GAME_CEIL};
    SDL_FillRect(screen, &board, 0x0000FF);

    player.render(screen);

    for (auto &entity : onScreen) {
        entity.render(screen);
    }


    SDL_Rect progressBar = {50, 0, 400, 20};
    SDL_FillRect(screen, &progressBar, 0x444444);
    int progress = (timeTotal - timeLeft) * 400 / timeTotal;
    progressBar.x += progress; progressBar.w -= progress;
    SDL_FillRect(screen, &progressBar, 0xFF4444);
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
    makeLevel(queued, timeTotal, time);
    timeLeft = timeTotal;
}

#define PUSH(t, type) queue.push(QueuedEntity(tzero, t, EType::type))
#define TOP(t) PUSH(t+50, TOPSMALL); PUSH(t+300,BOTSMALL); PUSH(t+550,TOPSMALL)
#define BOT(t) PUSH(t, BOTSMALL); PUSH(t+300,TOPSMALL); PUSH(t+350, TOPSMALL); PUSH(t+600,BOTSMALL)
#define UPBUMP(t) PUSH(t, TOPBUMP); PUSH(t+300, BOTBUMP)
#define BOTBUMP(t) PUSH(t, BOTBUMP); PUSH(t+300, TOPBUMP)

void makeLevel(std::queue<QueuedEntity> &queue, int &duration, int tzero) {
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
    duration = 64*800 + 3000;
}
