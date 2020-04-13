#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include <Mmsystem.h>
#include<fstream>
#define color(a) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),a)
using namespace std;
typedef long long ll;
const char go_out1[]="exit",go_out2[]="esc";
const int N=150;
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
bool ok=false,progress[10],ene_coord=false;
char a[N][N],go,fire,game_mode,file_mode,volspeed[]="    V    ",speedstair[]="|||||||||",choice; 
string file_a,file_b,file_c,file_d;	
fstream myfile,savefile;
void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
int x,y,speed,n,m,u,cnt=0,hieu,nhat,pos[N][N],snum,number,bspeed=50,mika=4,his_dem=0;
struct congratulations{
	bool secret_key_code;
}achievement;
struct tretrau{
	int First,Second;
}ene[N],history[N];
void play(); void game(); void chck(); void batset(); void mune(); void addmap();
void eliminated(int needtobekilled){
	--number;pos[ene[needtobekilled].First][ene[needtobekilled].Second]=-1;
	history[his_dem].First=ene[needtobekilled].First;history[his_dem++].Second=ene[needtobekilled].Second;
	for(int kill=needtobekilled;kill<number;kill++){
		ene[kill].First=ene[kill+1].First;ene[kill].Second=ene[kill+1].Second;//ene[kill]=ene[kill+1];
		pos[ene[kill].First][ene[kill].Second]=kill;
	}
}
void finp(int choic){
	color(choic);
	for(int i=0;i<6;++i){
		gotoxy(0,8+i); printf("                                                  ");
	}
}
void retry(){
	finp(255);color(252);gotoxy(18,10);printf("You died! ");
	color(249);gotoxy(18,12);printf("Play again?");color(240);gotoxy(17,13);printf("1.Yes	2.No\n");cin>>game_mode; his_dem=0;
	finp(0);if(game_mode=='2') exit(1); if(game_mode!='1'){system("cls");printf("Invalid!");retry();exit(1);} cnt=0;ok=false; play();
	exit(1);
}
void es(){
	color(144); gotoxy(0,0); printf(
	"                \n"
	"    Esc-Back    \n"
	"                \n");
}
void adjust_speed(){color(136); system("cls"); es();color(115);
	gotoxy(10,10);printf("    a   ");
	gotoxy(10,11);printf("  <---  ");
	gotoxy(10,12);printf("        ");
	gotoxy(60,10);printf("   d    ");
	gotoxy(60,11);printf("  --->  ");
	gotoxy(60,12);printf("        ");color(112);
	gotoxy(31,8); printf("                 ");
	gotoxy(31,9); printf("                 ");
	gotoxy(31,10);printf("                 ");
	gotoxy(31,11);printf("                 ");
	gotoxy(31,12);printf("                 ");
	gotoxy(31,13);printf("                 ");
	gotoxy(35,11);printf("%s",speedstair);color(118);
	gotoxy(28,4);printf("                        ");
	gotoxy(28,5);printf("                        ");
	gotoxy(28,6);printf("                        ");
	gotoxy(32,5);printf("Current Speed:");
	for(;;){
	gotoxy(35,10);printf("%s",volspeed);
	gotoxy(46,5);printf("%d",mika);gotoxy(0,0);
		for(;;){choice=getch();
			if(choice==27) return;
			if(choice=='a'&&mika>0){
				volspeed[mika--]=' ';
				bspeed+=10;
				volspeed[mika]='V';
				break;}
			else if(choice=='d'&&mika<8){
				volspeed[mika++]=' ';
				bspeed-=10;
				volspeed[mika]='V';
				break;}	
		}
	}
}
void show_ene_coord(){
	color(136);system("cls");es();  color(112);
	gotoxy(25,7);printf("                                                        ");
	gotoxy(25,8);printf("                                                        ");
	gotoxy(25,9);printf("                                                        ");
		gotoxy(27,8); printf("Showing enemies coordinates is now currently "); color(112);printf("|");
		if(!ene_coord){color(120);printf("OFF"); }
		else{color(118);printf("ON");}
		color(112);printf("|");
		gotoxy(49,11); printf("Yes");
		gotoxy(49,12);printf("NO ");
		color(240);hieu=0;choice=1;
		for(;;){
			hieu+=((choice=='w'&&hieu>0)?-1:((choice=='s'&&hieu<1)?1:0));
			if(hieu==0){color(118);
			gotoxy(73,8); printf("ON ");color(129);
			gotoxy(44,11); printf("--->");
			gotoxy(53,11); printf("<---");
			do{choice=getch();
			}while(choice!=27&&choice!='s');color(136);
			gotoxy(44,11); printf("    ");
			gotoxy(53,11); printf("    ");
			}
			else if(hieu==1){color(120);
				gotoxy(73,8);printf("OFF");color(129);
				gotoxy(44,12); printf("--->");
				gotoxy(53,12); printf("<---");
				do{choice=getch();
				}while(choice!=27&&choice!='w');color(136);
				gotoxy(44,12); printf("    ");
				gotoxy(53,12); printf("    ");
			}
			if(choice==27) break;
		}
}
void batset(){int hong=10;
	color(136);system("cls");es();
	gotoxy(25+hong,7);printf("                              ");
	gotoxy(25+hong,8);printf("                              ");
	gotoxy(25+hong,9);printf("                              ");
	gotoxy(25+hong,10);printf("                              ");
	gotoxy(31+hong,8); printf("Adjust bullet Speed");
	gotoxy(27+hong,9); printf("In-game enemy's coordinate");
	color(240);hieu=0;choice=1;
		for(;;){
			if(choice==13){
				if(hieu==0)adjust_speed();
				else if(hieu==1)show_ene_coord();
				color(136);system("cls");es();
				gotoxy(25+hong,7);printf("                              ");
				gotoxy(25+hong,8);printf("                              ");
				gotoxy(25+hong,9);printf("                              ");
				gotoxy(25+hong,10);printf("                              ");
				gotoxy(32+hong,8); printf("Adjust bullet Speed");
				gotoxy(27+hong,9); printf("In-game enemy's coordinate");
				color(240);hieu=0;choice=1;
			}
			hieu+=((choice=='w'&&hieu>0)?-1:((choice=='s'&&hieu<1)?1:0));
			if(hieu==0){color(129);
			gotoxy(20+hong,8); printf("--->");
			gotoxy(56+hong,8); printf("<---");
			do{choice=getch();
			}while(choice!=13&&choice!=27&&choice!='s');color(136);
			gotoxy(20+hong,8); printf("    ");
			gotoxy(56+hong,8); printf("    ");
			}
			else if(hieu==1){color(129);
				gotoxy(20+hong,9); printf("--->");
				gotoxy(56+hong,9); printf("<---");
				do{choice=getch();
				}while(choice!=13&&choice!=27&&choice!='w');color(136);
				gotoxy(20+hong,9); printf("    ");
				gotoxy(56+hong,9); printf("    ");
			}
			if(choice==27) break;
		}
}
void addmap(int lev){string s;
	if(lev==1){
		m=70;
		myfile.open("level1.txt");
	}
	else if(lev==2){
		m=70;
		myfile.open("level2.txt");
	}
	else if(lev==3){
		m=60;
		myfile.open("level3.txt");
	}
	else if(lev==4){
		m=70;
		myfile.open("level4.txt");
	}
	else if(lev==5){
		m=59;
		myfile.open("level5.txt");
	}
	while(getline(myfile,s)){
		for(int i=0;i<s.length();++i){
			if(s.at(i)=='E'){
				a[n][i]='E'; ++number;
				pos[n][i]=cnt;
				ene[cnt].First=n; ene[cnt++].Second=i;
			}
			else if(s.at(i)=='#'){
				a[n][i]='#';pos[n][i]=-1;
			}
			else if(s.at(i)==' '){
				a[n][i]=' ';pos[n][i]=-1;
			}
			else if(s.at(i)=='P'){
				a[n][i]='P';pos[n][i]=-1;
				x=n; y=i;
			}
		}++n;
		//cout<<s<<endl;
	}
	myfile.close();
}
void sound(){
	gotoxy(30,15);printf("This is still not availble!"); getch();
	gotoxy(30,15);printf("                           ");
}
void xnxx(){
	gotoxy(30,15);printf("This is still not availble!");getch();
	gotoxy(30,15);printf("                           ");
}
void menu(){
	for(;;){
		color(160);system("cls"); 
		myfile.open("Menu.txt"); string s;
		for(int i=0;i<7;++i){
			gotoxy(0,30+i); getline(myfile,s);
			if(i==0) color(236);
			else if(i==1||i==2) color(233);
			else if(i==3) color(237);
			else if(i==6) color(225);
			else color(224);
			cout<<s<<endl;
		} myfile.close(); 
		myfile.open("Option.txt");
		for(int i=0;i<11;++i){
			gotoxy(20,2+i); getline(myfile,s);
			if(i<6) color(176);
			else color(112);
			cout<<s<<endl;
		}myfile.close(); game_mode='1';
		do{color(160);
			if(game_mode>'6'){gotoxy(50,2+game_mode-'1'); printf("<---");}
			else{gotoxy(15,2+game_mode-'1'); printf("--->");}
			for(;;){
				choice=getch();
				if(choice=='w'&&game_mode>'1'){color(170);
				if(game_mode>'6'){gotoxy(50,2+game_mode-'1'); printf("    ");}
				else{gotoxy(15,2+game_mode-'1'); printf("    ");}
					--game_mode;
					break;}
				else if(choice=='s'&&game_mode<59){color(170);
				if(game_mode>'6'){gotoxy(50,2+game_mode-'1'); printf("    ");}
				else{gotoxy(15,2+game_mode-'1'); printf("    ");}
					++game_mode;
					break;}
				else if(choice==13) break;
			}
		}while(choice!=13);
		switch(game_mode){
			case '1':{n=0;number=0; speed=3;
				addmap(1);
				cnt=0;
				break;}
			case '2':{n=0; number=0; speed=3;
				addmap(2);
				cnt=0;
				break;}
			case '3':{n=0; number=0;speed=3;
				addmap(3);
				cnt=0;
				break;}
			case '4':{n=0; number=0;speed=3;
				addmap(4);
				cnt=0;
				break;
			}
			case '5':{n=0; number=0;speed=3;
				addmap(5);
				cnt=0;
				break;
			}
			case ':':{
				color(112);system("cls");es();color(143);gotoxy(40,5);printf("Battle Settings");
				gotoxy(33,7); printf("Sound Settings.(Not availble)");
				gotoxy(45,9); printf("XXXX");hieu=0;choice=1;color(112);
				for(;;){
					if(choice==13){
						if(hieu==0) batset();
						else if(hieu==1) sound();
						else if(hieu==2) xnxx();
						color(112);system("cls");es();color(143);gotoxy(40,5);printf("Battle Settings");
						gotoxy(33,7); printf("Sound Settings.(Not availble)");
						gotoxy(45,9); printf("XXXX");color(112);
					}
					hieu+=((choice=='w'&&hieu>0)?-1:((choice=='s'&&hieu<3)?1:0));
					if(hieu==0){
						gotoxy(35,5); printf("--->");
						gotoxy(56,5); printf("<---");
						do{choice=getch();
						}while(choice!=13&&choice!=27&&choice!='s');
						
						gotoxy(35,5); printf("    ");
						gotoxy(56,5); printf("    ");
					}
					else if(hieu==1){
						gotoxy(28,7); printf("--->");
						gotoxy(63,7); printf("<---");
						do{choice=getch();
						}while(choice!=13&&choice!=27&&choice!='s'&&choice!='w');
						gotoxy(28,7); printf("    ");
						gotoxy(63,7); printf("    ");
					}
					else if(hieu==2){
						gotoxy(40,9); printf("--->");
						gotoxy(50,9); printf("<---");
						do{choice=getch();
						}while(choice!=13&&choice!=27&&choice!='w');
						gotoxy(40,9); printf("    ");
						gotoxy(50,9); printf("    ");
					}
					if(choice==27) break;
				}
				break;		
			}
			case ';':{
				if(file_mode=='1'){myfile.open("a.inp",ios::out); myfile<<file_a<<endl;}
			 	else if(file_mode=='2'){myfile.open("b.inp",ios::out); myfile<<file_b<<endl;}
			 	else if(file_mode=='3'){myfile.open("c.inp",ios::out); myfile<<file_c<<endl;}
			 	else if(file_mode=='4'){myfile.open("d.inp",ios::out); myfile<<file_d<<endl;}
			 	for(int i=0;i<5;++i) myfile<<(progress[i]?'1':'0');
			 	myfile<<endl;
				 myfile.close();
				mune();
				break;
			}
			default:{
				printf("Your key is Invalid or this game_mode/funtion is still not completed yet!\nTry other key word!");
				getch();
				break;
			}
		}
		if(game_mode>='1'&&game_mode<='5') break;
	}
}
void print(){color(112);system("cls");
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++) printf("%c",a[i][j]);
		cout<<endl;
	} printf("\n\n");
}
void approach(int cx,int cy){
	a[x][y]=' ';gotoxy(y,x);printf(" "); a[cx][cy]='X'; gotoxy(cy,cx); printf("X");
	retry();exit(1);
}
void approach2(int cx, int cy){
	a[cx][cy]=' '; gotoxy(cy,cx); printf(" ");a[x][y]='X';gotoxy(y,x); printf("X");
	retry();exit(1);
}
void enemy(){
	for(int i=0;i<number;i++){
		if(pos[ene[i].First][ene[i].Second]==i) if(a[ene[i].First][ene[i].Second]=='E'){
			/*if(x>ene[i].First&&y>ene[i].Second){
				swap(a[ene[i].First][ene[i].Second],a[ene[i].First+1][ene[i].Second+1]);
				++ene[i].First; ++ene[i].Second;
			}
			else if(x<ene[i].First&&y<ene[i].Second){
				swap(a[ene[i].First][ene[i].Second],a[ene[i].First-1][ene[i].Second-1]);
				--ene[i].First; --ene[i].Second;
			}*/
			if(x<ene[i].First&&a[ene[i].First-1][ene[i].Second]!='E'){
				if(a[ene[i].First-1][ene[i].Second]=='P') approach2(ene[i].First,ene[i].Second);
				swap(a[ene[i].First-1][ene[i].Second],a[ene[i].First][ene[i].Second]);
				gotoxy(ene[i].Second,ene[i].First); printf(" ");
				gotoxy(ene[i].Second,ene[i].First-1); printf("E");
				swap(pos[ene[i].First-1][ene[i].Second],pos[ene[i].First][ene[i].Second]);
				--ene[i].First;}
			else if(x>ene[i].First&&a[ene[i].First+1][ene[i].Second]!='E'){
				if(a[ene[i].First+1][ene[i].Second]=='P') approach2(ene[i].First,ene[i].Second);
				swap(a[ene[i].First+1][ene[i].Second],a[ene[i].First][ene[i].Second]);
				gotoxy(ene[i].Second,ene[i].First); printf(" ");
				gotoxy(ene[i].Second,ene[i].First+1); printf("E");
				swap(pos[ene[i].First+1][ene[i].Second],pos[ene[i].First][ene[i].Second]);
				++ene[i].First;}
			else if(y>ene[i].Second&&a[ene[i].First][ene[i].Second+1]!='E'){
				if(a[ene[i].First][ene[i].Second+1]=='P') approach2(ene[i].First,ene[i].Second);
				swap(a[ene[i].First][ene[i].Second+1],a[ene[i].First][ene[i].Second]);
				gotoxy(ene[i].Second,ene[i].First); printf(" ");
				gotoxy(ene[i].Second+1,ene[i].First); printf("E");
				swap(pos[ene[i].First][ene[i].Second+1],pos[ene[i].First][ene[i].Second]);
				++ene[i].Second;}
			else if(y<ene[i].Second&&a[ene[i].First][ene[i].Second-1]!='E'){
				if(a[ene[i].First][ene[i].Second-1]=='P') approach2(ene[i].First,ene[i].Second);
				swap(a[ene[i].First][ene[i].Second-1],a[ene[i].First][ene[i].Second]);
				gotoxy(ene[i].Second,ene[i].First); printf(" ");
				gotoxy(ene[i].Second-1,ene[i].First); printf("E");
				swap(pos[ene[i].First][ene[i].Second-1],pos[ene[i].First][ene[i].Second]);
				--ene[i].Second;}	
		}
	}
	gotoxy(0,0);
}
void bullet(char hit){
	switch(hit){
		case '>':{
			if(a[x][y+1]=='E'){
				++cnt;a[x][y+1]=' '; gotoxy(y+1,x);printf(" "); eliminated(pos[x][y+1]); return;
			}
			a[x][y+1]='-'; gotoxy(y+1,x); printf("-"); gotoxy(0,0);
			for(int o=y+2;o<m-1;++o){
				if(a[x][o]=='E'){
					++cnt;a[x][o]=a[x][o-1]=' '; gotoxy(o-1,x); printf("  ");gotoxy(0,0);
					eliminated(pos[x][o]);return;
				}
				swap(a[x][o-1],a[x][o]);
				gotoxy(o-1,x);printf("%c%c",a[x][o-1],a[x][o]);Sleep(bspeed);gotoxy(0,0);
			} 
			a[x][m-2]=' ';gotoxy(m-2,x); printf(" ");gotoxy(0,0);break;
		}
		case '<':{
			if(a[x][y-1]=='E'){
				++cnt;a[x][y-1]=' '; gotoxy(y-1,x);printf(" ");eliminated(pos[x][y-1]); return;
			}
			a[x][y-1]='-';gotoxy(y-1,x); printf("-");gotoxy(0,0);
			for(int o=y-2;o>0;o--){
				if(a[x][o]=='E'){
					++cnt;a[x][o]=a[x][o+1]=' ';gotoxy(o,x);printf("  ");eliminated(pos[x][o]);gotoxy(0,0);return;
				}
				swap(a[x][o+1],a[x][o]);
				gotoxy(o,x);printf("- ");Sleep(bspeed);gotoxy(0,0);
			}
			gotoxy(1,x);a[x][1]=' ';printf(" ");gotoxy(0,0);break;
		}
		case 'v':{
			if(a[x+1][y]=='E'){
				++cnt;a[x+1][y]=' '; gotoxy(y,x+1);printf(" ");eliminated(pos[x+1][y]);return;
			}
			a[x+1][y]='i';gotoxy(y,x+1);printf("i");gotoxy(0,0);
			for(int o=x+2;o<n-1;o++){
				if(a[o][y]=='E'){
					++cnt;a[o][y]=a[o-1][y]=' ';gotoxy(y,o-1);printf(" ");gotoxy(y,o);printf(" ");gotoxy(0,0);eliminated(pos[o][y]);return;
				}
				swap(a[o-1][y],a[o][y]);
				gotoxy(y,o-1);printf(" ");gotoxy(y,o);printf("i");Sleep(bspeed);gotoxy(0,0);
			}
			a[n-2][y]=' ';gotoxy(y,n-2);printf(" ");gotoxy(0,0);break;
		}
		case '^':{
			if(a[x-1][y]=='E'){
				++cnt;a[x-1][y]=' '; gotoxy(y,x-1);printf(" ");eliminated(pos[x-1][y]); return;
			}
			a[x-1][y]='-';
			gotoxy(y,x-1); printf("-");gotoxy(0,0);
			for(int o=x-2;o>0;--o){
				if(a[o][y]=='E'){
					++cnt;a[o][y]=a[o+1][y]=' ';gotoxy(y,o);printf(" ");gotoxy(y,o+1);printf(" ");gotoxy(0,0);
					eliminated(pos[o][y]);return;
				}
				swap(a[o+1][y],a[o][y]);gotoxy(y,o);printf("-");gotoxy(y,o+1);printf(" ");
				Sleep(bspeed);gotoxy(0,0);
			}
			a[1][y]=' '; gotoxy(y,1); printf(" ");gotoxy(0,0);
			break;
		}
	}
}
void shot(){
	a[x][y]='>'; gotoxy(y,x); printf(">");
	for(;;){
		gotoxy(0,n+3);printf("a-Turn left	d-Turn right\nw-Turn up	s-Turn down\nf-FIRE	q-Quit\nYour choice:");
		fire=_getch();if(fire=='q'){a[x][y]='P';gotoxy(y,x);printf("P");game();return;}
		if(fire=='f'){bullet(a[x][y]);return;}
		else switch(fire){
				case 'a':{a[x][y]='<';gotoxy(y,x);printf("<");break;}
				case 'd':{a[x][y]='>';gotoxy(y,x);printf(">");break;}
				case 'w':{a[x][y]='^';gotoxy(y,x);printf("^");break;}
				case 's':{a[x][y]='v';gotoxy(y,x);printf("v");break;}
			}
	}
	a[x][y]='P'; gotoxy(y,x); printf("P");gotoxy(0,0);
}
void game(){
	for(;;){	
		go=getch();
		if(go=='s'){
			if(x+1<n-1){
				if(a[x+1][y]=='E') approach(x+1,y);
				swap(a[x+1][y],a[x][y]);
				gotoxy(y,x); printf(" ");
				gotoxy(y,x+1); printf("P");
				++x;
				return;
			}
		}
		else if(go=='w'){
			if(x-1>0){
				if(a[x-1][y]=='E') approach(x-1,y);
				swap(a[x-1][y],a[x][y]);
				gotoxy(y,x); printf(" ");
				gotoxy(y,x-1); printf("P");
				--x;
				return;
			}
		}
		else if(go=='a'){
			if(y-1>0){
				if(a[x][y-1]=='E') approach(x,y-1);
				swap(a[x][y-1],a[x][y]);
				gotoxy(y,x); printf(" ");
				gotoxy(y-1,x); printf("P");--y;return;
			}
		}
		else if(go=='d'){
			if(y+1<m-1){
				if(a[x][y+1]=='E') approach(x,y+1);
				swap(a[x][y+1],a[x][y]);
				gotoxy(y,x); printf(" ");
				gotoxy(y+1,x); printf("P");++y;return;
			}
		}
		else if(go=='b'){
				shot();
				if(a[x][y]=='q') exit(1);
			a[x][y]='P';gotoxy(y,x);printf("P");return;
		}
		else if(go=='c'){
			if(!achievement.secret_key_code){
				achievement.secret_key_code=true;
				gotoxy(0,n+4);printf("You have discovered new hidden key!\nCheck your achievement librabry for more informations!"); getch();
				gotoxy(0,n+4);printf("                                                       ");
				gotoxy(0,n+5);printf("                                                                     ");
				gotoxy(0,n+6);printf("                                                           ");
			}char scode[100];
			gotoxy(0,n+4);printf("To exit,type 'exit' or 'esc'.\nPlease type your Code here:");
			gets(scode); gotoxy(0,n+4); printf("                                                                                                        ");
			gotoxy(0,n+5); printf("                                                                                                        ");
			if(strcmp(scode,go_out1)==0||strcmp(scode,go_out2)==0) continue;
		}
		gotoxy(0,0);
	}
}
void chck(){
	for(int i=0;i<number+his_dem;++i){
		gotoxy(m+4,i); printf("                ");
	}
	int j=0; hieu=0; 
	for(int i=0;i<number;i++){gotoxy(m+4,i);
		printf("%d %d|pos:%d",ene[i].First,ene[i].Second,pos[ene[i].First][ene[i].Second]);
		if(a[ene[i].First][ene[i].Second]!='E') printf(":Lost connection.");
	}
	for(int i=0;i<his_dem;++i){
		gotoxy(m+4,i+number);
		cout<<history[i].First<<" "<<history[i].Second<<":Was killed"<<endl;
	} gotoxy(0,0);
}

