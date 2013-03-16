
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
typedef pair<int,string> P;

static const double eps = 1e-8;

const int moveTo[][2] = {{-1,1},{0,1},{1,1}};

int stage[17][17];
int dp[17][17];

int main(){
	int w,h;
	while(~scanf("%d %d",&w,&h)){
		if(w==h && h==0) break;
		memset(stage,-1,sizeof(stage));
		memset(dp,0,sizeof(dp));
		for(int y=0;y<h;y++){
			for(int x=0;x<w;x++){
				scanf("%d",&stage[y][x]);
			}
		}

		//space:0 tree:1 jump:2
		for(int x=0;x<w;x++){
			if(stage[0][x]!=1) dp[0][x] = 1;
		}

		for(int dy=1;dy<=h;dy++){
			for(int dx=0;dx<w;dx++){
				if(stage[dy][dx] != 1){			
					for(int j=0;j<3;j++){
						int sx = dx - moveTo[j][0];
						int sy = dy - moveTo[j][1];
						if(sx < 0 || sx >= w || sy < 0 || sy >= h-1) continue;

						//space:0 tree:1 jump:2
						if(stage[sy][sx]!=0) continue;
						if(stage[dy][dx]==2 && dx != sx) continue;

						dp[dy][dx] += dp[sy][sx];
					}

					int sx = dx;
					int sy = dy-2;
					if(sx >=0 && sx < w && sy >= 0 && sy < h-1){
						//space:0 tree:1 jump:2
						if(stage[sy][sx] == 2){
							dp[dy][dx] += dp[sy][sx];
						}
					}
				}
			}
		}

		int res=0;
		for(int y=h-1;y<=h;y++){
			for(int x=0;x<w;x++){
				res += dp[y][x];
			}
		}

		printf("%d\n",res);
	}

}

