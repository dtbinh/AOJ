
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

int path[101][101];

int main(){
	string str;
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) continue;
		
		int* mincost = new int[n];
		bool* used = new bool[n];

		fill((bool*)used,(bool*)used + n,false);
		fill((int*)mincost,(int*)mincost+n,INF);
		fill((int*)path,(int*)path+101*101,INF);

		for(int i=0;i<m;i++){
			int a,b,cost;
			scanf("%d %d %d",&a,&b,&cost);
			path[a][b] = min(cost,path[a][b]);
			path[b][a] = min(cost,path[b][a]);
		}

		int res=0;
		mincost[0] = 0;

		while(1){
			int v=-1;
			for(int u=0;u<n;u++){
				if(!used[u] && (v==-1 || mincost[u] < mincost[v])){
					v = u;
				}
			}

			if(v==-1) break;
			used[v] = true;		

			res+=mincost[v];
			
			for(int u=0;u<n;u++){
				mincost[u] = min(mincost[u],path[v][u]);
			}
			
		}

		printf("%d\n",res);

		delete[] mincost;
		delete[] used;
	}
}