void play(){
	menu();print(); 
	if(ene_coord) chck(); snum=number;
		for(;;){
			for(int k=0;k<speed;k++){
				game();gotoxy(0,0);if(ene_coord) chck();
				if(cnt==snum){ok=true;break;}
			}
			if(ok) break;
			enemy();if(ene_coord) chck();
		}finp(255);color(246);gotoxy(20,10);printf("You won! "); if(!progress[game_mode-'1']){progress[game_mode-'1']=true;gotoxy(7,11); color(240);printf("You has achieved achievement ");
			switch(game_mode){
				case '1':{color(240);printf("Newbie!\n");break;}
				case '2':{color(242);printf("Pupil!\n");break;}
				case '3':{color(253);printf("Expert!\n");break;}
				case '4':{color(246);printf("Master!\n");break;}
				case '5':{color(244);printf("Legendary!\n");break;}
			}
		}getch();finp(0);cnt=0;ok=false;play();
}
void file_opt(string s,int hippy){
	gotoxy(26,11+hippy);
	if(s.size()>=46){
		s.at(45)=s.at(44)=s.at(43)='.';
		for(int i=0;i<46;++i) printf("%c",s.at(i)); printf("\n");
	}else{
		for(int i=0;i<s.size();++i) printf("%c",s.at(i)); for(int i=s.size();i<46;++i) printf(" "); printf("\n");
	}
}
void arrow(int dm=10,int cs=5,int dc=10,int ch=10){color(255);
	gotoxy(dm-2,cs-1); printf("#####"); gotoxy(dm-2,cs); printf("##"); gotoxy(dm+1,cs); printf("##");
	gotoxy(dm-2,cs+2); printf("#####"); gotoxy(dm-2,cs+1); printf("##"); gotoxy(dm+1,cs+1); printf("##");
	gotoxy(dc-2,ch-1); printf("#####"); gotoxy(dc-2,ch); printf("##"); gotoxy(dc+1,ch); printf("##");
	gotoxy(dc-2,ch+2); printf("#####"); gotoxy(dc-2,ch+1); printf("##"); gotoxy(dc+1,ch+1); printf("##");
	color(240);
	gotoxy(dm,cs+1); printf("W"); gotoxy(dc,ch); printf("S");
	color(249);
	gotoxy(dm,cs); printf("^\n"); gotoxy(dc,ch+1); printf("V\n");
	
	
}

