#include"Game.h"

Game::Game(){
	result = 0;
	x = 0;
	y = 0;
	for(i=0;i<size_max;i++){
		for(j=0;j<size_max;j++){
			map[i][j] = 0;
			flag_posi[i][j] = 0;
		}
	}
	hint_time = 3;
	DIE = TRUE;
	first_dig=TRUE;
}
void Game::bombset(int bomb_num){
	bomb = bomb_num;
}
void Game::sizeset(int wid, int hei){
	width = wid;
	height = hei;
}
int Game::width_get(){
	return width;
}
int Game::height_get(){
	return height;
}
bool Game::first_dig_get(){
	return first_dig;
}
void Game::print_board(){
	for(j=1;j<=height*2;j+=2)
		for(i=0;i<=width*2-1;i++)
			mvaddstr(j, i, "-");
	for(j=1;j<=width*2;j+=2)
		for(i=0;i<=height*2-1;i++)
			mvaddstr(i, j, "|");
	mvprintw(2,60,"Hint times:%d", hint_time);
}
void Game::map_generate(){
	for(i=0;i<size_max;i++){
		for(j=0;j<size_max;j++){
			map[i][j] = 0;
			flag_posi[i][j] = 0;
		}
	}
	int a,b,k;
	int check[bomb] = {0};
	srand(time(NULL));
	for(i=0;i<bomb;i++){
		check[i] = rand()%(width*height);
		//mvprintw(i+30, 0, "check[%d]=%d", i, check[i]);//For Test
		if(check[i]%width - x/2 ==  1){i--;continue;}
		if(check[i]/width - y/2 ==  1){i--;continue;}
		if(check[i]%width - x/2 == -1){i--;continue;}
		if(check[i]/width - y/2 == -1){i--;continue;}
		if(check[i] == x/2+(y*width/2)){i--;continue;}
		for(j=0;j<i;j++)
			if(check[i] == check[j]){i--;break;}
		//avoid the bomb next to first point
	}
	for(i=0;i<bomb;i++){
		map[check[i]%width][check[i]/width] = 9;
		/*attrset(A_BOLD|COLOR_PAIR(1));
		mvaddstr(2*(check[i]/width), 2*(check[i]%width), "b");//show bomb position
		attrset(A_NORMAL);*/
	}
	for(i=0;i< bomb;i++){
		a = check[i]%width;
		b = check[i]/width;
		for(k=a-1;k<a+2;k++){
			if(k<0 || k>= width) continue;
			for(j=b-1;j<b+2;j++){
				if(j<0 || j>=height) continue;
				if(map[k][j] != 9) map[k][j]++;
				else continue;
			}
		}
	}
	/*for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			mvprintw(j,8*i+30,"(%d,%d)=%d",i,j,map[i][j]);}}*/ //show the stored num
}
void Game::Output_map(string s){
	ofstream Map_out(s, ios::out);
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
			if(map[i][j] != 9)
				Map_out << map[i][j] << " ";
			else
				Map_out << "b ";
		}
		Map_out << endl;
	}
}
void Game::Out_Read_map(string s){
	ofstream Flag_out("flag", ios::out);
	ofstream Map_out(s, ios:: out);
	for(j=0;j<height;j++){
		for(i=0;i<width;i++){
				Map_out << map[i][j] << " ";
				Flag_out << flag_posi[i][j] << " ";
				
		}
	}
}
	
