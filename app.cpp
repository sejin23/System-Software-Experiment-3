#include <iostream>
#include <string>
#include <cmath>
using namespace std;
typedef struct point{
	int i, j;
	float a[5];
}Point;
class Area{
	public:
		int cnt, max;
		Point x[5];
		virtual float compute(){
			cout << 0 << endl;
		};
		virtual void setPoint(int i, int j) = 0;
};
class triangle: public Area{
	public:
		triangle(){
			cnt = 0;
			max = 3;
		}
		float compute(){
			int i;
			float a[3];
			float p, q, s;
			for(i=0;i<3;i++){
				p = x[i%3].i - x[(i+1)%3].i;
				q = x[i%3].j - x[(i+1)%3].j;
				a[i] = sqrt(p*p + q*q);
			}
			s = (a[0]+a[1]+a[2])/2;
			return sqrt(s*(s-a[0])*(s-a[1])*(s-a[2]));
		}
		void setPoint(int i, int j){
			if(cnt < max){
				x[cnt].i = i;
				x[cnt].j = j;
				cnt++;
			}
		}
};

class rectangle: public Area{
	public:
		rectangle(){
			cnt = 0;
			max = 4;
		}
		float compute(){
			int i;
			int a[2];
			for(i=0;i<4;i++){
				if(x[i%4].i != x[(i+1)%4].i){
					a[0] = x[i%4].i - x[(i+1)%4].i;
					if(a[0] < 0) a[0] = 0 - a[0];
				}
				if(x[i%4].j != x[(i+1)%4].j){
					a[1] = x[i%4].j - x[(i+1)%4].j;
					if(a[1] < 0) a[1] = 0 - a[1];
				}
			}
			return (float)(a[0]*a[1]);
		}
		void setPoint(int i, int j){
			if(cnt < max){
				x[cnt].i = i;
				x[cnt].j = j;
				cnt++;
			}
		}
};

class pentagon: public Area{
	public:
		pentagon(){
			cnt = 0;
			max = 5;
		}
		float compute(){
			int i;
			float min = 10000;
			float p, q, s;
			for(i=1;i<5;i++){
				p = x[0].i - x[i].i;
				q = x[0].j - x[i].j;
				s = sqrt(p*p + q*q);
				if(min > s) min = s;
			}
			return min;
		}
		void setPoint(int i, int j){
			if(cnt < max){
				x[cnt].i = i;
				x[cnt].j = j;
				cnt++;
			}
		}
};

int main()
{
	int i, j, k;
	float  result;
	string fig;
	Area* figure;
	cout << "Figure: ";
	cin >> fig;
	if(!fig.compare("triangle")){
		figure = new triangle();
		for(i=0;i<3;i++){
			cout << "Point" << i+1 << ": ";
			cin >> j >> k;
			figure->setPoint(j, k);
		}
		result = figure->compute();
	}else if(!fig.compare("rectangle")){
		figure = new rectangle();
		for(i=0;i<4;i++){
			cout << "Point" << i+1 << ": ";
			cin >> j >> k;
			figure->setPoint(j, k);
		}
		result = figure->compute();
	}else if(!fig.compare("pentagon")){
		figure = new pentagon();
		for(i=0;i<5;i++){
			cout << "Point" << i+1 << ": ";
			cin >> j >> k;
			figure->setPoint(j, k);
		}
		result = figure->compute();
	}
	cout << "Area: " << result << endl;
	delete figure;
	return 0;
}