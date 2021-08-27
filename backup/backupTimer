#include"Timer.h"

Timer::Timer(){
	start_ts = 0;
}

void Timer::setstart(){
		start_ts = time(NULL);
}
void Timer::print(int re){
	if(re == 6) reset();
	if(time_stop){
		start_ts=start_ts+time_continue-time_stop;
		time_stop = 0;
	}
	int sec = time(NULL)-start_ts;
	mvprintw(0,60, "              ");
	mvprintw(0,60, "Time:%d:%d:%d",sec/3600,sec/60,sec%60);
}
void Timer::print_init(){
	mvprintw(0,60, "Time:0:0:0");
}
void Timer::stop(){
	time_stop=time(NULL);
}
void Timer::Resume(){
	time_continue=time(NULL);
}
void Timer::reset(){
	time_stop=FALSE;
	time_continue=0;
	start_ts=time(NULL);
}


/*class Timer{
	public:
		Timer();
		Timer(time_t s);
		void start();
		void setStart(time_t ts);
		time_t getStart();
		int getStart();
		int getElapsedTime();

	private:
		time_t start_ts;
};*/
