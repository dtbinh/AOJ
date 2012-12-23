
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
typedef pair <int,int> P;
typedef pair <int,P > PP;

static const double eps = 1e-8;

int path[101][101];
int used[101][11];

void bfs(int s,int d,int n,int c){
	priority_queue<PP,vector<PP>,greater<PP> > que;
	que.push(PP(0,P(s,c)));
	used[s][c] = 0;

	while(!que.empty()){
		int cost = que.top().first;
		int src = que.top().second.first;
		int ticket = que.top().second.second;
		que.pop();

		for(int dst=1;dst<=n;dst++){
			if(used[dst][ticket] > cost + path[src][dst]){
				used[dst][ticket] = cost + path[src][dst];
				que.push(PP(cost + path[src][dst],P(dst,ticket)));
			}

			if(ticket > 0 && used[dst][ticket-1] > cost + path[src][dst]/2){
				used[dst][ticket-1] = cost + path[src][dst]/2;
				que.push(PP(cost + path[src][dst]/2,P(dst,ticket-1)));
			}
		}
	}
}

int main(){
	//c:number of tickets
	//n:number of towns
	//m:number of buses
	//s:source
	//d:destination
	int c,n,m,s,d;
	while(~scanf("%d %d %d %d %d",&c,&n,&m,&s,&d)){
		if(c==n && n==m && m==s && s==d && d==0) break;
		memset(path,0x3,sizeof(path));
		memset(used,0x3,sizeof(used));

		for(int i=0;i<m;i++){
			int a,b,f;
			scanf("%d %d %d",&a,&b,&f);
			path[a][b] = path[b][a] = min(path[a][b],f);
		}

		bfs(s,d,n,c);
		int res=numeric_limits<int>::max();
		for(int i=c;i>=0;i--) res = min(res,used[d][i]);
		printf("%d\n",res);
	}
}


