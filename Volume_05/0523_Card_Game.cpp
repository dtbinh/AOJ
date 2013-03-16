
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
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		bool visited[201];
		memset(visited,0,sizeof(visited));
		list<int> tl,hl;
		for(int i=0;i<n;i++){
			int num;
			scanf("%d",&num);
			visited[num] = true;
			tl.push_back(num);
		}

		for(int i=1;i<=2*n;i++){
			if(!visited[i]) hl.push_back(i);
		}

		tl.sort();
		hl.sort();

		int field=-1;
		int turn=0;
		while(1){
			if(hl.empty() || tl.empty()) break;

			if(turn==0){
				list<int>::iterator taro_it = lower_bound(tl.begin(),tl.end(),field);
				if(taro_it != tl.end()){
					field = *taro_it;
					tl.erase(taro_it);
				}
				
				else{
					field = -1;
				}
				turn = 1;
			}

			else{
				list<int>::iterator hanako_it = lower_bound(hl.begin(),hl.end(),field);
				if(hanako_it != hl.end()){
					field = *hanako_it;
					hl.erase(hanako_it);
				}
				
				else{
					field = -1;
				}
				turn = 0;
			}
		}

		int taro = 0;
		int hanako = 0;
		if(!tl.empty()){
			hanako = tl.size();
		}

		else if(!hl.empty()){
			taro = hl.size();
		}
		printf("%d\n%d\n",taro,hanako);
	}
}

