#include <cstdio>
#include <string.h>
#include <stdlib.h>
#include "file_manager.h"
using namespace std;

/*MyFile*/

MyFile::MyFile() : file(NULL), next(NULL)
{
	strcpy_s(file_path, _countof(file_path), "empty");
}

MyFile::MyFile(const char* _path, FILE* _file, MyFile* _next = NULL) : file(_file), next(_next)
{
	strcpy_s(file_path, _countof(file_path), _path);
}

MyFile :: ~MyFile()
{
	fclose(file);
	delete next;
}

void MyFile::set_file(FILE* _file)
{
	file = _file;
}

FILE* MyFile::get_file(void)
{
	return file;
}

void MyFile::set_next(MyFile* _next)
{
	next = _next;
}

MyFile* MyFile::get_next(void)
{
	return next;
}

/*FileManager*/

FileManager::FileManager() : files(NULL) {}

FileManager::~FileManager()
{
	delete files;
}

void FileManager::open_file(const char* path, const char* mode)
{
	FILE* new_file = NULL;
	fopen_s(&new_file, path, mode);
	MyFile* my_file = new MyFile(path, new_file);
	MyFile* ptr = files;
	if (files == NULL) {
		files = my_file;
		return;
	}
	while (ptr->get_next() != NULL) {
		ptr = ptr->get_next();
	}
	ptr->set_next(my_file);
}

void FileManager::close_file(const char* path)
{
	MyFile* ptr = files;
	if (files == NULL) {
		fprintf(stderr, "File close error: file list is empty.\n");
		return;
	}
	if (!strcmp(files->file_path, path)) {
		files = files->get_next();
		delete ptr;
		return;
	}
	while (ptr->get_next() != NULL) {
		if (!strcmp(ptr->get_next()->file_path, path)) {
			MyFile* tmp = ptr->get_next();
			ptr->set_next(tmp->get_next());
			fclose(tmp->file);
			return;
		}
		ptr = ptr->get_next();
	}
	fprintf(stderr, "File close error: file \"%s\" not found.\n", path);
}

void FileManager::write_to_file(const char* path, const char* msg)
{
	MyFile* ptr = files;
	if (files == NULL) {
		fprintf(stderr, "File write error: file list is empty.\n");
		return;
	}
	while (ptr != NULL) {
		if (!strcmp(ptr->file_path, path)) {
			fprintf(ptr->file, msg);
			return;
		}
		ptr = ptr->get_next();
	}
	fprintf(stderr, "File write error: file \"%s\" not found.\n", path);
}