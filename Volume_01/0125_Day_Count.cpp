
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
typedef pair<string,int> P;

bool isLeap(int i){
	return i % 400 == 0 
			? true : i % 100 == 0
			? false : i % 4 == 0
			? true : false;
}

int getSum(int y,int m,int d,const int* month){
	int sum=0;
	for(int i=0;i<y;i++){
		sum += isLeap(i) ? 366 : 365;
	}

	for(int i=1;i<m;i++){
		sum += i != 2 ? month[i] :
			isLeap(y) ? month[i] + 1 : month[i];
	}

	sum += d;

	return sum;
}

int main(){
	const int month[] = {-1,31,28,31,30,31,30,31,31,30,31,30,31};
	int y1, m1, d1, y2, m2, d2;
	while(~scanf("%d %d %d %d %d %d",&y1, &m1, &d1, &y2, &m2, &d2)){
		if(y1 < 0 || m1 < 0 || d1 < 0
			|| y2 < 0 || m2 < 0 || d2 < 0) break;

		cout << abs(getSum(y1,m1,d1,month) - getSum(y2,m2,d2,month)) << endl;
	}
}


