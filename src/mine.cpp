#include "mine.h"
#include "level.h"
#include "globals.h"
#include "tank.h"
#include "graphics.h"
#include "gui.h"

Mine::Mine() {
    this->width = MINE_SIZE;
    this->height = MINE_SIZE;
    this->respect_holes = true;
}

void Mine::process() {
    //Ignore mines which have already finished their countdowns
    if(!this->countdown) return;

    if(--this->countdown == EXPLOSION_ANIM) {
        detonate();
    }
    if(!this->alive) return;

    //this belongs to enemy
    if(tank != &tanks[0]) {
        if(center_distance_less_than(&tanks[0], MINE_EXPLOSION_RADIUS)) {
            detonate();
            return;
        }
    }

    //this belongs to our tank
    if(!center_distance_less_than(&tanks[0], MINE_EXPLOSION_RADIUS)) {
        for(uint8_t j = 1; j < game.level.num_tanks; j++) {
            if(center_distance_less_than(&tanks[j], MINE_EXPLOSION_RADIUS)) {
                detonate();
                break;
            }
        }
    }
}

void Mine::detonate() {
    this->alive = false;
    this->countdown = EXPLOSION_ANIM - 1;

    //The original game uses a radius, not a square
    //Don't tell anyone.

    for(uint8_t j = COORD_TO_X_TILE(center_x() - MINE_EXPLOSION_RADIUS);
        j <= COORD_TO_X_TILE(center_x() + MINE_EXPLOSION_RADIUS); j++) {
        if(j < 0 || j >= LEVEL_SIZE_X) continue;
        for(uint8_t k = COORD_TO_Y_TILE(center_y() - MINE_EXPLOSION_RADIUS);
            k <= COORD_TO_Y_TILE(center_y() + MINE_EXPLOSION_RADIUS); k++) {
            if(k < 0 || k >= LEVEL_SIZE_Y) continue;
            if(TILE_TYPE(tiles[k][j]) == DESTRUCTIBLE) tiles[k][j] |= DESTROYED;
            needs_redraw = true;
        }
    }

    for(uint8_t j = 0; j < game.level.num_tanks; j++) {
        Tank *tank = &tanks[j];
        if(tank->alive && center_distance_less_than(tank, MINE_EXPLOSION_RADIUS)) {
            tank->alive = false;
            game.kills[tanks[j].type]++;
            if(tanks[j].type != PLAYER) game.total_kills++;
        }
        for(uint8_t k = 0; k < Tank::max_shells[tank->type]; k++) {
            Shell *shell = &tank->shells[k];
            if(shell->alive && center_distance_less_than(shell, MINE_EXPLOSION_RADIUS)) {
                shell->alive = false;
            }
        }
        for(uint8_t k = 0; k < Tank::max_mines[tank->type]; k++) {
            Mine *other = &tank->mines[k];
            if(other->alive && center_distance_less_than(other, MINE_EXPLOSION_RADIUS)) {
                other->detonate();
            }
        }
    }

    bang();

    generate_bg_tilemap();
}
