#ifndef PERSON_H
#define PERSON_H

#include "player_animate.h"


extern struct Player_Animation;
extern struct Player_Sprite;


typedef struct Player {
	CP_Vector position;
	CP_Vector velocity;
	int speed;
	struct Player_Sprite sprite;
	struct Player_Animation state_manager;
	int acc;
};



void render_player(struct Player* p);

void init_player(struct Player* p, int position_x, int position_y, int speed, int acc, CP_Image sprite, CP_BOOL flip, int row_index, int collumn_index);

#endif