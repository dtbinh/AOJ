
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


int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};

char buf[1000000];

int main(){
	int m,n;

	while(~scanf("%d",&n)){
		if(n==0) break;
		scanf("%d",&m);
		scanf("%s",buf);

		deque<char> que;
		int tmp = 0;
		int res = 0;
		for(int i=0;i<m;i++){
			que.push_back(buf[i]);
			
			if(que.size()==3){
				char f = que[0];
				char m = que[1];
				char r = que[2];
				
				if(f=='I' && m == 'O' && r == 'I'){
					tmp++;
					if(tmp>=n) res++;
					que.pop_front();
					que.pop_front();
				}
				else{
					tmp=0;
					que.pop_front();
				}
			}

		}
		printf("%d\n",res);
	}
}

