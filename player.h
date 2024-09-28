#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class GUI;

struct Player_Move { //zestaw koordynatow wykonanego ruchu
	int x;
	int y;
};

class Player {
public:
	virtual void make_move(const char _type, GUI& gui) {}; //przyjecie ruchu gracza
};

class Human_Player : public Player {
public:
	void make_move(const char _type, GUI& gui); //przyjecie ruchu gracza
};

class CPU_Player : public Player {
public:
	void make_move(const char _type, GUI& gui); //wylosowanie ruchu komputera
};

#endif