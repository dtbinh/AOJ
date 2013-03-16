
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
	int n,m;
	while(~scanf("%d",&n)){
		if(n==0) break;
		scanf("%d",&m);

		int* mincost = new int[n];
		bool* used = new bool[n];

		fill((bool*)used,(bool*)used + n,false);
		fill((int*)mincost,(int*)mincost + n,numeric_limits<int>::max());


		int** cost = new int*[n];
		for(int i=0;i<n;i++){
			cost[i] = new int[n];
			for(int j=0;j<n;j++){
				cost[i][j]=numeric_limits<int>::max();
			}
		}
		
		for(int i=0;i<m;i++){
			int from,to,dist;
			scanf("%d,%d,%d",&from,&to,&dist);
			cost[from][to] = min(cost[from][to],dist / 100 - 1);
			cost[to][from] = min(cost[to][from],dist / 100 - 1);
		}

		mincost[0]=0;

		int res=0;
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
				mincost[u] = min(mincost[u],cost[v][u]);
			}
			
		}

		cout << res << endl;

		for(int i=0;i<n;i++){
			delete[] cost[i];
		}

		delete[] cost;
	}
}

