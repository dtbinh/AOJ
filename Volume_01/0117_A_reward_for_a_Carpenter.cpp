
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

static const double eps = 1e-8;

int path[21][21];

int main(){
	int n,m;
	memset(path,0x3,sizeof(path));
	scanf("%d",&n);
	scanf("%d",&m);
	for(int i=0;i<m;i++){
		int a,b,cost_ab,cost_ba;
		scanf("%d,%d,%d,%d",&a,&b,&cost_ab,&cost_ba);
		path[a][b] = cost_ab;
		path[b][a] = cost_ba;
	}

	int x1,x2,y1,y2;
	scanf("%d,%d,%d,%d",&x1,&x2,&y1,&y2);

	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				path[i][j] = min(path[i][k] + path[k][j],path[i][j]);
			}
		}
	}

	printf("%d\n",y1 - path[x1][x2] - path[x2][x1] - y2);
}

