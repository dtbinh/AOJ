
#define _USE_MATH_DEFINES
#define INF 100000000
 
#include <iostream>
#include <cstdio>
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
int main(){
	int N,K;
	while(~scanf("%d %d",&N,&K)){
		map<int,map<int,bool> > boats;
 
		for(int i=0;i<K;i++){
			int m;
			scanf("%d",&m);
 
			map<int,bool> tmp;
			for(int j=0;j<m;j++){
 
				int usagi;
				scanf("%d",&usagi);
				tmp[usagi] = true;
			}
 
			boats[i] = tmp;
		}
 
		int R;
		scanf("%d",&R);
		bool sux[100];
		memset(sux,0,sizeof(sux));
		for(int i=0;i<R;i++){
			int a,b;
			scanf("%d %d",&a,&b);
			for(int j=0;j<K;j++){
				if(boats[j].find(a) != boats[j].end()
					&& boats[j].find(b) != boats[j].end()){
						sux[a] = true;
						sux[b] = true;
				}
			}
		}
 
		int res = 0;
		for(int i=0;i<=N;i++){
			if(sux[i]) res++;
		}
 
		printf("%d\n",res);
	}
}


