#ifndef ABRAXAS_CLEANER_H
#define ABRAXAS_CLEANER_H
#include "Header.h"
#include "MD5.h"
class AbraxasCleaner
{
	private:
		vector<string> file_names;
		vector<string> extra_files;
		vector<string> Hashes;
		MD5 md5;
		char *GetHash(string file_name);
	public:
		AbraxasCleaner();
		~AbraxasCleaner();
		void GetFiles(string folder);
		vector<string> getnames();
		string set_string(string foldername,string filename);
		vector<string> GetExtraFiles(vector<string> files,HWND hwnd,HINSTANCE hinst);
		double Getsize(vector<string> extrafiles);
};
#endif
