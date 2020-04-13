/*
*Author:Nguyen Gia Bach (Ng.JaBach).
*This is an open source code.
*/
#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
#define color(a) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a)

void gotoxy(int tranxuanbach, int vuminhduc){
  COORD coord;
  coord.X = tranxuanbach;
  coord.Y = vuminhduc;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetWindow(int Width, int Height){
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
}
int main(){
	ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0);
	SetWindow(100,100);
	for(int i=0;i<=255;i++){
		gotoxy(10,10+i);
		color(i); cout<<i<<" gay"<<endl;
	}
}

