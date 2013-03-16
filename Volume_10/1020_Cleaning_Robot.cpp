
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
 
static const double EPS = 1e-8;
 
const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};
 
char stage[3][3];
double prob[17][3][3];

int main(){
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
 
        char s,t,b;
        memset(stage,'.',sizeof(stage));
        cin >> s >> t >> b;
        int sx = (s-'A')%3;
        int sy = (s-'A')/3;
        int gx = (t-'A')%3;
        int gy = (t-'A')/3;
        stage[(b-'A')/3][(b-'A')%3] = 'B';

		fill(prob[0][0],prob[0][0]+3*3*17,0.0);

		prob[0][sy][sx] = 1.0;

		for(int i=0;i<n;i++){
			for(int y=0;y<3;y++){
				for(int x=0;x<3;x++){
					for(int j=0;j<4;j++){
						int dx = x + tx[j];
						int dy = y + ty[j];
						if((dx < 0 || dx >= 3 || dy < 0 || dy >= 3)
							|| stage[dy][dx]=='B') prob[i+1][y][x] += prob[i][y][x]/4.0;
						else prob[i+1][dy][dx] += prob[i][y][x]/4.0;
					}
				}
			}
		}

		printf("%lf\n",prob[n][gy][gx]);
	}
}

