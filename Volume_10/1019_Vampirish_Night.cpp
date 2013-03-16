
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

int main(){
	int N,K;

	int tank[100];
	while(~scanf("%d %d",&N,&K)){
		if(N==K && K==0) break;
		for(int i=0;i<K;i++){
			scanf("%d",tank+i);
		}

		bool isok = true;
		for(int i=0;i<N;i++){
			for(int j=0;j<K;j++){
				int B;
				scanf("%d",&B);
				tank[j]-=B;
				if(tank[j]<0) isok = false;
			}
		}

		printf("%s\n",isok ? "Yes" : "No");
	}
}

