#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(void) {
	string type;
    string temps;
    int i, tempi;
	cout << "Type: ";
	cin >> type;
	cout << "Input: ";
    if(type.compare("integer")){
        vector<string> arr;
        for(i=0;i<5;i++){
            cin >> temps;
            arr.push_back(temps);
        }
        vector<string>::iterator itr;
        for(itr = arr.begin(); itr != arr.end(); itr++){
            if((*itr)[0] != 'c') cout << *itr << " ";
        }
    }else{
        vector<int> num;
        for(i=0;i<5;i++){
            cin >> tempi;
            num.push_back(tempi);
        }
        vector<int>::iterator itri;
        for(itri = num.begin(); itri != num.end(); itri++){
            if(*itri%2 == 0) cout << *itri << " ";
        }
    }
}