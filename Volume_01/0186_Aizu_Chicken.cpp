
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

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	int q1;
	while(~scanf("%d",&q1)){
		if(q1==0) break;
		int b,c1,c2,q2;
		//1:aize chicken 2:normal chicken
		scanf("%d %d %d %d",&b,&c1,&c2,&q2);
		for(int i=q2;i>=1;i--){//i:total number of aizu chickens
			int cost = i*c1;
			if(cost > b) continue;
			int ub = 1000000;
			int lb = 0;

			for(int j=0;j<20;j++){
				int md = (ub+lb)/2;
				if(cost + md*c2 <=b) lb = md; // lb:total number of normal chickens
				else ub = md;
			}

			if(lb+i >= q1 && cost + lb*c2 <=b){
				printf("%d %d\n",i,lb);
				goto next;
			}
		}
		printf("NA\n");
next:;
	}
}

