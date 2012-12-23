
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <bitset>
#include <list>

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	int a,b;
	while(~scanf("%d %d",&a,&b)){
		if(a==b && b==0) break;

		int X,Y;
		if(a>=b){
			X = a;
			Y = b;
		}
		else{
			X = b;
			Y = a;
		}

		int count = 0;
		while(Y!=0){
			X = X % Y;
			swap(X,Y);
			count++;
		}

		printf("%d %d\n",X,count);
	}
}

