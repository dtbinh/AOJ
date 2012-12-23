
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

int trainTime[101][101];
int trainCost[101][101];

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;
		memset(trainTime,0x3,sizeof(trainTime));
		memset(trainCost,0x3,sizeof(trainCost));
		for(int i=0;i<n;i++){
			int a,b,cost,time;
			scanf("%d %d %d %d",&a,&b,&cost,&time);
			trainTime[a][b] = trainTime[b][a] = min(trainTime[a][b],time);
			trainCost[a][b] = trainCost[b][a] = min(trainCost[a][b],cost);
		}

		for(int k=1;k<=m;k++){
			for(int i=1;i<=m;i++){
				for(int j=1;j<=m;j++){
					trainTime[i][j] = min(trainTime[i][k]+trainTime[k][j],trainTime[i][j]);
					trainCost[i][j] = min(trainCost[i][k]+trainCost[k][j],trainCost[i][j]);
				}
			}
		}

		int k;
		scanf("%d",&k);
		for(int i=0;i<k;i++){
			int a,b,r;
			scanf("%d %d %d",&a,&b,&r);
			printf("%d\n", r == 0 ? trainCost[a][b] : trainTime[a][b]);
		}

	}

}

