#include <cstdio>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "file_manager.h"
#include "config.h"
#include "gui.h"

#pragma warning (disable: 4996)

using namespace std;

int game(int x, int y, GUI& gui) //gra
{
	Player* h_player = new Human_Player, * cpu_player = new CPU_Player;
	int quit = 0;
	while (!quit) {
		gui.draw_board(x, y);
		gui.draw_stones(x, y);
		h_player->make_move('x', gui);
		if ( (quit = gui.check_endgame()) ) { //przypadek kiedy to gracz 1 wykona ostatni ruch/wygra gre, zapobiega nieskonczonej petli
			switch (quit) {
			case 1:
				gui.msg_screen(x, y, "Wygrana!", sizeof("Wygrana!"));
				break;
			case 2:
				gui.msg_screen(x, y, "Przegrana!", sizeof("Przegrana!"));
				break;
			case 3:
				gui.msg_screen(x, y, "Remis!", sizeof("Remis!"));
				break;
			}
			continue;
		}
		gui.draw_board(x, y);
		gui.draw_stones(x, y);
		cpu_player->make_move('o', gui);
		quit = gui.check_endgame();
		switch (quit) {
		case 0:
			//pass
			break;
		case 1:
			gui.msg_screen(x, y, "Wygrana!", sizeof("Wygrana!"));
			break;
		case 2:
			gui.msg_screen(x, y, "Przegrana!", sizeof("Przegrana!"));
			break;
		case 3:
			gui.msg_screen(x, y, "Remis!", sizeof("Remis!"));
			break;
		}
	}
	gui.reset();
	delete h_player;
	delete cpu_player;
	return quit; //informacja o tym jak zakonczyla sie gra
}

void log_entry(const char* path, const char* buffer, FileManager& FM) //wpis do pliku wraz z timestampem
{
	char msg[150];
	time_t aclock;
	tm* newtime;
	time(&aclock);
	newtime = localtime(&aclock);
	strcpy(msg, "");
	strcat(msg, buffer);
	strcat(msg, asctime(newtime));
	FM.write_to_file(path, msg);
}

int main(void)
{
	FileManager FM;
	FM.open_file("log.txt", "a");
	freopen("log.txt", "a", stderr);
	log_entry("log.txt", "Uruchomienie programu\t\t", FM);
	GUI gui;
	int choice = 3;
	bool is_running = true;
	while (is_running) {
		switch (choice) {
		case 0: //wyjdz z gry
			is_running = false;
			gui.msg_screen(0, 0, "Dziekujemy za gre!", sizeof("Dziekujemy za gre!"));
			break;
		case 1: //ekran z zasadami
			log_entry("log.txt", "Przejscie do ekranu z zasadami\t", FM);
			choice = gui.rules(0, 0);
			break;
		case 2: //gra
			log_entry("log.txt", "Uruchomienie gry\t\t", FM);
			choice = game(0, 0, gui);	
			switch (choice) {
			case 1: //wygra³ gracz
				log_entry("log.txt", "Koniec gry - wygral gracz\t", FM);
				break;
			case 2: //wygra³ komputer
				log_entry("log.txt", "Koniec gry - wygral komputer\t", FM);
				break;
			case 3: //remis
				log_entry("log.txt", "Koniec gry - remis\t", FM);
				break;
			}
			choice = 3;
			break;
		case 3: //menu glowne
			log_entry("log.txt", "Przejscie do menu glownego\t", FM);
			choice = gui.home_screen(0, 0);
			break;
		}
	}
	log_entry("log.txt", "Zakonczenie programu\t\t", FM);
	FM.write_to_file("log.txt", "\n");
	return 0;
}