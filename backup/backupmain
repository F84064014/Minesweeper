#include<ncurses.h>
#include<iostream>
#include<unistd.h>
#include"Game.h"
#include"Timer.h"
#include"Pse.h"
#define levels_num 4
using namespace std;

int main(){
int option = 0;
int select;
bool go_on = TRUE;

	initscr();
	curs_set(0);
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1,COLOR_RED,COLOR_BLACK);
	init_pair(2,COLOR_BLACK,COLOR_WHITE);
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	init_pair(4,COLOR_YELLOW,COLOR_BLACK);
	attrset(A_BOLD|COLOR_PAIR(1));
	mvaddstr(0,0,"Select Level(Press up or down)");
	attrset(COLOR_PAIR(0));
	mvaddstr(1,0,"Easy");
	mvaddstr(2,0,"Medium");
	mvaddstr(3,0,"Hard");
	mvaddstr(4,0,"Harder");
	//add new level

	while(go_on){
		select = getch();
		switch(select){
			case KEY_UP: --option;
				if(option < 1) option = levels_num;
				 break;
			case KEY_DOWN: ++option;
				if(option > levels_num) option =1;
				break;
			case '\n':go_on=0;
				continue;
			default:continue; 
		}//switch
		mvaddstr(1,0,"Easy    ");
		mvaddstr(2,0,"Medium  ");
		mvaddstr(3,0,"Hard    ");
		mvaddstr(4,0,"Harder  ");
		//add new level

		attrset(COLOR_PAIR(2));
		mvaddstr(option,0,"Enter  ");
		attrset(A_NORMAL);
	}//while go_on==FALSE
	sleep(1);
	erase();

	Game game_A;//Game declared
	Timer tmr;//timer declared

	switch(option){
		case 1: game_A.bombset(10);game_A.sizeset(10,  8);break; //sizeset(width, height)
		case 2:	game_A.bombset(40);game_A.sizeset(18, 14);break;
		case 3:	game_A.bombset(99);game_A.sizeset(24, 20);break;
		case 4: game_A.bombset(199);game_A.sizeset(28,20);break;
		//add new level
	}

	Pse pause_A(game_A.width_get(),game_A.height_get());//Pause declared
	game_A.print_board();
	tmr.print_init();
	curs_set(1);
	mvaddstr(3,60,"press d somewhere to dig, more help press :");
	game_A.control();
	pause_A.read_map("ans");
	tmr.setstart();
	nodelay(stdscr,TRUE);//cause getch() a non-blocking call. if no input return ERR
	int res;
	while(!game_A.get_result()){
		if(game_A.first_dig_get()){
			tmr.print_init();
			tmr.reset();
		}
		else
			tmr.print(res);
		res = 0;
		if(!game_A.control()){
			tmr.stop();
			res = pause_A.Suspend();
			game_A.set_result(res);
			game_A.print_board();
			tmr.Resume();
		}
	}
	nodelay(stdscr,FALSE);

	remove("ans");
	remove("flag");
	remove("map_pause");

	if(game_A.get_result() == 1){
		tmr.print(0);
		mvaddstr(4,60,"U WIN");
		mvaddstr(5,60, "Press anything to leave");
		if(getch()){endwin();return 0;}
	}
	else if(game_A.get_result() == 2){
		tmr.print(0);
		mvaddstr(4,60,"U WIN");
		mvaddstr(4, 60, "U LOSE");
		mvaddstr(5, 60, "Press anything to leave");
		if(getch()){endwin();return 0;}
	}
	else if(game_A.get_result() == 3){
		endwin();
		return 0;
	}
}
