#include"Header.h"
#include "Mover.h"
using namespace std;
void Mover::Move_files(vector<string>extrafiles,string destinationpath,HWND hwnd,HINSTANCE hinst)
{
	int count=0;
	HWND pro;
	pro=CreateWindowEx(0, PROGRESS_CLASS,NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH|PBS_MARQUEE , 70, 360, 440, 20, hwnd, (HMENU)IDC_PROGBAR, hinst, NULL);// create bar
	int pb_pos;
	SendMessage(pro, PBM_SETRANGE, 0, MAKELPARAM(0,extrafiles.size()+2)); // set bar
	for(int i=0;i<extrafiles.size();i++)
	{
		pb_pos = SendMessage(pro, PBM_GETPOS, 0, 0); //get bar position
        pb_pos++;
        SendMessage(pro, PBM_SETPOS, pb_pos, 0); //set bar position
		LPCSTR originpath=extrafiles[i].c_str(); //string to LPCSTR
		string fullpath=extrafiles[i];
		string nametemp=""; // temp string of name
		int k=fullpath.size()-1; 
		while (fullpath[k]!='\\')
		{
			nametemp=nametemp+fullpath[k]; //get files name(it will be reverse)
			k--;
		}
		string name="";
		string temp="";
		count++;
		for(int a=nametemp.size()-1;a>=0;a--)
		{
			name=name+nametemp[a]; // reverse name 
		}
		temp=to_string(count);
		name=temp+name;
		string destpath= set_string(destinationpath,name); //combine path and filename
		LPCSTR destinationpath=destpath.c_str(); //string to LPCSTR
		MoveFile(originpath,destinationpath); //move files from origin to destination
	}
	SendMessage(pro, PBM_SETPOS, extrafiles.size()+2, 0); //fill bar
	SendMessage(pro, PBM_SETPOS, 0, 0); //set bar back to zero
	DestroyWindow(pro);
}
Mover::~Mover()
{
	//object deleted
}
