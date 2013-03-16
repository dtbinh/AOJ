
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;


int main(){

	double w;
	while(~scanf("%lf",&w)){
		if(w <= 48.0){
			cout << "light fly" << endl;
		}
		else if(48.0 < w && w <= 51.0){
			cout << "fly" << endl;
		}
		else if(51.0 < w && w <= 54.0){
			cout << "bantam" << endl;
		}
		else if(54.0 < w && w <= 57.0){
			cout << "feather" << endl;
		}
		else if(57.0 < w && w <= 60.0){
			cout << "light" << endl;
		}
		else if(60.0 < w && w <= 64.0){
			cout << "light welter" << endl;
		}
		else if(64.0 < w && w <= 69.0){
			cout << "welter" << endl;
		}
		else if(69.0 < w && w <= 75.0){
			cout << "light middle" << endl;
		}
		else if(75.0 < w && w <= 81.0){
			cout << "middle" << endl;
		}
		else if(81.0 < w && w <= 91.0){
			cout << "light heavy" << endl;
		}
		else if(91.0 < w){
			cout << "heavy" << endl;
		}
	}
}

