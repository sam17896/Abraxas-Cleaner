This program is used to clear duplicate files if avaialble in a directory, the program will take address of the
directory from user and delet/move duplicates files if found.

The code is written on Dev-Cpp_5.8.3_TDM-GCC_4.8.1 by using the following libraries

1.  #include <string>
2.  #include <stdio.h>
3.  #include <tchar.h>
4.  #include <fstream>
5.  #include <iostream>
6.  #include <shlobj.h>
7.  #include <vector>
8.  #include <dirent.h>
9.  #include <sys/stat.h>
10. #include <windows.h>

This program is design on 64 bit operating system, make sure you have the above libraries and latest version of Dev
c++ and a 64 bit operating system.

How To Run:

After successfull compilation, a window with a header AbraxasCleaner will appear, containing two boxex. First box is
for the address of the folder to be clean. User will provide address by selecting the folder with browse button present 
just next to the edit box or window. Second box is for the destination address of the duplicate files (if user wants
to move instead of deleting them). If user wants to delete the files, so there is no need to provide destination adrress.
There are two button on the bottom left corner 'Move' and 'Delete', click one of these button to perform the desired action.
You can scan as many directories as you want before exiting the program by clicking of 'Exit' button present on the 
right corner of the window.

Try to follow above mention steps to get the better result.
Have a happy storage :).