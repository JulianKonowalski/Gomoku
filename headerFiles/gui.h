#ifndef GUI_H
#define GUI_H

#include "player.h"

class GUI 
{
private:
	int round; //licznik tur
	char board[15][15]; //tablica zawierajaza ulozene kamieni obu graczy
	void draw_logo(int x, int y); //rysuje logo
	void draw_outline(int x, int y); //rysuje otoczke interfejsu umieszczajac lewy gorny rog w punkcie [x, y]
	void go_to(int x, int y); //ustawia kursor konsoli w punkcie x, y (liczac znakami)

public:
	GUI(); //inicjalizuje obiekt proszac uzytkownika o przejscie w tryb pelnego ekranu
	int home_screen(int x, int y); //rysuje i obsluguje menu glowne
	int rules(int x, int y); //rysuje i obsluguje ekran zasad
	void draw_board(int x, int y); //rysuje plansze umieszczajac lewy gorny rog w punkcie [x, y]
	void draw_button(int x, int y, int width, int height, const char* txt, int strlen); //rysuje guzik o podanych wymiarach i z podanym tekstem, umieszczajac lewy gorny rog w punkcie[x, y]
	void get_move(int x, int y, const char type); //wczytaj ruch uzytkownika
	bool check_move(Player_Move move, const char type); //sprawdza czy podany ruch mozna wykonac, zwraca wartosc logiczna
	void draw_stones(int x, int y); //narysuj kamienie obu graczy, punkt [x, y] to poczatek ukladu
	int check_endgame(void); //sprawdza czy gra powinna sie dalej toczyc i okresla ktory gracz wygral
	void reset(void); //usuwa wszystkie kamienie na planszy, wypelnia plansze 'n' (NULL) i zeruje licznik tur
	void msg_screen(int x, int y, const char msg[], int strlen); //ekran wypisujacy krotki komunikat msg
};

#endif //GUI_H