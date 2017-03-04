#ifndef MOVER_H
#define MOVER_H
#include "Header.h"
#include "AbraxasCleaner.h"
class Mover:public AbraxasCleaner
{
	public:
		void Move_files(vector<string>extrafiles,string destinationpath,HWND hwnd,HINSTANCE hinst);
		~Mover();

};
#endif
