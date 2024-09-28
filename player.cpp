#include <cstdio>
#include "stdlib.h"
#include "time.h"
#include "gui.h"
#include "player.h"

using namespace std;

void Human_Player::make_move(const char _type, GUI& gui)
{
	gui.get_move(0 ,0, _type);
}

void CPU_Player::make_move(const char _type, GUI& gui)
{
	srand((unsigned)time(NULL));
	Player_Move move;
	bool got_move = false;
	while (!got_move) {
		move.x = (rand() % 15) + 1;
		move.y = (rand() % 15) + 1;
		got_move = gui.check_move(move, _type);
	}
}