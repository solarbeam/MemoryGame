// Klaipėdos „Ąžuolyno“ gimnazijos II a klasės mokinio
// Liutauro Butkino
// kūrybinis darbas
// 2014 m.
#include <windows.h>
#include "header.h"
#include <ctime>
#include <sstream>
#include <string>

void RefreshText();
std::string IntToStr(int a);
void ShowButton(int id);
void HideButton(int id);
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int param;//Paspausto mygtuko numeris
std::string s;//Simbolių eilutė, skirta taškams skaičiuoti
HWND text=NULL;//Teksto laukas
HWND text2=NULL;//Teksto laukas
bool afterstate=FALSE;//Kintamasis, žymintis ar žaidėjas gauna taška ar ne
int cleanup[2]={0,0};//Mygtuku, kurie buvo paspausti, poros numeriai
int state=0;//Pažymi ar buvo paspaustas mygtukas
int correct=0;//Tašku skaičius
int gueses=0;//Spėjimų skaičius
int buttonselect;//Pasirinktas mygtukas
HINSTANCE hInst;//Programos egzemplioriaus identifikatorius
HWND button[16];//Mygtukai
int a[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//Paveikslelių vietos
int b[16]={1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};//Masyvas, skirtas atsitiktinai išdėlioti paveikslėlius
HBITMAP blank;//Tuščias Paveikslėlis
HBITMAP circle;//Apskritimas
HBITMAP square;//Kvadratas
HBITMAP triangle;//Trikampis
HBITMAP rhombus;//Rombas

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    srand((unsigned)time(0));
    hInst=hThisInstance;
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "MEMORYGAME";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
    if (!RegisterClassEx (&wincl))
        return 0;
    hwnd = CreateWindowEx (
           0,
           "MEMORYGAME",
           "Memory Game",
           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           340,
           450,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );
    ShowWindow (hwnd, nCmdShow);
    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message){
        case WM_COMMAND:
               param=(int)wParam-1;
               switch(state){
                             case 0:buttonselect=param;ShowButton(param);state=1;gueses++;break;
                             case 1:if(buttonselect==param){break;}ShowButton(param);cleanup[0]=param;cleanup[1]=buttonselect;if(a[buttonselect]==a[param]){correct++;afterstate=true;buttonselect=0;}
                             else{afterstate=false;buttonselect=0;}state=0;break;
                             }
    if(state==0){RefreshText();
                 Sleep(500);
    switch(afterstate){
                       case true:ShowWindow(button[cleanup[0]],SW_HIDE);ShowWindow(button[cleanup[1]],SW_HIDE);break;
                       case false:HideButton(cleanup[0]);HideButton(cleanup[1]);break;
    }}
    if(correct==8){
    	int messreturn=MessageBoxW(hwnd,L"Ar norite žaisti dar kartą?",L"Žaidimas baigtas",MB_YESNO|MB_ICONASTERISK|MB_APPLMODAL);
    	if(messreturn==6){
            int b[16]={1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
    		for(int i=0;i!=16;i++){
                int rng=rand()%16;
                if(b[rng]==0){i--;continue;}
                a[i]=b[rng];
                b[rng]=0;}
			for(int i=0;i!=16;i++){
				HideButton(i);
				ShowWindow(button[i],SW_SHOW);
			}
			gueses=0;
			correct=0;
			RefreshText();
    	}
    	if(messreturn==7){
    		PostQuitMessage(0);
    	}
    }
    break;
        case WM_CREATE:
        for(int i=0;i!=16;i++){
                int rng=rand()%16;
                if(b[rng]==0){i--;continue;}
                a[i]=b[rng];
                b[rng]=0;}
        button[0] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 25, 25, 50, 50, hwnd, (HMENU) 1, NULL, NULL);
        button[1] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 100, 25, 50, 50, hwnd, (HMENU) 2, NULL, NULL);
        button[2] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 175, 25, 50, 50, hwnd, (HMENU) 3, NULL, NULL);
        button[3] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 250, 25, 50, 50, hwnd, (HMENU) 4, NULL, NULL);
        button[4] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 25, 100, 50, 50, hwnd, (HMENU) 5, NULL, NULL);
        button[5] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 100, 100, 50, 50, hwnd, (HMENU) 6, NULL, NULL);
        button[6] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 175, 100, 50, 50, hwnd, (HMENU) 7, NULL, NULL);
        button[7] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 250, 100, 50, 50, hwnd, (HMENU) 8, NULL, NULL);
        button[8] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 25, 175, 50, 50, hwnd, (HMENU) 9, NULL, NULL);
        button[9] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 100, 175, 50, 50, hwnd, (HMENU) 10, NULL, NULL);
        button[10] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 175, 175, 50, 50, hwnd, (HMENU) 11, NULL, NULL);
        button[11] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 250, 175, 50, 50, hwnd, (HMENU) 12, NULL, NULL);
        button[12] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 25, 250, 50, 50, hwnd, (HMENU) 13, NULL, NULL);
        button[13] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 100, 250, 50, 50, hwnd, (HMENU) 14, NULL, NULL);
        button[14] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 175, 250, 50, 50, hwnd, (HMENU) 15, NULL, NULL);
        button[15] = CreateWindow("BUTTON", " ", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_BITMAP, 250, 250, 50, 50, hwnd, (HMENU) 16, NULL, NULL);
        circle = LoadBitmap(hInst,MAKEINTRESOURCE(CIRCLE));
        square = LoadBitmap(hInst,MAKEINTRESOURCE(SQUARE));
        triangle = LoadBitmap(hInst,MAKEINTRESOURCE(TRIANGLE));
        rhombus = LoadBitmap(hInst,MAKEINTRESOURCE(RHOMBUS));
        blank = LoadBitmap(hInst,MAKEINTRESOURCE(BLANK));
        text=CreateWindowW(L"STATIC",L"",WS_CHILD | WS_VISIBLE, 25,300,65,30,hwnd,0,0,0);
        text2=CreateWindow("STATIC","",WS_CHILD | WS_VISIBLE, 90,300,25,30,hwnd,0,0,0);
        RefreshText();
        for(int i=0;i!=16;i++)HideButton(i);
        break;
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
void ShowButton(int id){
	switch(a[id]){
                	case 1:SendMessage(button[id], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)circle);break;
                	case 2:SendMessage(button[id], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)square);break;
                	case 3:SendMessage(button[id], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)triangle);break;
                	case 4:SendMessage(button[id], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)rhombus);break;
                }
   SendMessage(button[id], WM_PAINT, (WPARAM)0, (LPARAM)0);
}
void HideButton(int id){
	SendMessage(button[id], BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)blank);
}
std::string IntToStr(int a){
    std::stringstream ss;
    ss << a;
    return ss.str();
}
void RefreshText(){
	SendMessageW(text, WM_SETTEXT, NULL, (LPARAM)L"Spėjimai:\nAtspėta:");
	s = IntToStr(gueses) + "\n"+IntToStr(correct);
	SendMessage(text2, WM_SETTEXT, NULL, (LPARAM)s.c_str());
}
