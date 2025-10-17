#include "cprocessing.h"

CP_Image tilemap_default;
CP_Image tilemap_transparent;


void tile_init() {
	tilemap_default = CP_Image_Load("Assets/Default/tilemap_packed.png");
	tilemap_transparent = CP_Image_Load("Assets/Transparent/Tilemap/tilemap_packed.png");
}



void draw_tile(CP_Image tilemap, float position_x, float position_y, int index_row, int index_collumn, int row, int collumn, int scale, CP_BOOL flip) {
	int tm_width = CP_Image_GetWidth(tilemap);
	int tm_height = CP_Image_GetHeight(tilemap);

	float tw = (scale * tm_width / collumn);
	float th = (scale * tm_height / row);

	float s0 = index_collumn * tm_width / collumn;
	float t0 = index_row * tm_height / row;

	float s1 = (index_collumn + 1) * tm_width / collumn;
	float t1 = (index_row + 1) * tm_height / row;
 
	CP_Settings_ImageFilterMode(CP_IMAGE_FILTER_NEAREST);
	if (flip == FALSE) {
		CP_Image_DrawSubImageAdvanced(tilemap, position_x, position_y, tw, th, s0, t0, s1, t1, 255, 0);
	}
	else {
		CP_Image_DrawSubImageAdvanced(tilemap, position_x, position_y, -tw, th, s0, t0, s1, t1, 255, 0);
	}
}

void generate_tile(CP_Image tilemap, int row, int collumn, int scale) {
	int tm_width = CP_Image_GetWidth(tilemap);
	int tm_height = CP_Image_GetHeight(tilemap);

	int window_width = CP_System_GetWindowWidth();
	int window_height = CP_System_GetWindowHeight();

	int tw = tm_width / collumn;
	int th = tm_height / row;


	CP_Random_Seed(1);
	for (int i = 0; i < window_width / (tw*scale) * 2; i++) {
		for (int j = 0; j < window_height / (th*scale) * 2; j++) {
		int random_index_row = CP_Random_RangeInt(2,5);
		int random_index_collumn = CP_Random_RangeInt(0, 2);
		draw_tile(tilemap, i * tw * scale, j * th * scale, random_index_collumn, random_index_row, row, collumn, scale, FALSE);
		}
	}
}