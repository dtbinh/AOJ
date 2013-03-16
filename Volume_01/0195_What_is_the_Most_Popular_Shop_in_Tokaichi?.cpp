
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
typedef pair<int,int> P;

static const double eps = 1e-8;

int main(){
	int am,pm;
	while(~scanf("%d %d",&am,&pm)){
		if(am == pm && pm == 0) break;
		int maxV = -1;
		char alph;
		if(maxV < am+pm){
			alph = 'A';
			maxV = am+pm;
		}
		for(int i=0;i<4;i++){
			scanf("%d %d",&am,&pm);
			if(maxV < am+pm){
				alph = 'A'+i+1;
				maxV = am+pm;
			}
		}
		printf("%c %d\n",alph,maxV);
	}
}

