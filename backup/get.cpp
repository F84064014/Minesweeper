#include<iostream>
#include<cstdio>
#include<ncurses.h>

int main(){
int c;
int i = 0;
initscr();
cbreak();
while(1){
	if(c = getch() || i == 0) break;
	mvprintw(0+i,0,"%d",i++);

}
endwin();
return 0;
}
