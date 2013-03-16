
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
#include <cctype>
#include <utility>

using namespace std;

typedef long long ll;
typedef pair <int,int> P;


static const double EPS = 1e-8;

int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};

bool stage[101][101];

int main()
{
	int N;
	while(~scanf("%d",&N)){
		if(N==0) break;
		memset(stage,0,sizeof(stage));
		int W,H;
		
		scanf("%d %d",&W,&H);	
		for(int i=0;i<N;i++){
			int x,y;
			scanf("%d %d",&x,&y);
			stage[y-1][x-1] = true;
		}
		int S,T;
		int res = 0;
		scanf("%d %d",&S,&T);
		for(int y=0;y+T<=H;y++){
			for(int x=0;x+S<=W;x++){
				int tmp = 0;
				for(int ny=y;ny-y+1<=T;ny++){
					for(int nx=x;nx-x+1<=S;nx++){
						if(stage[ny][nx]) tmp++;
					}
				}

				res = max(res,tmp);
			}
		}

		printf("%d\n",res);
	}

}

