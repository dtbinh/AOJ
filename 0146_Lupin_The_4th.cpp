
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

struct edge{
	int idx;
	int dist;
	int num;
};

class info{
public:
	double val;
	vector<int> route;
	info() : val(10000000.0){}
};

double calcCost(int S,int n,int u,int v,const vector<edge>& Edge){
	double w=0;
	for(int i=0;i<n;i++){
		if(S & (1<<i)){
			w+=(double)Edge[i].num*20.0;
		}
	}

	double velocity = 2000.0/(70.0+(double)w);
	double dist = abs(Edge[v].dist - Edge[u].dist);

	return dist/velocity;
}


int main(){
	int n;
	scanf("%d",&n);

	info **dp = new info*[(1<<n)];
	for(int i=0;i<=(1<<n)-1;i++) dp[i] = new info[n];

	vector<edge> Edge;

	for(int i=0;i<n;i++){
		int idx,dist,num;
		scanf("%d %d %d",&idx,&dist,&num);
		edge e;
		e.dist = dist;
		e.idx = idx;
		e.num = num;
		Edge.push_back(e);
	}

	for(int i=0;i<n;i++){
		dp[1<<i][i].val = 0;
		dp[1<<i][i].route.push_back(i);
	}

	for(int S=0;S<=(1<<n)-1;S++){
		//from u
		for(int u=0;u<n;u++){
			if(!(S & (1<<u))) continue;
			//to v
			for(int v=0;v<n;v++){
				if(S & (1<<v)) continue;
				double val;
				if(dp[S|(1<<v)][v].val > (val = (dp[S][u].val + calcCost(S,n,u,v,Edge)))){
					dp[S|(1<<v)][v].val = val;
					dp[S|(1<<v)][v].route = dp[S][u].route;
					dp[S|(1<<v)][v].route.push_back(v);
				}
			}
		}
	}

	int min_idx;
	double minv=10000000.0;
	for(int i=0;i<n;i++){
		if(dp[(1<<n)-1][i].val < minv){
			minv = dp[(1<<n)-1][i].val;
			min_idx = i;
		}
	}

	for(int i=0;i<dp[(1<<n)-1][min_idx].route.size();i++){
		printf("%d%s",Edge[dp[(1<<n)-1][min_idx].route[i]].idx,i == dp[(1<<n)-1][min_idx].route.size() - 1 ? "\n" : " ");
	}

	for(int i=0;i<=(1<<n)-1;i++) delete[] dp[i];
	delete[] dp;

}

