#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int randRange(int min, int max);

int main(int argc, char** argv){
	int mini, maxi, i;
	int cnt;
	srand(time(NULL));
	cout << "min? ";
	cin >> mini;
	cout << "max? ";
	cin >> maxi;
	cnt = (int)(*argv[1]) - '0';
	for(i=0;i<cnt;i++)
		cout << randRange(mini, maxi) << endl;
}

int randRange(int min, int max){
	int sum = max - min;
	return rand()%sum + min;
}
