
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
typedef pair<int,vector<int> > P;

void bfs(const vector<int>& tmp,int cost[8][8],int N,map<vector<int>,int>& visited){
	priority_queue<P,vector<P>,greater<P> > que;
	que.push(P(0,tmp));

	visited[tmp] = 0;
	vector<int> now;
	vector<int> next;
	while(!que.empty()){
		now = que.top().second;
		int costNow = que.top().first;
		que.pop();
		for(int i=0;i<N;i++){
			for(int j=i+1;j<N;j++){
				swap(now[i],now[j]);
				next = now;
				swap(now[i],now[j]);

				int c;
				if(visited[next] <= (c = (costNow + cost[i][j]))) continue;
				visited[next] = c;
				que.push(P(visited[next],next));
			}
		}
	}

}

int main(){
	int N;

	int cost[8][8];
	memset(cost,0x3,sizeof(cost));

	map<vector<int>,int> visited;

	while(~scanf("%d",&N)){
		for(int y=0;y<N;y++){
			for(int x=0;x<N;x++){
				int c;
				scanf("%d",&c);
				cost[y][x] = c;
			}
		}

		vector<int> tmp;
		for(int i=0;i<N;i++){
			tmp.push_back(i);
		}

		do{
			visited[tmp] = 5000000;
		}while(next_permutation(tmp.begin(),tmp.end()));

		bfs(tmp,cost,N,visited);

		int res=0;

		for(map<vector<int>,int>::iterator it = visited.begin(); it != visited.end(); it++){
			res = max(res,it->second);
		}

		printf("%d\n",res);
	}

}

