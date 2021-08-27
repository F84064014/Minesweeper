#include<iostream>
#include<ctime>
#include<ncurses.h>
using namespace std;

class Timer{
	public:
		Timer();
		void setstart();
		void print_init();
		void print(int re);
		void stop();
		void Resume();
		void reset();
	private:
		time_t start_ts;
		time_t time_stop;
		time_t time_continue;
};
