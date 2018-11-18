#include <iostream>
#include <string>
using namespace std;

template <typename T>
T* sort(T* arr){
	int i, j;
	T p;
	for(i=0;i<9;i++){
		for(j=i+1;j<10;j++){
			if(arr[i] < arr[j]){
				p = arr[i];
				arr[i] = arr[j];
				arr[j] = p;
			}
		}
	}
	return arr;
}

template <>
string* sort<string>(string* arr){
	int i, j;
	string p;
	for(i=0;i<9;i++){
		for(j=i+1;j<10;j++){
			if(arr[i].compare(arr[j]) > 0){
				p = arr[i];
				arr[i] = arr[j];
				arr[j] = p;
			}
		}
	}
	return arr;
}

int main(int argc, char** argv){
	string type;
	int i;
	string* stringarr;
	int* intarr;
	char* chararr;
	float* floatarr;
	double* doublearr;
	cout << "which type do you want to sort? ";
	cin >> 	type;
	if(!type.compare("string")){
		stringarr = new string[10];
		for(i=0;i<10;i++) cin >> stringarr[i];
		stringarr = sort(stringarr);
		for(i=0;i<10;i++) cout << stringarr[i] << " ";
		delete[] stringarr;
	}else if(!type.compare("char")){
		chararr = new char[10];
		for(i=0;i<10;i++) cin >> chararr[i];
		chararr = sort(chararr);
		for(i=0;i<10;i++) cout << chararr[i] << " ";
		delete[] chararr;
	}else if(!type.compare("int")){
		intarr = new int[10];
		for(i=0;i<10;i++) cin >> intarr[i];
		intarr = sort(intarr);
		for(i=0;i<10;i++) cout << intarr[i] << " ";
		delete[] intarr;
	}else if(!type.compare("float")){
		floatarr = new float[10];
		for(i=0;i<10;i++) cin >> floatarr[i];
		floatarr = sort(floatarr);
		for(i=0;i<10;i++) cout << floatarr[i] << " ";
		delete[] floatarr;
	}else if(!type.compare("double")){
		doublearr = new double[10];
		for(i=0;i<10;i++) cin >> doublearr[i];
		doublearr = sort(doublearr);
		for(i=0;i<10;i++) cout << doublearr[i] << " ";
		delete[] doublearr;
	}
}
