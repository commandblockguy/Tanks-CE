#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "objects.h"
#include "level.h"
#ifdef CREATE_LEVEL_APPVAR
#include "tiles/tilemaps.h"
#endif

uint16_t tileToXPixel(uint8_t tile_x) {
	return MAP_OFFSET_X + tile_x * TILE_SIZE;
}

uint8_t tileToYPixel(uint8_t tile_y) {
	return tile_y * TILE_SIZE;
}

ufix_t tileToXPt(uint8_t x) {
	return to_ufix(tileToXPixel(x));
}

ufix_t tileToYPt(uint8_t y) {
	return to_ufix(tileToYPixel(y));
}

uint8_t pixelToXTile(uint24_t pix_x) {
	return (pix_x - MAP_OFFSET_X) / TILE_SIZE;
}

uint8_t pixelToYTile(uint8_t pix_y) {
	return pix_y / TILE_SIZE;
}

uint8_t ptToXTile(ufix_t x) {
	return pixelToXTile(from_ufix(x));
}

uint8_t ptToYTile(ufix_t y) {
	return pixelToYTile(from_ufix(y));
}

void createLevels(void) {
	#ifdef CREATE_LEVEL_APPVAR
	#define s(n) {sizeof(lvl##n##_compressed), sizeof(ser_tanks##n)/sizeof(ser_tanks##n[0])}
	SerializedTank* ser_tanks; //TODO: change to a 2D array somehow?
	const SerializedTank ser_tanks1[]  = {{PLAYER, 2, 6}, {IMMOBILE, 19, 6}};
	const SerializedTank ser_tanks2[]  = {{PLAYER, 2, 13}, {BASIC, 19, 3}};
	const SerializedTank ser_tanks3[]  = {{PLAYER, 2, 8}, {BASIC, 5, 1}, {BASIC, 18, 15}, {IMMOBILE, 19, 8}};
	const SerializedTank ser_tanks4[]  = {{PLAYER, 3, 14}, {BASIC, 10, 8}, {BASIC, 18, 2}, {IMMOBILE, 18, 8}, {IMMOBILE, 11, 2}};
	const SerializedTank ser_tanks5[]  = {{PLAYER, 2, 14}, {MISSILE, 14, 1}, {MISSILE, 20, 9}};
	const SerializedTank ser_tanks6[]  = {{PLAYER, 2, 8}, {BASIC, 17, 4}, {BASIC, 17, 15}, {MISSILE, 19, 8}, {MISSILE, 20, 13}};
	const SerializedTank ser_tanks7[]  = {{PLAYER, 2, 14}, {MISSILE, 1, 1}, {MISSILE, 19, 2}, {MISSILE, 2, 7}, {MISSILE, 19, 15}};
	const SerializedTank ser_tanks8[]  = {{PLAYER, 1, 8}, {MISSILE, 21, 2}, {MISSILE, 21, 14}, {MINE, 15, 4}, {MINE, 18, 8}, {MINE, 14, 14}};
	const SerializedTank ser_tanks9[]  = {{PLAYER, 2, 13}, {MINE, 3, 3}, {MINE, 19, 13}, {BASIC, 7, 1}, {BASIC, 13, 5}, {BASIC, 14, 15}, {BASIC, 19, 3}};
	const SerializedTank ser_tanks10[] = {{PLAYER, 1, 12}, {RED, 11, 1}, {RED, 20, 4}};
	const SerializedTank ser_tanks11[] = {{PLAYER, 2, 2}, {BASIC, 3, 13}, {BASIC, 14, 1}, {MISSILE, 7, 0}, {MISSILE, 19, 14}, {RED, 19, 4}, {RED, 10, 8}};
	const SerializedTank ser_tanks12[] = {{PLAYER, 2, 7}, {RED, 12, 1}, {RED, 10, 14}, {IMMOB_MISSILE, 17, 15}, {IMMOB_MISSILE, 19, 4}};
	const SerializedTank ser_tanks13[] = {{PLAYER, 0, 8}, {MINE, 5, 15}, {MINE, 8, 1}, {MINE, 12, 10}, {MISSILE, 20, 1}, {MISSILE, 20, 15}, {MISSILE, 21, 8}};
	const SerializedTank ser_tanks14[] = {{PLAYER, 1, 15}, {RED, 1, 7}, {RED, 15, 1}, {RED, 20, 11}, {IMMOB_MISSILE, 6, 6}, {IMMOB_MISSILE, 15, 11}, {IMMOB_MISSILE, 20, 1}};
	const SerializedTank ser_tanks15[] = {{PLAYER, 2, 15}, {FAST, 6, 5}, {FAST, 19, 2}, {FAST, 19, 15}};
	const SerializedTank ser_tanks16[] = {{PLAYER, 1, 15}, {FAST, 9, 1}, {IMMOB_MISSILE, 20, 1}, {FAST, 13, 8}, {IMMOB_MISSILE, 8, 11}, {FAST, 1, 11}};
	const SerializedTank ser_tanks17[] = {{PLAYER, 1, 13}, {IMMOB_MISSILE, 3, 2}, {IMMOB_MISSILE, 20, 3}, {IMMOB_MISSILE, 10, 8}, {IMMOB_MISSILE, 20, 9}, {IMMOB_MISSILE, 19, 14}};
	const SerializedTank ser_tanks18[] = {{PLAYER, 2, 13}, {MISSILE, 4, 2}, {FAST, 14, 2}, {RED, 7, 4}, {IMMOB_MISSILE, 11, 8}, {MISSILE, 19, 14}, {FAST, 14, 15}};
	const SerializedTank ser_tanks19[] = {{PLAYER, 1, 15}, {FAST, 1, 1}, {FAST, 8, 1}, {FAST, 17, 1}, {FAST, 9, 5}, {FAST, 19, 6}, {FAST, 1, 8}, {FAST, 20, 11}, {FAST, 17, 15}};
	const SerializedTank ser_tanks20[] = {{PLAYER, 2, 8}, {INVISIBLE, 17, 6}, {INVISIBLE, 19, 8}};
	Level lvls[] = {s(1), s(2), s(3), s(4), s(5), s(6), s(7), s(8), s(9), s(10), s(11), s(12), s(13), s(14), s(15), s(16), s(17), s(18), s(19), s(20)};
	LevelPack lvl_pack = {"TANKS!", sizeof(lvls) / sizeof(lvls[0]), {0, 0, 0, 0, 0}};
	ti_var_t appVar;
	int i;

	ti_CloseAll();

	appVar = ti_Open("TANKSLPK", "w");

	ti_Write(&lvl_pack, sizeof(LevelPack), 1, appVar);
	for(i = 0; i < lvl_pack.num_levels; i++) {
		uint8_t* comp_tiles;
		ti_Write(lvls + i, sizeof(Level), 1, appVar);
		switch(i) {
			case 0:
			default:
				comp_tiles = lvl1_compressed;
				ser_tanks = ser_tanks1;
				break;
			case 1:
				comp_tiles = lvl2_compressed;
				ser_tanks = ser_tanks2;
				break;
			case 2:
				comp_tiles = lvl3_compressed;
				ser_tanks = ser_tanks3;
				break;
			case 3:
				comp_tiles = lvl4_compressed;
				ser_tanks = ser_tanks4;
				break;
			case 4:
				comp_tiles = lvl5_compressed;
				ser_tanks = ser_tanks5;
				break;
			case 5:
				comp_tiles = lvl6_compressed;
				ser_tanks = ser_tanks6;
				break;
			case 6:
				comp_tiles = lvl7_compressed;
				ser_tanks = ser_tanks7;
				break;
			case 7:
				comp_tiles = lvl8_compressed;
				ser_tanks = ser_tanks8;
				break;
			case 8:
				comp_tiles = lvl9_compressed;
				ser_tanks = ser_tanks9;
				break;
			case 9:
				comp_tiles = lvl10_compressed;
				ser_tanks = ser_tanks10;
				break;
			case 10:
				comp_tiles = lvl11_compressed;
				ser_tanks = ser_tanks11;
				break;
			case 11:
				comp_tiles = lvl12_compressed;
				ser_tanks = ser_tanks12;
				break;
			case 12:
				comp_tiles = lvl13_compressed;
				ser_tanks = ser_tanks13;
				break;
			case 13:
				comp_tiles = lvl14_compressed;
				ser_tanks = ser_tanks14;
				break;
			case 14:
				comp_tiles = lvl15_compressed;
				ser_tanks = ser_tanks15;
				break;
			case 15:
				comp_tiles = lvl16_compressed;
				ser_tanks = ser_tanks16;
				break;
			case 16:
				comp_tiles = lvl17_compressed;
				ser_tanks = ser_tanks17;
				break;
			case 17:
				comp_tiles = lvl18_compressed;
				ser_tanks = ser_tanks18;
				break;
			case 18:
				comp_tiles = lvl19_compressed;
				ser_tanks = ser_tanks19;
				break;
			case 19:
				comp_tiles = lvl20_compressed;
				ser_tanks = ser_tanks20;
				break;
		}
		ti_Write(comp_tiles, sizeof(uint8_t), lvls[i].compressed_tile_size, appVar);
		ti_Write(ser_tanks, sizeof(SerializedTank), lvls[i].num_tanks, appVar);
	}

	ti_CloseAll();

	/*
	1: blue:(3,7), brown(20,7)
	2: blue:(3,14), grey:(20,4)
	3: blue:(3,9), grey:(6,2), grey:(19,16), brown:(20,9)
	*/
	#endif
}

Tank deserializeTank(SerializedTank ser_tank) {
	Tank result = {0};
	result.type = ser_tank.type;
	result.start_x = ser_tank.start_x;
	result.start_y = ser_tank.start_y;
	result.phys.position_x = tileToXPt(ser_tank.start_x);
	result.phys.position_y = tileToYPt(ser_tank.start_y);
	result.phys.height = TANK_SIZE;
	result.phys.width = TANK_SIZE;
	result.barrel_rot = 0;
	result.tread_rot = 0;
	calc_bullet_spawn(&result);
	return result;
}
