#include "cprocessing.h"
#include "tilemap.h"
#include "player.h"

CP_Image tilemap_default;
CP_Image tilemap_transparent;

struct Player p;

void game_init(void)
{

	tilemap_default = CP_Image_Load("Assets/Default/Tilemap/tilemap_packed.png");
	tilemap_transparent = CP_Image_Load("Assets/Transparent/Tilemap/tilemap_packed.png");
	init_player(&p, 0, 0, 10, 10, tilemap_transparent, FALSE, 6, 0);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetFrameRate(60);
	CP_System_SetWindowSize(1920, 1080);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	generate_tile(tilemap_default, 10, 15, 20);
	render_player(&p);
	//draw_tile(tilemap_transparent, 0, 0, 6, 0, 10, 15, 20);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

}

void game_exit(void)
{
	CP_Image_Free(tilemap_default);
	CP_Image_Free(tilemap_transparent);
}




int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(0);
	return 0;
}
