#include "Deleter.h"
#include "Header.h"
using namespace std;
void Deleter::Remove_Files(vector<string> extrafiles,HWND hwnd,HINSTANCE hinst)
{
	int pb_pos;
	HWND pro;	
	double size=0;
	pro=CreateWindowEx(0, PROGRESS_CLASS,NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH|PBS_MARQUEE , 70, 360, 440, 20, hwnd, (HMENU)IDC_PROGBAR, hinst, NULL); // create bar
	SendMessage(pro, PBM_SETRANGE, 0, MAKELPARAM(0,extrafiles.size())); //set bar
	vector<string> tempfiles;
	size=size+Getsize(extrafiles); //get size of extra files
	for(int i=0;i<extrafiles.size();i++)
    {
    	pb_pos = SendMessage(pro, PBM_GETPOS, 0, 0); //get bar postion
       	pb_pos++;
       	SendMessage(pro, PBM_SETPOS, pb_pos, 0); //set bar position
       	LPCSTR Extrafiles = extrafiles[i].c_str(); //string to LPCSTR
       	remove(Extrafiles); // delete files
	}
	size=size/(1024*1024); //convert byte to mb
	string message = to_string(size); //int to string
	string mes="Memory Cleared: "+message+ " MB\n"; 
	message = to_string(extrafiles.size()); //int to string
	mes = mes+"Files Deleted: " + message;
	LPCSTR Message=mes.c_str(); //string to LPCSTR
	::MessageBox(hwnd, Message, "Statistics", MB_OK); // display statistics
	SendMessage(pro, PBM_SETPOS, extrafiles.size(), 0); //fill bar
	SendMessage(pro, PBM_SETPOS, 0, 0); // set back to zero
	DestroyWindow(pro);
}
Deleter::~Deleter()
{
	//Object Destroyed
}
