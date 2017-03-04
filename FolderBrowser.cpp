#include "Header.h"
#include "FolderBrowser.h"
using namespace std;
string FolderBrowser::ChooseFolder() 
{  
	TCHAR path[MAX_PATH];
	BROWSEINFO bi = { 0 };
	bi.lpszTitle = ("All Folders Automatically Recursed."); // title of browse window 
	bi.ulFlags = BIF_USENEWUI; //used to add 'Create New Folder' Button
	LPITEMIDLIST pidl = SHBrowseForFolder ( &bi );	// create window to browse the path 
	if ( pidl != 0 )
	{
		SHGetPathFromIDList ( pidl, path ); // get path user selected
		return path; // return path
	} 
	else
	{
		return "Error"; // if user hit cancel button return error
	}
}
FolderBrowser::~FolderBrowser()
{
	//object destroyed
}

