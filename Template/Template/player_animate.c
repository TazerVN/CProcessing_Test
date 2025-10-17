#include "cprocessing.h"
#include "player_animate.h"

CP_Vector index_range;
int i;

float elapsedTime = 0.0f;

void state_manager(struct Player_Animation* pa, struct Player_Sprite* ps) {
	
	switch (pa->state) {

	case IDLE:
		index_range = CP_Vector_Set(0, 0);
		break;
	case RUNNING:
		index_range = CP_Vector_Set(1, 2);
		break;
	case DEAD:
		index_range = CP_Vector_Set(3, 3);
		break;
	}

	anim_player(index_range, pa);

	ps->collumn_index = pa->current_frame;
}

void anim_player(CP_Vector index_range, struct Player_Animation* pa) {
	float anim_timer = pa->timer;
	float frame_duration;

	
	anim_timer += CP_System_GetDt();
	if (index_range.y != index_range.x) {
		frame_duration = pa->max_timer / (index_range.y - index_range.x);
	}
	else {
		frame_duration = 0;
		anim_timer = 0;
		pa->current_frame = index_range.x;
	}

	if (anim_timer >= frame_duration && frame_duration != 0) {
		if (pa->current_frame == index_range.y) {
				pa->current_frame = index_range.x;
				anim_timer -= frame_duration;
			}
		else {
				anim_timer -= frame_duration;
				pa->current_frame += 1;

			}
		}
	
	pa->timer = anim_timer;
}