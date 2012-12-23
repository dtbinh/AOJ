
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

static const int t[][2] = {{1,0},{0,1},{-1,0},{0,-1}};
static const int s[][2] = {{0,2},{1,1},{1,2},{1,3},
{2,0},{2,1},{2,2},{2,3},{2,4},{3,1},{3,2},{3,3},{4,2}};

void bfsRoot(map<vector< vector<int> >,int>& cost,vector< vector<int> >& rv){
	cost[rv] = 0;
	queue<vector< vector<int> > > que;
	que.push(rv);

	while(!que.empty()){
		vector< vector<int> > now = que.front();
		que.pop();

		for(int i=0;i<13;i++){
			int x = s[i][1];
			int y = s[i][0];
			if(now[y][x] != 0) continue;

			for(int j=0;j<4;j++){
				int dx = x + t[j][0];
				int dy = y + t[j][1];

				if(dy < 0 || dy >= 5 || dx < 0 || dx >= 5) continue;
				if(now[dy][dx] == -1) continue;
				if(now[dy][dx] == 0) continue;

				vector< vector<int> > tmp = now;
				swap(tmp[y][x],tmp[dy][dx]);

				if(cost.find(tmp) != cost.end()) continue;
				cost[tmp] = cost[now] + 1;
				if(cost[tmp] >= 10) continue;
				que.push(tmp);
			}
		}
	}
}

int bfs(map<vector< vector<int> >,int>& cost,vector< vector<int> >& rv,
	map<vector< vector<int> >,int>& costR){
	cost[rv] = 0;
	queue<vector< vector<int> > > que;
	que.push(rv);

	if(costR.find(rv) != costR.end()) return costR[rv];

	while(!que.empty()){
		vector< vector<int> > now = que.front();
		que.pop();

		for(int i=0;i<13;i++){
			int x = s[i][1];
			int y = s[i][0];
			if(now[y][x] != 0) continue;

			for(int j=0;j<4;j++){
				int dx = x + t[j][0];
				int dy = y + t[j][1];

				if(dy < 0 || dy >= 5 || dx < 0 || dx >= 5) continue;
				if(now[dy][dx] == -1) continue;
				if(now[dy][dx] == 0) continue;

				vector< vector<int> > tmp = now;
				swap(tmp[y][x],tmp[dy][dx]);

				if(cost.find(tmp) != cost.end()) continue;

				cost[tmp] = cost[now] + 1;
				if(costR.find(tmp) != costR.end()) return costR[tmp] + cost[tmp]; 

				if(cost[tmp] >= 10) continue;
				que.push(tmp);
			}
		}
	}

	return -1;
}

int main(){
	int table[5][5];
	int root[5][5];
	memset(table,-1,sizeof(table));
	memset(root,-1,sizeof(root));
	root[0][2] = 0;
	root[1][1]=1; root[1][2]=2; root[1][3]=3;
	root[2][0]=4; root[2][1]=5; root[2][2]=6; root[2][3]=7; root[2][4]=8;
	root[3][1]=9; root[3][2]=10; root[3][3]=11;
	root[4][2] = 0;

	vector< vector<int> > rv(5,vector<int>(5));
	map<vector< vector<int> >,int> costR;
	

	for(int y=0;y<5;y++){
		for(int x=0;x<5;x++){
			rv[y][x] = root[y][x];
		}
	}
	bfsRoot(costR,rv);

	while(~scanf("%d",&table[0][2])){
		if(table[0][2] == -1) break;
		scanf("%d %d %d",&table[1][1],&table[1][2],&table[1][3]);
		scanf("%d %d %d %d %d",&table[2][0],&table[2][1],&table[2][2],&table[2][3],&table[2][4]);
		scanf("%d %d %d",&table[3][1],&table[3][2],&table[3][3]);
		scanf("%d",&table[4][2]);
		vector< vector<int> > tv(5,vector<int>(5));

		for(int y=0;y<5;y++){
			for(int x=0;x<5;x++){
				tv[y][x] = table[y][x];
			}
		}
		map<vector< vector<int> >,int> cost;
		int res = bfs(cost,tv,costR);

		if(res != -1) printf("%d\n",res);
		else printf("NA\n");
	}
}

