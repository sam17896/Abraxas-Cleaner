#include"Header.h"
#include "AbraxasCleaner.h"
#include "MD5.h"
using namespace std;
AbraxasCleaner::AbraxasCleaner()
{
		vector<string> file_names;
		vector<string> extra_files;
		vector<string> Hashes;
}
double AbraxasCleaner::Getsize(vector<string> extrafiles) // get size of extra files
{
	double size=0;
	for(int i=0;i<extrafiles.size();i++)
	{
		  FILE * pFile; // pointer of FILE
		  const char* Extrafiles = extrafiles[i].c_str(); // string to LPCSTR(const char*)
  		  pFile = fopen (Extrafiles,"rb");
  		  if (pFile==NULL) perror ("Error opening file"); // if invalid file
  	else
  	{
    	fseek (pFile, 0, SEEK_END);
    	size = size + ftell (pFile); // size of file using ftell
    	fclose (pFile); // close file
    }	
	}
	return size; //size in bytes
}
void AbraxasCleaner::GetFiles(string folder) // get files from folder
{
 	DIR* directory; // pointer of DIR
    struct dirent* entry; //pointer of dirent
    struct stat buf; // variable of stat
	LPCSTR base_directory=folder.c_str(); // string to LPCSTR(const char*)
    size_t base_len = strlen(base_directory); 
    if (!(directory = opendir(base_directory))) //open directory
	{
        perror("failed to open directory"); // if invalid directory
    }
    while((entry = readdir(directory)) != NULL)// while end of directory
	{
        if (!strcmp(entry->d_name, "..") || !strcmp(entry->d_name, ".")) //  ignore first to return values i.e .. and .
		{
            continue;
        }   
        string temp = set_string(base_directory, entry->d_name); // attacthing address to file name 
        LPCSTR filenames = temp.c_str();
        if (stat(filenames, &buf) != 0) 
		{
            perror(filenames);
            continue;
        }
        if (S_ISREG(buf.st_mode)) // check if files
		{ 
			file_names.push_back(filenames);  		
		} 
		else if (S_ISDIR(buf.st_mode)) // check if folder 
		{
  			GetFiles(filenames); // recursive function
        }
    }
    closedir(directory);
}
vector<string> AbraxasCleaner::getnames()
{
	return file_names;
}
char *AbraxasCleaner::GetHash(string file_name)
{
	LPCSTR lpFileName = file_name.c_str(); //string to LPCSTR
	HANDLE hFile = CreateFile(lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
	   // error
	}
	DWORD dwFileSize = GetFileSize(hFile, NULL); //get files size
	if (dwFileSize > 5000000000000)				
	return FALSE;		// if file size exceed the limit program will report error						
	md5_state_t state;
	md5_byte_t digest[16];
	char buffer[1024];
	char szHash[33];
	DWORD dwRead, dwTotal = 0;
	md5.md5_init(&state);  //function call of md5 class
	do 
	{
		ReadFile(hFile, buffer, 1024, &dwRead, NULL);
		md5.md5_append(&state, (const md5_byte_t *)buffer, dwRead); //fucntion call of md5 class
		dwTotal += dwRead;
	} while (dwTotal < dwFileSize);
	md5.md5_finish(&state, digest); //function call of md5 class
	for (int di = 0; di < 16; ++di)
	sprintf(szHash + di * 2, "%02x", digest[di]);
	CloseHandle(hFile);		
	return szHash; //return hash 
}
string AbraxasCleaner::set_string(string foldername,string filename) // setting path
{
	string path;
	path=foldername + "\\" + filename;
	return path;
}
vector<string> AbraxasCleaner::GetExtraFiles(vector<string> files,HWND hwnd,HINSTANCE hinst)// get similar files by comparing
{
	HWND pro;
	int pb_pos; //for progress bar
	pro=CreateWindowEx(0, PROGRESS_CLASS,NULL, WS_CHILD | WS_VISIBLE | PBS_SMOOTH|PBS_MARQUEE , 70, 360, 440, 20, hwnd, (HMENU)IDC_PROGBAR, hinst, NULL); // creating progress bar
	SendMessage(pro, PBM_SETRANGE, 0, MAKELPARAM(0,files.size()+2)); //set progress bar
	string hash1,hash2;	
	for(int i=0;i<files.size();++i)
   	{
   		int count=0;
       	hash1=GetHash(files[i]); //get hash of file
       	for(int p=0;p<Hashes.size();p++)
       	{
       		if(hash1==Hashes[p])
			   {
			   		count++;
			   }	
		}
 		if (count==0)
		{
			Hashes.push_back(hash1);
    		pb_pos = SendMessage(pro, PBM_GETPOS, 0, 0); //get progress bar position
    		pb_pos++;
    		SendMessage(pro, PBM_SETPOS, pb_pos, 0); //set progress bar position
    		for(int j=i+1;j<files.size();++j)
			{
				hash2=GetHash(files[j]);
				if(hash1==hash2)
				{
					pb_pos = SendMessage(pro, PBM_GETPOS, 0, 0); //get progress bar position
    				pb_pos++;
    				SendMessage(pro, PBM_SETPOS, pb_pos, 0); //set progress bar position
					extra_files.push_back(files[j]);
				}
			}	
		}
		}
		SendMessage(pro, PBM_SETPOS, files.size()+2, 0); // fill progress bar
		SendMessage(pro, PBM_SETPOS, 0, 0); // set progress back to zero
		DestroyWindow(pro);
		if(extra_files.size()>0)
		{
			string message="Similar Files Found!"; 
			LPCSTR st=message.c_str();// string to LPCSTR
			::MessageBox(hwnd, st, "Result", MB_OK);
		}
    return extra_files;
}
AbraxasCleaner::~AbraxasCleaner()
{
	//object destroyed
}
