#include<iostream>
#include<string>
#include<fstream>
#include<ncurses.h>
#include<stdio.h>
#define max_size 30
using namespace std;

class Pse{
	public:
		Pse(int w, int h);
		int Suspend();
		void Continue();
		void read_map(string s);
		void check_map();
		void HELP();
		void print_ans();
		void How();
	private:
		int map[max_size][max_size];
		int answer[max_size][max_size];
		int flag[max_size][max_size];
		int i,j;
		int width, height;
};	
