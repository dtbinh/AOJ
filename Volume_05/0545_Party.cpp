
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

int path[501][501];


int main(){
	int N,M;
	while(~scanf("%d %d",&N,&M)){
		if(N==M && M==0) break;
		memset(path,0,sizeof(path));
		for(int i=0;i<M;i++){
			int a,b;
			scanf("%d %d",&a,&b);
			path[a][b] = path[b][a] = 1;
		}

		priority_queue<P,vector<P>,greater<P> > que;
		que.push(P(0,1));
		map<int,int> visited;
		visited[1] = 1;

		int res=0;
		while(!que.empty()){
			int cost = que.top().first;
			int now = que.top().second;

			if(cost >= 2) break;

			que.pop();
			for(int i=2;i<=N;i++){
				if(path[now][i]==1 && visited.find(i) == visited.end()){
					visited[i] = 1;
					res++;
					que.push(P(cost+1,i));
				}
			}

		}

		printf("%d\n",res);
	}
}

