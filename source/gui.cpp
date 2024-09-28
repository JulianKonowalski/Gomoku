#include <cstdio>
#include <stdlib.h>
#include <windows.h>
#include "config.h"
#include "gui.h"
#include "player.h"

using namespace std;

GUI::GUI()
{
	printf("Wlacz tryb pelnoekranowy!\n");
	system("pause");
	system("cls");
	reset();
}

void GUI::go_to(int x, int y)
{
	if (x < 0 || y < 0) {
		fprintf(stderr, "\nNagle zakonczenie programu - podano zle koordynaty elementu GUI.\n");
		exit(0);
	}
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void GUI::draw_outline(int x, int y)
{
	go_to(x, y);
	/*gorna linia*/
	putchar('/');
	for (int i = 0; i < GUI_WDT - 2; ++i) {
		printf("-");
	}
	putchar('\\');
	go_to(x, y + 1); //nowa linia
	/*linie boczne*/
	for (int i = 0; i < GUI_HGT - 2; ++i) {
		putchar('|');
		for (int j = 0; j < GUI_WDT - 2; ++j) {
			printf(" ");
		}
		putchar('|');
		go_to(x, y + 2 + i); //nowa linia
	}
	/*dolna linia*/
	putchar('\\');
	for (int i = 0; i < GUI_WDT - 2; ++i) {
		printf("-");
	}
	putchar('/');
}

void GUI::draw_logo(int x, int y)
{
	go_to(x, y);
	printf("  /$$$$$$   /$$$$$$  /$$      /$$  /$$$$$$  /$$   /$$ /$$   /$$");
	go_to(x, y + 1);
	printf(" /$$__  $$ /$$__  $$| $$$    /$$$ /$$__  $$| $$  /$$/| $$  | $$");
	go_to(x, y + 2);
	printf("| $$  \\__/| $$  \\ $$| $$$$  /$$$$| $$  \\ $$| $$ /$$/ | $$  | $$");
	go_to(x, y + 3);
	printf("| $$ /$$$$| $$  | $$| $$ $$/$$ $$| $$  | $$| $$$$$/  | $$  | $$");
	go_to(x, y + 4);
	printf("| $$|_  $$| $$  | $$| $$  $$$| $$| $$  | $$| $$  $$  | $$  | $$");
	go_to(x, y + 5);
	printf("| $$  \\ $$| $$  | $$| $$\\  $ | $$| $$  | $$| $$\\  $$ | $$  | $$");
	go_to(x, y + 6);
	printf("|  $$$$$$/|  $$$$$$/| $$ \\/  | $$|  $$$$$$/| $$ \\  $$|  $$$$$$/");
	go_to(x, y + 7);
	printf(" \\______/  \\______/ |__/     |__/ \\______/ |__/  \\__/ \\______/ ");
}

int GUI::home_screen(int x, int y)
{
	system("cls");
	draw_outline(x, y);
	draw_logo(x+4, y+2);
	draw_button(x + 4, y + 2 + 20, 16, 3, "WYJDZ", sizeof("WYJDZ")); //po przekazaniu napisu do funkcji, sizeof nie dziala poprawnie
	draw_button(x + 4 + 23, y + 2 + 20, 17, 3, "ZASADY", sizeof("ZASADY"));
	draw_button(x + 4 + 47, y + 2 + 20, 16, 3, "GRAJ", sizeof("GRAJ"));
	go_to(0, GUI_HGT);
	char buffer[BUFFER_SIZE];
	while (true) { //sprawdz wybor uzytkownika
		go_to(x, y+GUI_HGT);
		printf("\rTwoj wybor: ");
		scanf_s("%s", buffer, BUFFER_SIZE);
		if (!strcmp(buffer, "wyjdz")) {
			while (getchar() != '\n') //wyczysc bufor
				;
			return 0;
		}
		else if (!strcmp(buffer, "zasady")) {
			while (getchar() != '\n') //wyczysc bufor
				;
			return 1;
		}
		else if (!strcmp(buffer, "graj")) {
			while (getchar() != '\n') //wyczysc bufor
				;
			return 2;
		}
		while (getchar() != '\n') //wyczysc bufor
			;
		go_to(0, GUI_HGT); //cofnij sie o jedna linie
		for (int i = 0; i < 30; ++i) { //usun wprowadzone znaki
			putchar(' ');
		}
		putchar('\n'); //dla bezpieczenstwa, aby kazda linia konczyla sie \n
	}
}

int GUI::rules(int x, int y) {
	system("cls");
	draw_outline(x, y);
	draw_logo(x + 4, y + 2);
	//wypisanie zasad
	go_to(x + 4, y + 15);
	printf("Celem gry jest ulozenie dokladnie pieciu swoich kamieni/znakow");
	go_to(x + 4, y + 16);
	printf("w ciaglej linii - poziomej, pionowej lub ukosnej. Gracz, ktoremu");
	go_to(x + 4, y + 17);
	printf("sie to uda zostaje zwyciezca. Jesli nie uda sie to zadnemu");
	go_to(x + 4, y + 18);
	printf("z graczy, to nastepuje remis.");
	draw_button(x + 4 + 23, y + 2 + 30, 17, 3, "WROC", sizeof("WROC"));
	go_to(0, GUI_HGT);
	char buffer[BUFFER_SIZE];
	while (true) {
		go_to(x, y+GUI_HGT);
		printf("\rTwoj wybor: ");
		scanf_s("%s", buffer, BUFFER_SIZE);
		if (!strcmp(buffer, "wroc")) {
			while (getchar() != '\n') //wyczysc bufor
				;
			return 3;
		}
		while (getchar() != '\n') //wyczysc bufor
			;
		go_to(0, GUI_HGT); //cofnij sie o jedna linie
		for (int i = 0; i < 30; ++i) { //usun wprowadzone znaki
			putchar(' ');
		}
		putchar('\n'); //dla bezpieczenstwa, aby kazda linia konczyla sie \n
	}
}

void GUI::draw_board(int x, int y)
{
	system("cls");
	draw_outline(x, y);
	x += 5;
	y += 3;
	go_to(x, y);
	/*gorna linia*/
	putchar('/');
	for (int i = 0; i < GUI_WDT - 12; ++i) {
		printf("-");
	}
	putchar('\\');
	go_to(x, y + 1); //nowa linia
	/*pionowe i poziome linie*/
	for (int i = 0; i < GUI_HGT - 8; ++i) {
		putchar('|');
		for (int j = 2; j < GUI_WDT - 10; ++j) { //tutuaj przesunalem indeksowanie o 2, aby linie rysowaly sie prawidlowo
			if (j % 4 == 1) {
				putchar('|');
			}
			else if (i % 2 == 1) {
				putchar('-');
			}
			else {
				putchar(' ');
			}
		}
		putchar('|');
		go_to(x, y + 2 + i); //nowa linia
	}
	/*dolna linia*/
	putchar('\\');
	for (int i = 0; i < GUI_WDT - 12; ++i) {
		printf("-");
	}
	putchar('/');
	/*cyfry*/
	go_to(x - 2, y + 1); //skok na miejsce liczby "15"
	for (int i = 15; i > 0; --i) {
		printf("%2d", i);
		go_to(x-2, y + 3 + 2*(15 - i)); //skok na miejsce kolejnej liczby
	}
	/*litery*/
	go_to(x + 2, y + GUI_HGT - 6); //skok na miejsce litery 'A'
	for (int i = 0; i < 15; ++i) {
		printf("%c   ", 'A' + i);
	}
	go_to(0, GUI_HGT);
}
  
void GUI::draw_button(int x, int y, int width, int height, const char* txt, int strlen)
{
	if (width < 2 || height < 2 || width - 2 < strlen - 1) {
		fprintf(stderr, "\nNagle zakonczenie programu - podano zle wymiary przycisku nalezacego do GUI.\n");
		exit(0);
	}
	go_to(x, y);
	/*gorna linia*/
	putchar('/');
	for (int i = 0; i < width - 2; ++i) {
		putchar('-');
	}
	putchar('\\');
	go_to(x, y + 1);
	/*boczne linie*/
	for (int i = 0; i < height - 2; ++i) {
		putchar('|');
		for (int j = 0; j < width - 2; ++j) {
			putchar(' ');
		}
		putchar('|');
		go_to(x, y + 2 + i);
	}
	/*dolna linia*/
	putchar('\\');
	for (int i = 0; i < width - 2; ++i) {
		putchar('-');
	}
	putchar('/');
	/*napis*/
	int x0, y0; //koordynaty napisu
	if ((width - strlen) % 2 == 0) {
		x0 = x + (width - strlen) / 2;
	}
	else {
		x0 = x + (width - strlen + 1) / 2; //strlen uwzglednia \0, wiec +1, zamiast -1, zeby poprawnie wycentrowac napisy z parzysta liczba drukowalnych znakow
	}
	if (height % 2 == 0) {
		y0 = y + height / 2;
	}
	else {
		y0 = y + (height - 1) / 2;
	}
	go_to(x0, y0);
	printf("%s", txt);
}

void GUI::get_move(int x, int y, const char type)
{
	Player_Move move;
	go_to(0, GUI_HGT);
	bool got_move = false;
	while (!got_move) {
		printf("Twoj ruch: ");
		move.x = getchar() - 'A' + 1; //pobranie wspolrzedniej x
		scanf_s("%d", &move.y); //pobranie wspolrzednej y
		while (getchar() != '\n') //wyczyszczenie bufora klawiatury
			;
		if ((got_move = check_move(move, type))) {
			continue;
		}
		go_to(0, GUI_HGT+1);
		for (int i = 0; i < 30; ++i) { //usun wprowadzone znaki
			putchar(' ');
		}
		putchar('\n'); //dla bezpieczenstwa, aby kazda linia konczyla sie \n
		go_to(0, GUI_HGT);
		for (int i = 0; i < 30; ++i) { //usun wprowadzone znaki
			putchar(' ');
		}
		printf("\rNie mozesz tak zrobic.\n");
	}
}

bool GUI::check_move(Player_Move move, const char type)
{
	//sprawdz czy pole znajduje sie na planszy
	if (move.x < 1 || move.x > 15) {
		return false;
	}
	if (move.y < 1 || move.y > 15) {
		return false;
	}
	if (board[move.y - 1][move.x - 1] != 'n') { //[wiersze][kolumny], zatem [y][x]
		return false;
	}
	round++; //po kazdym pomyslnym ruchu zinkrementuj ilosc zakonczonych tur o 1
	board[move.y - 1][move.x - 1] = type;
	return true;
}

void GUI::draw_stones(int x, int y)
{
	x += 3;
	y += 2;
	for (int i = 0; i < 15; ++i) { //wiersze
		for (int j = 0; j < 15; ++j) { //kolumny
			go_to(x + ((j+1) * 4), y + ((15 - (i+1) + 1) * 2));
			if (board[i][j] != 'n') {
				printf("%c", board[i][j]);
			}
		}
	}
}

int GUI::check_endgame(void)
{
	if (round >= 225) { //sprawdz czy sa jakies wolne pola
		return 3; //remis
	}
	int tmp = 0;
	char type = board[0][0]; //miejsce startowe sprawdzania
	for (int i = 0; i < 15; ++i) { //sprawdzenie wierszami
		for (int j = 0; j < 15; ++j) {
			if (type != board[i][j]) {
				type = board[i][j];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
		}
	}
	type = board[0][0]; //miejsce startowe sprawdzania
	for (int i = 0; i < 15; ++i) { //sprawdzenie kolumnami
		tmp = 0;
		for (int j = 0; j < 15; ++j) {
			if (type != board[j][i]) {
				type = board[j][i];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
		}
	}
	type = board[0][0]; //miejsce startowe sprawdzania
	for (int i = 0; i < 11; ++i) { //sprawdzanie po skosie w prawo, na oraz nad glowna przekatna
		int j = 0;
		tmp = 0;
		for (int k = i; k < 15; ++k) {
			if (type != board[k][j]) {
				type = board[k][j];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
			++j;
		}
		
	}
	type = board[0][1]; //miejsce startowe sprawdzania
	for (int j = 1; j < 11; ++j) { //sprawdzanie po skosie w prawo, pod glowna przekatna
		int i = 0;
		tmp = 0;
		for (int k = j; k < 15; ++k) {
			if (type != board[i][k]) {
				type = board[i][k];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
			++i;
		}
	}
	type = board[0][14]; //miejsce startowe sprawdzania
	for (int i = 0; i < 11; ++i) { //sprawdzanie po skosie w lewo, na i nad glowna przekatna
		int j = 14;
		tmp = 0;
		for (int k = i; k < 15; ++k) {
			if (type != board[k][j]) {
				type = board[k][j];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
			--j;
		}
	}	
	type = board[0][13]; //miejsce startowe sprawdzania
	for (int j = 13; j >= 0; --j) { //sprawdzanie po skosie w lewo, pod glowna przekatna
		int i = 0;
		tmp = 0;
		for (int k = j; k >= 0; --k) {
			if (type != board[i][k]) {
				type = board[i][k];
				tmp = 1;
			}
			else if (type != 'n') {
				++tmp;
			}
			if (tmp == 5) {
				if (type == 'x') {
					return 1; //wygral gracz 1
				}
				else {
					return 2; //wygral gracz 2
				}
			}
			++i;
		}
	}
	return 0; //gra ma sie toczyc dalej
}

void GUI::reset(void)
{
	round = 0; //wyzerowanie licznika tur
	for (int i = 0; i < 15; ++i) {
		for (int j = 0; j < 15; ++j) {
			board[i][j] = 'n'; //wype³nienie planszy znakami n - "NULL"
		}
	}
}

void GUI::msg_screen(int x, int y, const char msg[], int strlen)
{
	system("cls");
	draw_outline(x, y);
	go_to(x + ((GUI_WDT - strlen) / 2), y + ((GUI_HGT - 3) / 2));
	printf("%s", msg);
	go_to(x, y+GUI_HGT);
	system("pause");
}