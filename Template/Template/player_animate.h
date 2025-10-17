#pragma once
enum Player_State {
	RUNNING,
	IDLE,
	DEAD
};

typedef struct Player_Animation {
	enum Player_State state;
	int current_frame;
	float timer;
	float max_timer;
};

typedef struct Player_Sprite {
	CP_Image spritesheet;
	CP_BOOL flip;
	int row_index;
	int collumn_index;
	int animate_timer;
};

void anim_player(CP_Vector index_range, struct Player_Animation* pa);
void state_manager(struct Player_Animation* pa, struct Player_Sprite* ps);