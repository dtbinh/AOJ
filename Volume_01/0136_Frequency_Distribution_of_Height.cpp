
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
typedef pair<char,int> P;

static const double eps = 10e-9;

int main(){
	int n;
	double table[]={165.0,170.0,175.0,180.0,185.0};
	int hist[] = {0,0,0,0,0,0};
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			double tall;
			scanf("%lf",&tall);
			int idx=5;
			for(int j=0;j<sizeof(table)/sizeof(double);j++){
				if(table[j] > tall){
					idx = j;
					break;
				}
			}
			hist[idx]++;
		}

		for(int i=0;i<sizeof(hist)/sizeof(int);i++){
			printf("%d:",i+1);
			for(int j=0;j<hist[i];j++){
				cout << "*";
			}
			cout << endl;
		}
	}
}

