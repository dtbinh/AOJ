
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
typedef pair <int,P> PP;
typedef pair <PP,bitset<8100> > Pv;

static const double EPS = 1e-8;


int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};

int main(){
	int m,n;
	while(~scanf("%d %d",&m,&n)){
		if(m==n && n==0) break;

		vector<P> pos;

		bitset<8100> field;
		for(int y=0;y<n;y++){
			for(int x=0;x<m;x++){
				int ice;
				scanf("%d",&ice);
				field[y*m+x] = ice ? true : false;
				if(ice) pos.push_back(P(x,y));
			}
		}

		int res=0;
		for(int p=0;p<pos.size();p++){
			queue<Pv> que;
			que.push(Pv(PP(1,pos[p]),field));
			
			while(!que.empty()){
				int cost = que.front().first.first;
				int x = que.front().first.second.first;
				int y = que.front().first.second.second;
				bitset<8100> now = que.front().second;
				now[y*m+x] = 0;
				res = max(res,cost);
				que.pop();
				for(int i=0;i<4;i++){
					int dx = x + tx[i];
					int dy = y + ty[i];

					if(dx<0 || dx >=m || dy<0 || dy>=n) continue;
					if(now[dy*m+dx]==0) continue;
					que.push(Pv(PP(cost+1,P(dx,dy)),now));
				}
			}
			
		}
		printf("%d\n",res);
	}
}

