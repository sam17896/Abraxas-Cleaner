#ifndef DELETER_H
#define DELETER_H
#include "Header.h"
#include "AbraxasCleaner.h"
class Deleter:public AbraxasCleaner
{
	public:
		void Remove_Files(vector<string> extrafiles,HWND hwnd,HINSTANCE hinst);
		~Deleter();
};
#endif
