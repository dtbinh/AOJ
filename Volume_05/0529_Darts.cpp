
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
	int N,M;	
	while(~scanf("%d %d",&N,&M)){
		if(N==M && M==0) break;
		vector<int> Points;
		Points.push_back(0);
		for(int i=0;i<N;i++){
			int p;
			scanf("%d",&p);
			Points.push_back(p);
		}

		vector<int> Points2;
		for(int i=0;i<=N;i++){
			for(int j=0;j<=N;j++){
				Points2.push_back(Points[i]+Points[j]);
			}
		}

		sort(Points2.begin(),Points2.end());
		vector<int>::iterator it = unique(Points2.begin(),Points2.end());
		Points2.erase(it,Points2.end());


		int res=0;
		for(vector<int>::iterator it = Points2.begin();it != Points2.end();it++){
			if(M-*it<0) continue;

			vector<int>::iterator it2 = lower_bound(Points2.begin(),Points2.end(),M-*it);
			if(it2==Points2.end()) continue;
			res = max((it2 == Points2.begin() ? 0 : *(it2-1)) + *it,res);
		}

		printf("%d\n",res);
	}
}