void Game::vision(){
	Expansion(x/2, y/2);
	for(i=0;i<width;i++){
		for(j=0;j<height;j++){
			if(map[i][j] != -1 && map[i][j] != 9) return;
			if(j == height-1 && i == width -1) result = 1;//win
		}
	}
}
void Game::Expansion(int x_cor, int y_cor){
	if(x_cor < 0 || x_cor >= width || y_cor < 0 || y_cor >= height)
		return;
	else if(map[x_cor][y_cor] == 0){
		mvaddstr(y_cor*2,x_cor*2,"0");
		map[x_cor][y_cor] = -1;
	}
	else if(map[x_cor][y_cor] != 9 && map[x_cor][y_cor] != -1){
		mvprintw(2*y_cor, 2*x_cor, "%d", map[x_cor][y_cor]);
		map[x_cor][y_cor] = -1;
		return;
	}
	else return;
	Expansion(x_cor+1,y_cor);
	Expansion(x_cor-1,y_cor);
	Expansion(x_cor,y_cor+1);
	Expansion(x_cor,y_cor-1);
	Expansion(x_cor+1,y_cor+1);
	Expansion(x_cor+1,y_cor-1);
	Expansion(x_cor-1,y_cor+1);
	Expansion(x_cor-1,y_cor-1);
}
void Game::Flag(){
	if(flag_posi[x/2][y/2] == 0 && map[x/2][y/2] != -1){
		flag_posi[x/2][y/2] = 1;
		attrset(A_BOLD|COLOR_PAIR(3));
		mvaddstr(y,x,"f");
		attrset(A_NORMAL);
	}
	else if(flag_posi[x/2][y/2] == 1 && map[x/2][y/2] != -1){
		mvaddstr(y,x," ");
		flag_posi[x/2][y/2] = 0;
	}
}
void Game::hint(){
	if(!hint_time){
		mvaddstr(3,60,"U have no HINTTTTTTTTTT QQ");
		return;}
	for(i=x/2-1;i<x/2+2;i++){
		if(i<0 || i>=width) continue;
		for(j=y/2-1;j<y/2+2;j++){
			if(j<0 || j>=height) continue;
			if(map[i][j] == 9){
				attrset(A_BOLD|COLOR_PAIR(1));
				mvaddstr(2*j,2*i,"b");
				flag_posi[i][j] =2;
			}
			else if(map[i][j] == -1) continue;
			else {
				attrset(A_NORMAL);
				mvprintw(j*2,i*2,"%d",map[i][j]);
				map[i][j] = -1;
			}
		}
	}
	vision();
	attrset(A_NORMAL);
	--hint_time;
	mvprintw(2,72,"     ");
	mvprintw(2,60,"Hint times:%d", hint_time);
	return;
}
bool Game::control(){
	static int WOOPs = 6;
	int c;
	bool go_on = TRUE;
	while(go_on){
		move(y,x);
		while((c = getch()) == ERR)return TRUE;
		switch(c){
			case KEY_LEFT: x-=2;break;
			case KEY_RIGHT: x+=2;break;
			case KEY_UP: y-=2;break;
			case KEY_DOWN: y+=2;break;
			case 'f': if(!first_dig){
					  Flag();
				  	  break;
				  }
				  else break;
			case 'd': if(first_dig){
					map_generate();
					Output_map("Mine.txt");
					Out_Read_map("ans");
					vision();
					first_dig = FALSE;
					return TRUE;
				  }//first_dig
				  else if(map[x/2][y/2] == 9 && DIE == TRUE){
					result=2;
					attrset(A_BOLD|COLOR_PAIR(1));
					mvaddstr(y,x,"b");
					attrset(A_NORMAL);
					return TRUE;
				  }//lose
				  else if(map[x/2][y/2] == 9 && DIE == FALSE){
					flag_posi[x/2][y/2] = 2;
					attrset(A_BOLD|COLOR_PAIR(1));
					mvaddstr(y,x,"b");
					attrset(A_NORMAL);
					mvaddstr(WOOPs++,60,"WOOPs!!!");
					return TRUE;
				  }//DIE off
				  else if(map[x/2][y/2] == -1)
					break;
				  else
					result = 0;
					vision();
					return TRUE;
			case 'h': if(!first_dig)
					  hint();
				  	  break;
			case ':': if(!first_dig){
					  WOOPs = 6;
					  Out_Read_map("map_pause");
					  return FALSE;
				  }
				  else break;
			default: break;
		}//switch
		if(x<0) x=0;
		if(x>=2*width) x=2*width-2;
		if(y<0) y=0;
		if(y>=2*height) y=2*height-2;
	}//while
}
void Game::set_result(int a){
	result = a;
	if(result == 4){
		hint_time+=1000;
		result = 0;
	}
	if(result == 5){
		if(DIE) DIE=FALSE;
		else DIE=TRUE;
		result = 0;
	}
	if(result == 6){
		map_generate();
		hint_time = 3;
		first_dig = TRUE;
		result = 0;
	}
}
int Game::get_result(){
	return result;
	//0:continue|1:win|2:lose|3:exit
	}
//int map[size_max][size_max];
//int bomb;
//int width,height;
//int i, j;
//int x, y;
//int result
//int  flag_posi[size_max][size_max]