void rename(){string s; char name[100];
	savefile.open("DMCS.txt",ios::out);
	if(file_mode=='1') myfile.open("a.inp");
	else if(file_mode=='2') myfile.open("b.inp");
	else if(file_mode=='3') myfile.open("c.inp");
	else if(file_mode=='4') myfile.open("d.inp");
	color(112);gotoxy(25,21); printf("                                                ");
	while(getline(myfile,s)) savefile<<s<<endl;
	gotoxy(27,21);fflush(stdin);gets(name);
	color(252);gotoxy(29,22); printf(" Are you sure that you want to Rename? "); gotoxy(29,23); printf("                                       ");
	gotoxy(29,25); printf("                                       ");gotoxy(29,24); printf("                                       ");hieu=0;
	color(159);gotoxy(37,24);printf("Yes"); color(240);gotoxy(57,24); printf("No"); gotoxy(0,0);
	do{
		do{
			choice=getch();
		}while(choice!='d'&&choice!=13);
		if(choice==13) break;
		++hieu; color(240);gotoxy(37,24);printf("Yes"); color(159);gotoxy(57,24); printf("No"); gotoxy(0,0);
		do{
			choice=getch();
		}while(choice!='a'&&choice!=13); if(choice==13) break;
		--hieu;color(159);gotoxy(37,24);printf("Yes"); color(240);gotoxy(57,24); printf("No"); gotoxy(0,0);
	}while(choice!=13); color(0);myfile.close(); savefile.close();
	for(int i=21;i<28;++i){
		gotoxy(0,i);for(int j=0;j<75;++j) printf(" ");
	}
	savefile.open("DMCS.txt");
	if(hieu==0){
		if(file_mode=='1'){
			myfile.open("a.inp",ios::out);
			file_a=name;
				gotoxy(26,12);
				file_opt(file_a,0);
		}
		else if(file_mode=='2'){
			myfile.open("b.inp",ios::out);
			file_b=name;
				gotoxy(26,13);
				file_opt(file_b,1);
		}
		else if(file_mode=='3'){
			myfile.open("c.inp",ios::out);
			file_c=name;
				gotoxy(26,14);
				file_opt(file_c,2);
		}
		else if(file_mode=='4'){
			myfile.open("d.inp",ios::out);
			file_d=name;
				gotoxy(26,15);
				file_opt(file_d,3);
		}
		myfile<<name<<endl;getline(savefile,s);
	}while(getline(savefile,s)) myfile<<s<<endl;
		
	myfile.close(); savefile.close();
}
void reset(){string name;
	color(252);gotoxy(29,22); printf(" Are you sure that you want to Reset?  "); gotoxy(29,23); printf("                                       ");
	gotoxy(29,25); printf("                                       ");gotoxy(29,24); printf("                                       ");hieu=0;
	color(159);gotoxy(37,24);printf("Yes"); color(240);gotoxy(57,24); printf("No"); gotoxy(0,0);
	do{
		do{
			choice=getch();
		}while(choice!='d'&&choice!=13);
		if(choice==13) break;
		++hieu; color(240);gotoxy(37,24);printf("Yes"); color(159);gotoxy(57,24); printf("No"); gotoxy(0,0);
		do{
			choice=getch();
		}while(choice!='a'&&choice!=13); if(choice==13) break;
		--hieu;color(159);gotoxy(37,24);printf("Yes"); color(240);gotoxy(57,24); printf("No"); gotoxy(0,0);
	}while(choice!=13); color(0);
	for(int i=21;i<28;++i){
		gotoxy(0,i);for(int j=0;j<68;++j) printf(" ");
	}
	savefile.open("ideal.txt"); 
	if(hieu==0){getline(savefile,name);
		if(file_mode=='1'){
			myfile.open("a.inp",ios::out);
			file_a=name;
				gotoxy(26,12);
				file_opt(file_a,0);
		}
		else if(file_mode=='2'){
			myfile.open("b.inp",ios::out);
			file_b=name;
				gotoxy(26,13);
				file_opt(file_b,1);
		}
		else if(file_mode=='3'){
			myfile.open("c.inp",ios::out);
			file_c=name;
				gotoxy(26,14);
				file_opt(file_c,2);
		}
		else if(file_mode=='4'){
			myfile.open("d.inp",ios::out);
			file_d=name;
				gotoxy(26,15);
				file_opt(file_d,3);
		}myfile<<name<<endl;
	}
	while(getline(savefile,name)) myfile<<name<<endl;
	savefile.close();myfile.close();
}
void mune(){color(0);system("cls"); gotoxy(0,0); 
	color(144);printf(
	"	              \n"
	"	   Esc-Quit   \n"
	"	              \n"
	);
	arrow(48,2,48,18);file_mode='1';
	color(255);gotoxy(7,9); printf("########"); gotoxy(7,10); printf("###"); gotoxy(11,10); printf("####"); gotoxy(7,11); printf("#"); gotoxy(14,11); printf("#");
	gotoxy(7,12); printf("########");
	color(246);gotoxy(10,10);printf("R"); 
	color(249);gotoxy(8,11); printf("Rename");
	color(255);gotoxy(83,9); printf("########"); gotoxy(83,10); printf("###"); gotoxy(87,10); printf("####"); gotoxy(83,11); printf("#"); gotoxy(90,11); printf("#");
	gotoxy(83,12); printf("########");
	color(253);gotoxy(86,10);printf("N"); 
	color(252);gotoxy(84,11); printf("ResetX");
	color(511); gotoxy(0,0);
	printf("\n\n\n\n\n\n"
	"			**************************************************\n"
	"			**************************************************\n"
	"			**************");color(506);printf("Choose a game file!");
	color(511);printf("*****************\n"
	"			**************************************************\n"
	"			**************************************************\n");
	gotoxy(24,14); printf("**"); gotoxy(72,14); printf("**");
	gotoxy(24,11); printf("**"); gotoxy(72,11); printf("**");
	gotoxy(24,12); printf("**"); gotoxy(72,12); printf("**");
	gotoxy(24,13); printf("**"); gotoxy(72,13); printf("**");
	gotoxy(24,15); printf("**************************************************");
 color(384);
 	myfile.open("a.inp"); getline(myfile,file_a); file_opt(file_a,0); myfile.close();
 	myfile.open("b.inp"); getline(myfile,file_b); file_opt(file_b,1); myfile.close();
 	myfile.open("c.inp"); getline(myfile,file_c); file_opt(file_c,2); myfile.close();
 	myfile.open("d.inp"); getline(myfile,file_d); file_opt(file_d,3); myfile.close();
 	do{
	 	if(file_mode=='1'){
			gotoxy(26,12); color(31);
			file_opt(file_a,0);
			color(384);
			do{
				choice=getch();
			}while(choice!='s'&&choice!=13&&choice!='r'&&choice!='n'&&choice!=27);
			gotoxy(26,12);
			file_opt(file_a,0);
		}
		else if(file_mode=='2'){
			gotoxy(26,13); color(31);
			file_opt(file_b,1);
			color(384);
			do{
				choice=getch();
			}while(choice!='w'&&choice!='s'&&choice!=13&&choice!='r'&&choice!='n'&&choice!=27);
			gotoxy(26,13);
			file_opt(file_b,1);
		}
		else if(file_mode=='3'){
			gotoxy(26,14); color(31);
			file_opt(file_c,2);
			color(384);
			do{
				choice=getch();
			}while(choice!='w'&&choice!='s'&&choice!=13&&choice!='r'&&choice!='n'&&choice!=27);
			gotoxy(26,14);
			file_opt(file_c,2);
		}
		else if(file_mode=='4'){
			gotoxy(26,15); color(31);
			file_opt(file_d,3);
			color(384);
			do{
				choice=getch();
			}while(choice!='w'&&choice!=13&&choice!='r'&&choice!='n'&&choice!=27);
			gotoxy(26,15);
			file_opt(file_d,3);
		}
	 	if(choice=='w') --file_mode;
	 	else if(choice=='s') ++file_mode;
	 	else if(choice=='r'){
	 		rename(); choice=14;
		}
		else if(choice=='n'){
			reset();
			choice=14;
		}
		else if(choice==27){
			color(9); system("cls"); gotoxy(40,10);printf("See you again!"); color(0); exit(0);
		}
	}while((int)choice!=13); string s;
	if(file_mode=='1'){myfile.open("a.inp"); getline(myfile,s);}
 	else if(file_mode=='2'){myfile.open("b.inp"); getline(myfile,s);}
 	else if(file_mode=='3'){myfile.open("c.inp"); getline(myfile,s);}
 	else if(file_mode=='4'){myfile.open("d.inp"); getline(myfile,s);}
 	getline(myfile,s); for(int i=0;i<s.size();++i) progress[i]=(s.at(i)-'0');
	myfile.close();
	/*
	File's name
	Playing process( Newbie, Expert)
	Achievements ( secret code..)
	Item
	
	*/
}
int main(){SetWindow(100,50);PlaySound("mysound.wav",NULL,SND_ASYNC|SND_FILENAME);
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);srand(time(NULL));	
	mune();
	play();
	return 0;
}
