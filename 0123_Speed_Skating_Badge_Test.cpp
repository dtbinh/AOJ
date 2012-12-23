
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
#include <set>
#include <deque>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

int main(){
	double a,b;
	

	double table1[] = {35.5,37.5,40.0,43.0,50.0,55.0,70.0};
	double table2[] = {71.0,77.0,83.0,89.0,105.0,116.0,148.0};
	string rank[] = {"AAA","AA","A","B","C","D","E","NA"};

	while(~scanf("%lf %lf",&a,&b)){
		int c=7,d=7;
		for(int i=0;i<sizeof(table1)/sizeof(double);i++){
			if(a < table1[i]) { c = i; break; }
		}

		for(int i=0;i<sizeof(table2)/sizeof(double);i++){
			if(b < table2[i]) { d = i; break; }
		}

		cout << rank[max(c,d)] << endl;

	}
}


