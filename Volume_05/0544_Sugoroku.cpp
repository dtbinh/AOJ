
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


int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};

int stage[1000];

int main(){
	int N,M;
	while(~scanf("%d %d",&N,&M)){
		if(N==M && M==0) break;
		for(int i=0;i<N;i++){
			int v;
			scanf("%d",&v);
			stage[i] = v;
		}

		int pos=0;
		int res=INF;
		for(int i=0;i<M;i++){
			int v;
			scanf("%d",&v);
			if(pos+v >= N-1){
				res = min(i+1,res);
				continue;
			}

			pos = (pos+v) + stage[(pos+v)];

			if(pos >= N-1){
				res = min(i+1,res);
				continue;
			}
		}

		printf("%d\n",res);
	}
}

