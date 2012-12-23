
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

struct Edge{
	int b;
	int x;
	int y;
};

vector<int> get_path(int t,int* prev){
	vector<int> path;
	for(; t!=-1; t = prev[t]) path.push_back(t);
	reverse(path.begin(),path.end());
	return path;
}

vector<int> dijkstra(int src,int dst, const vector<Edge>& edge){
	
	double d[1001];
	int prev[1001];
	bool used[1001];

	fill((double*)d,(double*)d+1001,10000000.0);
	fill((bool*)used,(bool*)used+1001,false);
	fill((int*)prev,(int*)prev+1001,-1);

	d[src] = 0.0;	

	while(true){

		int v = -1;
		for(int u=0;u<edge.size();u++){
			if(!used[u] && (v == -1 || d[u] < d[v])) v = u;
		}

		if(v == -1) break;
		used[v] = true;

		int srcX = edge[v].x;
		int srcY = edge[v].y;

		for(int u=0;u<edge.size();u++){
			if(u==v) continue;
			double cost = sqrt((double)(edge[u].x - srcX) * (double)(edge[u].x - srcX)
				+ (double)(edge[u].y - srcY) * (double)(edge[u].y - srcY));
			if(cost > 50.0) continue;

			if(d[u] > d[v] + cost){
				d[u] = d[v] + cost;
				prev[u] = v;
				//printf("u:%d v:%d\n",u+1,v+1);
			}
		}
	}
/*
	for(int i=0;i<edge.size();i++){
		printf("d[%d]=%d ",i+1,d[i]);
	}
	cout << endl;
*/
	return get_path(dst,prev);
}

int main(){
	string str;

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		vector<Edge> edge;
		for(int i=0;i<n;i++){
			int b,x,y;
			scanf("%d %d %d",&b,&x,&y);
			Edge e = {b,x,y};
			edge.push_back(e);
		}
		int m;
		scanf("%d",&m);

		for(int i=0;i<m;i++){
			int src,dst;
			scanf("%d %d",&src,&dst);
			int src_idx,dst_idx;
			for(int i=0;i<edge.size();i++){
				if(edge[i].b == src){
					src_idx = i;
				}
				if(edge[i].b == dst){
					dst_idx = i;
				}
			}

			vector<int> route = dijkstra(src_idx,dst_idx,edge);

			if(route[0] == src_idx && route[route.size()-1] == dst_idx){
				for(int j=0;j<route.size();j++){
					printf("%d%s",edge[route[j]].b,j == route.size() -1 ? "\n" : " ");
				}
			}
			else cout << "NA" << endl; 
		}
	}
}

