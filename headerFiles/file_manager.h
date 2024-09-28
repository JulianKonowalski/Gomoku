#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

class MyFile;
class FileManager;

class MyFile 
{
	friend FileManager;

private:
	char file_path[100]; //sciezka do wskazywanego pliku
	FILE* file; //wskazywany plik
	MyFile* next; //wskaznik do nastepnego obiektu w liscie dynamicznej

public:
	MyFile(); //inicjalizuje obiekt z wartosciami domyslnymi (empty, NULL, NULL)
	MyFile(const char* _file_path, FILE* _file, MyFile* _next); //inicjalizuje obiekt z polami o wskazanych wartosciach, wartosc _next nie jest wymagana, domyslnie _next = NULL
	~MyFile(); //usuwa obiekt wskazywany przez "next", po czym usuwa siebie
	void set_file(FILE* _file); //nadaje nowa wartosc polu "file"
	FILE* get_file(void); //zwraca wartosc pola "file"
	void set_next(MyFile* _next); //nadaje nowa wartosc polu "next"
	MyFile* get_next(void); //zwaraca wartosc pola "next"
};

class FileManager 
{
private:
	MyFile* files; //lista dynamiczna otwartych plikow

public:
	FileManager(); //inicjalizuje obiekt z lista dynamiczna "files" z wartoscia NULL
	~FileManager(); //usuwa liste dynamiczna "files"
	void open_file(const char* path, const char* mode); //otwiera plik o danej nazwie w danym trybie i dolacza go do listy dynamicznej "files"
	void close_file(const char* path); //zamyka plik o wskazanej nazwie i skraca liste dynamiczna "files"
	void write_to_file(const char* path, const char* msg); //wpisuje podana wiadomosc do pliku o podanej nazwie
};

#endif //FILE_MANAGER_H