
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
	int a,b,c;
	while(~scanf("%d %d %d",&a,&b,&c)){
		if(a==b && b==c && c== -1) break;

		int remain1 = 120 * 60 - (a*60*60+b*60+c);
		int h = remain1 / 3600;
		int remain2 = remain1 % 3600;
		int m = remain2 / 60;
		int s = remain2 % 60;
		printf("%02d:%02d:%02d\n",h,m,s);


		remain1*=3;
		h = remain1 / 3600;
		remain2 = remain1 % 3600;
		m = remain2 / 60;
		s = remain2 % 60;
		printf("%02d:%02d:%02d\n",h,m,s);
	}
}

