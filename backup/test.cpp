#include<iostream>
#include<time.h>
#include<ncurses.h>
using namespace std;

class recur{
	public:
		recur(){x=5;}
		int fact(int a){
			if(a == 1) {
				return 1;
			}
			else{ 
				return a*(fact(a-1));
			}
		}
		void execute(){
			cout << "x=" << x << endl;
			cout << "fact(x)="<< fact(x) << endl;
			cout << "x after is " << x;
		}
	private:
		int x;
};

int main(){
	recur A;
	A.execute();
return 0;
}
