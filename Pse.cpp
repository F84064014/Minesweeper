#include"Pse.h"

Pse::Pse(int w, int h){
	width = w;
	height = h;
	for(i=0;i<max_size;i++)
		for(j=0;j<max_size;j++)
			map[i][j] = answer[i][j] = 0;
}
int Pse::Suspend(){
	char c[50];
	string ch;
	bool go_on = TRUE;
	read_map("map_pause");
	erase();
	nodelay(stdscr, FALSE);
	echo();
	while(go_on){
		erase();
		mvaddstr(0,0,"Enter help for more information");
		attrset(COLOR_PAIR(4));
		mvaddstr(0,6,"help");attrset(A_NORMAL);
		move(1,0);
		getstr(c);
		ch = c;
			if(ch == "quit"){
				Continue();
				return 0;
			}
			else if(ch == "help"){
				HELP();
				continue;
			}
			else if(ch == "how to play"){
				How();
				continue;
			}
			else if(ch == "exit"){
				remove("flag");
				remove("map_pause");
				return 3;
			}
			else if(ch == "This is too hard"){
				Continue();
				print_ans();
				return 1;
			}
			else if(ch == "more hint"){
				Continue();
				return 4;
			}
			else if(ch == "die"){
				Continue();
				return 5;
			}
			else if(ch == "renew"){
				erase();
				remove("flag");
				remove("map_pause");
				nodelay(stdscr, TRUE);
				noecho();
				return 6;
			}
	}
}
void Pse::Continue(){
	erase();
	for(i=0;i<width;i++)
		for(j=0;j<height;j++){
			if(map[i][j] == -1){
				attrset(A_NORMAL);
				mvprintw(j*2,i*2,"%d", answer[i][j]);
			}
			if(flag[i][j] == 1){
				attrset(A_BOLD|COLOR_PAIR(3));
				mvaddstr(j*2,i*2,"f");
			}
			else if(flag[i][j] == 2){
				attrset(A_BOLD|COLOR_PAIR(1));
				mvaddstr(j*2,i*2,"b");
			}
		}
	attrset(A_NORMAL);
	remove("flag");
	remove("map_pause");
	nodelay(stdscr, TRUE);
	noecho();
}
void Pse::read_map(string s){
	static bool first = TRUE;
	ifstream RFlag("flag", ios::in);
	ifstream READ(s,ios::in);
	i = 0;
	j = 0;
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			READ >> map[i][j];
			RFlag >> flag[i][j];
		}
	}
	if(first){
		for(i=0;i<width;i++)
			for(j=0;j<height;j++)
				answer[i][j] = map[i][j];
		first = FALSE;
		remove("ans");
	}
	else return;
}
void Pse::check_map(){
	erase();
	for(i=0;i<height;i++)
		for(j=0;j<width;j++)
			mvprintw(j*2,i*2,"%d",map[i][j]);
}
void Pse::print_ans(){
	for(i=0;i<width;i++)
		for(j=0;j<height;j++)
			if(map[i][j] == -1) continue;
			else if(map[i][j] == 9){
				attrset(COLOR_PAIR(1));
				mvaddstr(j*2,i*2,"b");
			}
			else{
				attrset(COLOR_PAIR(4));
				mvprintw(j*2,i*2,"%d",map[i][j]);
			}
	attrset(A_NORMAL);
}
void Pse::HELP(){
	curs_set(0);
	erase();
	mvaddstr(0,0,"Help");
	mvaddstr(1,0,"Press          to leave help");attrset(COLOR_PAIR(4));mvaddstr(1,6,"anything");attrset(A_NORMAL);
	mvaddstr(2,0,"Enter   to return game");attrset(COLOR_PAIR(4));mvaddstr(2,6,"quit");attrset(A_NORMAL);
	mvaddstr(3,0,"Enter      to exit game");attrset(COLOR_PAIR(4));mvaddstr(3,6,"exit");attrset(A_NORMAL);
	mvaddstr(4,0,"Enter       to creat new map if you don't like this one");attrset(COLOR_PAIR(4));mvaddstr(4,6,"renew");attrset(A_NORMAL);
	mvaddstr(5,0,"Enter     to turn on/off the bomb(on:normal/off:reveal the bomb)");attrset(COLOR_PAIR(4));mvaddstr(5,6,"die");attrset(A_NORMAL);
	mvaddstr(6,0,"Enter           to get more hint");attrset(COLOR_PAIR(4));mvaddstr(6,6,"more hint");attrset(A_NORMAL);
	mvaddstr(7,0,"Enter                  if you think this is too hard");attrset(COLOR_PAIR(4));mvaddstr(7,6,"This is too hard");attrset(A_NORMAL);
	if(getch()){
	curs_set(1);
		return;
	}
}
void Pse::How(){
	curs_set(0);
	erase();
	mvaddstr(0,0,"How to play");
	mvaddstr(1,0,"Press          to leave How to play");attrset(COLOR_PAIR(4));mvaddstr(1,6,"anything");attrset(A_NORMAL);
	mvaddstr(2,0,"Press up down right left on your keyboard to move");attrset(COLOR_PAIR(4));mvaddstr(2,6,"up down right left");attrset(A_NORMAL);
	mvaddstr(3,0,"Press d to dig the mine");attrset(COLOR_PAIR(4));mvaddstr(3,6,"d");attrset(A_NORMAL);
	mvaddstr(4,0,"Press f to put flag on your map");attrset(COLOR_PAIR(4));mvaddstr(4,6,"f");attrset(A_NORMAL);
	mvaddstr(5,0,"Press h to reveal a 3x3 square");attrset(COLOR_PAIR(4));mvaddstr(5,6,"h");attrset(A_NORMAL);
	if(getch()){
	curs_set(1);
		return;
	}
}
