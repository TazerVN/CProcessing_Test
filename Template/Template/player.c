#include "cprocessing.h"
#include "tilemap.h"
#include "player.h"
#include "player_animate.h"

void init_player(struct Player* p, int position_x, int position_y, int speed, int acc, CP_Image sprite, CP_BOOL flip, int row_index, int collumn_index) {
	p->position = CP_Vector_Set(position_x, position_y);
	p->velocity = CP_Vector_Set(0, 0);
	p->speed = speed;
	p->acc = acc;
	p->sprite.spritesheet = sprite;
	p->sprite.flip = flip;
	p->sprite.row_index = row_index;
	p->sprite.collumn_index = collumn_index;
	p->state_manager.state = IDLE;
	p->state_manager.timer = 0;
	p->state_manager.max_timer = 0.25;
}


void render_player(struct Player* p) {

	float decel = p->acc / 1.5;
	float dt = CP_System_GetDt();
	int x = p->position.x;
	int y = p->position.y;
	float vx = p->velocity.x;
	float vy = p->velocity.y;

	if (CP_Input_KeyDown(KEY_D)) {
		vx = (vx + p->acc * dt) >= 1 ? 1 : vx + dt * p->acc;
		p->state_manager.state = RUNNING;
		p->sprite.flip = FALSE;
	}
	if (CP_Input_KeyDown(KEY_A)) {
		vx = (vx - p->acc * dt) <= -1 ? -1 : vx - dt * p->acc;
		p->state_manager.state = RUNNING;
		p->sprite.flip = TRUE;
	}
	if (CP_Input_KeyDown(KEY_S)) {
		vy = (vy + p->acc * dt) >= 1 ? 1 : vy + dt * p->acc;
	}
	if (CP_Input_KeyDown(KEY_W)) {
		vy = (vy - p->acc * dt) <= -1 ? -1 : vy - dt * p->acc;
	}

	if(vx > 0){
		vx = vx - dt * decel <= 0 ? 0 : vx - dt * decel;
	}
	else if (vx < 0) {
		vx = vx + dt * decel >= 0 ? 0 : vx + dt * decel;
	}

	if (vy > 0) {
		vy = vy - dt * decel <= 0 ? 0 : vy - dt * decel;
	}

	else if (vy < 0) {
		vy = vy + dt * decel >= 0 ? 0 : vy + dt * decel;
	}

	if (vx == 0 && vy == 0) {
		p->state_manager.state = IDLE;
	}

	x += vx * p->speed;
	y += vy * p->speed;

	p->velocity.x = vx;
	p->velocity.y = vy;
	p->position.x = x;
	p->position.y = y;

	state_manager(&p->state_manager, &p->sprite);
	
	draw_tile(p->sprite.spritesheet, x, y, p->sprite.row_index, p->sprite.collumn_index, 10, 15, 10, p->sprite.flip);
}