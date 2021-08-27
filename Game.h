#include<iostream>
#include<fstream>
#include<ncurses.h>
#include<time.h>
#include<string>
#include<unistd.h>
#define size_max 30
using namespace std;

class Game{
	public:
		Game();
		void bombset(int bomb_num);
		void sizeset(int wid, int hei);
		int width_get();
		int height_get();
		bool first_dig_get();
		void print_board();
		void map_generate();
		void Output_map(string s);
		void Out_Read_map(string s);
		bool control();
		void vision();
		void Flag();
		void Expansion(int x_cor, int y_cor);
		void hint();
		void set_result(int a);
		int  get_result();
	private:
		short int map[size_max][size_max];
		int bomb;
		int width;
		int height;
		int i, j;
		int x, y;
		int result;
		bool first_dig;
		int flag_posi[size_max][size_max];
		int hint_time;
		bool DIE;
};
