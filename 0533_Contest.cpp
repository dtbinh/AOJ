
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
typedef pair <int,int> P;

static const double EPS = 1e-8;

int main(){
	int p1[10],p2[10];
	for(int i=0;i<2;i++){
		for(int j=0;j<10;j++){
			if(i==0) scanf("%d",p1+j);
			else scanf("%d",p2+j);
		}
	}

	sort(p1,p1+10,greater<int>());
	sort(p2,p2+10,greater<int>());
	printf("%d %d\n",p1[0]+p1[1]+p1[2],p2[0]+p2[1]+p2[2]);
}

