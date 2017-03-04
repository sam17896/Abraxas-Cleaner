#include "Header.h"
#include "MD5Header.h"
#include "MD5.h"
#include "AbraxasCleaner.h"
#include "Mover.h"
#include "Deleter.h"
#include "FolderBrowser.h"
#include "GUI.h"
using namespace std;
HWND TextBox1,TextBox2,Message,Message2,Header1,Header2,Header3,Header4,Header5,Mover1,Deleter1,Browser1,Browser2,Exit1; //Handle of child windows
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hBitmap; //handle to bitmap
	HBRUSH  hbrBkgnd=NULL,hColorBrush; // handle to brushes (to change bk color of child and parent window)
	char TextSaved[100],TextSaved2[100]; // char array to save addresses
	vector<string> files;
	vector<string> extrafiles;
	HINSTANCE hinst; // handle to instance
	PAINTSTRUCT ps; //variable of PAINTSTRUCT class (used to load bitmap)
	HDC hdc; // handle to dc (used to create bitmap 
	HFONT font1=CreateFont(20,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Segoe UI"); //create custom font 
	HFONT font2=CreateFont(27,0,0,0,FW_ULTRABOLD,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Segoe UI");
	HFONT font3=CreateFont(18,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Segoe UI"); 
	HFONT font4=CreateFont(17,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Segoe UI"); 	
	HFONT font5=CreateFont(12,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Segoe UI");//create custom font 
	Mover move; 
	Deleter del;
	FolderBrowser Choose;
	GUI *Browse1 =new Button();
	GUI *Browse2 =new Button();
	GUI *Delete =new Button();
	GUI *Exit =new Button();
	GUI *Move =new Button();
	GUI *Heading1 =new TextField();
	GUI *Heading2 =new TextField();
	GUI *Heading3 =new TextField();
	GUI *Heading4 =new TextField();
	GUI *Heading5 =new TextField();
	GUI *Box1 =new TextBox();
	GUI *Box2 =new TextBox();
	Bitmap bitmap;
	switch(Message) {
		case WM_CREATE: //create child window and setting font
			{
				// creating child windows using polymorphism
				Browser1=Browse1->CreateChildWindow(hwnd,"Browse",510,220,70,22,1); // create browse button
				Deleter1=Delete->CreateChildWindow(hwnd,"Delete",100,420,70,22,2); //create delete button
				Exit1=Exit->CreateChildWindow(hwnd,"Exit",510,420,70,22,3);  //crete edit button
				Browser2=Browse2->CreateChildWindow(hwnd,"Browse",510,280,70,22,4); //create second browse button
				Mover1=Move->CreateChildWindow(hwnd,"Move",20,420,70,22,5); // create move button
				Header1=Heading1->CreateChildWindow(hwnd,"Welcome To Abraxas Cleaner!",170,140,300,50,6); // Main heading
				Header2=Heading2->CreateChildWindow(hwnd,"Choose a directory to clean:",10,195,250,25,7); //subheading
				Header3=Heading3->CreateChildWindow(hwnd,"Choose a destination to move duplicate files:",10,255,300,25,8);//subheading
				Header4=Heading4->CreateChildWindow(hwnd,"Have a Happy Storage :)",225,160,200,25,9); //main heading
				Header5=Heading5->CreateChildWindow(hwnd,"Copyrights (c) 2015 Abraxas Productions",17,445,200,25,9);
				TextBox1=Box1->CreateChildWindow(hwnd,"",10,220,490,22,10); // create box to enter address
				TextBox2=Box2->CreateChildWindow(hwnd,"",10,280,490,22,11); // create box to enter address
				SendMessage(TextBox1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0)); // these all function are used to set userdefine font
				SendMessage(TextBox2,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Browser1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Deleter1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Exit1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Browser2,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Mover1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
				SendMessage(Header1,WM_SETFONT,(WPARAM)font2,MAKELPARAM(true,0));
				SendMessage(Header2,WM_SETFONT,(WPARAM)font4,MAKELPARAM(true,0));
				SendMessage(Header3,WM_SETFONT,(WPARAM)font4,MAKELPARAM(true,0));
				SendMessage(Header4,WM_SETFONT,(WPARAM)font3,MAKELPARAM(true,0));
				SendMessage(Header5,WM_SETFONT,(WPARAM)font5,MAKELPARAM(true,0));
				break;
			}
		case WM_CTLCOLORSTATIC: // set bk color to all statics windows
		{
			HDC hdcStatic = (HDC) wParam;
			SetTextColor(hdcStatic,RGB(255,255,255));
    		SetBkColor(hdcStatic, RGB(15,15,15));
    		if (hbrBkgnd == NULL)
    		{
    			hbrBkgnd = CreateSolidBrush(RGB(15,15,15));
     		}
        	return (INT_PTR)hbrBkgnd;
        	break;
		}
		case WM_CTLCOLOREDIT: // set bk color to all edit windows 
		{
			HDC hdcStatic = (HDC) wParam;
			SetTextColor(hdcStatic,RGB(255,255,255));
    		SetBkColor(hdcStatic, RGB(99,99,99));
    		if (hbrBkgnd == NULL)
    		{
    			hbrBkgnd = CreateSolidBrush(RGB(99,99,99));
     		}
        	return (INT_PTR)hbrBkgnd;
        	break;
		}
		case WM_PAINT: // load bitmap
			{
				hdc =BeginPaint(hwnd ,&ps);
				bitmap.LoadBitmap("AbraxasCleanerFinal.bmp",hdc,235,7);
				EndPaint(hwnd,&ps);
				break;
			}
		case WM_COMMAND: //button action
			{
				switch (LOWORD (wParam)) //buttons wParam 
				{
        			case 1: //first Browse button 
						{
							string address1=Choose.ChooseFolder(); //call to open browse window						
							if (address1=="Error")  //if user hit cancel
							{
								break; //close browse window
							}
							LPCSTR Address1 = address1.c_str(); //string to LPCSTR 
							TextBox1=Box1->CreateChildWindow(hwnd,Address1,10,220,490,22,10); //replace TextBox1 with the new window with origin address
							SendMessage(TextBox1,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0)); //for font
							break;	
						}
					case 2://Delete button
						{
							DisableProcessWindowsGhosting(); //window will be inactive when any action is being performed
							GetWindowText(TextBox1,&TextSaved[0],100); //get origin address from TextBox1
							string folderaddress=TextSaved; 
                            del.GetFiles(folderaddress); // get all files from the folder
							files=del.getnames(); // get all files from the folder and save it to vector files
							extrafiles=del.GetExtraFiles(files,hwnd,hinst); //Get same files from the files of folders (hwnd and Hinst is passed as a argument to create progress bar ) 
							if(extrafiles.size()>0) //if extra files found
							{
								Message=::MessageBox(hwnd,"Files will permentaly deleted\nAre you sure you want to delete same files?","Warning",MB_YESNOCANCEL|MB_ICONWARNING); //confirmation from user to delete exrafiles
								if(Message==IDYES)// if user hit yes
                            	{
									del.Remove_Files(extrafiles,hwnd,hinst); // delete all the extra files (hwnd and hinst is passed to create progress bar)
                            	}
								else if(Message==IDNO)// if user hit no                        	
								{
									::MessageBox(hwnd,"No files deleted!","Result",MB_ICONINFORMATION); 
								}
								else if(Message==IDCANCEL) //if user hit cancel
								{
									::MessageBox(hwnd,"Operation canceled","Result",MB_ICONINFORMATION);
								}
							}
							else // if no extra files found
							::MessageBox(hwnd,"No same files found!","Result",MB_ICONINFORMATION);
							break;
						}
					case 3://Exit button 
					{
						Message=::MessageBox(hwnd,"Are you sure you want to exit?","Exit",MB_YESNO|MB_ICONWARNING); //confirmation from user
						if(Message==IDYES)
						PostQuitMessage(0);
						break;
					}
					case 4: //second Browse button
						{
							string address2=Choose.ChooseFolder();
							if (address2=="Error") 
							{
								break;
							}
							LPCSTR Address2 = address2.c_str();
							TextBox2=Box2->CreateChildWindow(hwnd,Address2,10,280,490,22,11);
							SendMessage(TextBox2,WM_SETFONT,(WPARAM)font1,MAKELPARAM(true,0));
							break;
							// same as first browse button
						}
					case 5:
						{
							DisableProcessWindowsGhosting(); // diable window while processing 
							GetWindowText(TextBox1,&TextSaved[0],100); // get text/address of box 1 and save into TextSaved
							GetWindowText(TextBox2,&TextSaved2[0],100); // get text/address of box2 and save into TextSaved 2
							string originaddress=TextSaved; // save origin address in a string
							string destinationaddress=TextSaved2;// save destination address in a string
							move.GetFiles(originaddress); // get all files name   
							files=move.getnames(); // save files names in a vector file
							extrafiles=move.GetExtraFiles(files,hwnd,hinst); // get extra/similar/duplicate files 
							if(extrafiles.size()>0)// if extra files found
							{
								Message=::MessageBox(hwnd,"Are You Sure You Want To Move Same Files?","Warning!",MB_YESNOCANCEL|MB_ICONWARNING);
								if(Message==IDYES) // if user hit yes
                            	{
									move.Move_files(extrafiles,destinationaddress,hwnd,hinst); // move files
                            		::MessageBox(hwnd,"Files Sucessfully Moved!","Result",MB_ICONINFORMATION);	
								}
								else if(Message==IDNO) // if user hit no                       	
								{
									::MessageBox(hwnd,"No Files Moved!","Result",MB_ICONINFORMATION);
								}
								else if(Message==IDCANCEL) // if user hit cancel
								{
									::MessageBox(hwnd,"Operation Canceled","Result",MB_ICONINFORMATION);
								}
							}
							else
							::MessageBox(hwnd,"No Same Files Found!","Result",MB_ICONINFORMATION); // if no similar/duplicate files found
							break;
						}
					}
				}
				break;
		case WM_DESTROY: // destroy all child windows and pointer objects and dismisses the program
		 {
		 	delete Browse1;
			delete Browse2;
			delete Delete;
			delete Exit;
			delete Move;
			delete Heading1;
			delete Heading2;
			delete Heading3;
			delete Heading4;
			delete Heading5;
			delete Box1;
			delete Box2;
			DestroyWindow(TextBox1);
			DestroyWindow(TextBox2);
			DestroyWindow(Header1);
			DestroyWindow(Header2);
			DestroyWindow(Header3);
			DestroyWindow(Header4);
			DestroyWindow(Header5);
			DestroyWindow(Mover1);
			DestroyWindow(Deleter1);
			DestroyWindow(Browser1);
			DestroyWindow(Browser2);
			DestroyWindow(Exit1);
			PostQuitMessage(0);
			break;
		 }
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
			break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A ExtraFilesMessageorary location for all messages */
 	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(15,15,15 )); // set bk color
	wc.lpszClassName = "WindowClass";
	wc.hIcon = (HICON) LoadImage( NULL,"Abraxas Cleaner.ico",   IMAGE_ICON,0,0,LR_LOADFROMFILE|LR_SHARED); // load a custom icon
	wc.hIconSm=(HICON) LoadImage( NULL,"Abraxas Cleaner.ico",   IMAGE_ICON,0,0,LR_LOADFROMFILE|LR_SHARED); // load a custon icon
	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK); // if windows creation failed
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Abraxas Cleaner",WS_VISIBLE|WS_SYSMENU|WS_MINIMIZEBOX,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT,/*y*/
		600, /* width */
		500, /* height */
		NULL,NULL,hInstance,NULL); // create main window with title AbraxasCleaner

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
