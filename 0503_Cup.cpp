
#define _USE_MATH_DEFINES
#define INF 100000000
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
typedef pair <int,vector<int> > P;

static const double eps = 1e-8;

int mypow(int x,int n){
	int res = 1;
	while(n>0){		
		if(n & 1) res = res*x;
		x = x * x;
		n>>=1;
	}
	return res;
}


int conv(vector<int>& sets,int n){
	int res = 0;
	for(int i=0;i<sets.size();i++){
		for(int j=0;j<n;j++){
			if(sets[i] & (1<<j)){
				res += i * mypow(3,j);
			}
		}
	}
	return res;
}

int bfs(int m,int n,vector<int>& root,bool* visited){

	priority_queue<P,vector<P>,greater<P> > que;
	que.push(P(0,root));
	visited[conv(root,n)] = 0;
	vector<int> tmp;
	vector<int> sets;
	while(!que.empty()){
		int cost = que.top().first;
		
		sets = que.top().second;

		if(sets[1]==0 && sets[2]==0) return cost;
		if(sets[0]==0 && sets[1]==0) return cost;

		if(cost >= m) break;
		que.pop();
		for(int i=0;i+1<sets.size();i++){
			if((sets[i] && sets[i+1] && sets[i] < sets[i+1]) 
				|| (!sets[i] && sets[i+1])){
				tmp = sets;

				int pos=0;
				for(int j=n-1;j>=0;j--){
					if(tmp[i+1] & (1<<j)){
						pos = j;
						break;
					}
				}
				tmp[i+1] &= ~(1<<pos);
				tmp[i] |= (1<<pos);

				
				int next;
				if(!visited[(next = conv(tmp,n))]){
					visited[next] = cost+1;
					que.push(P(cost+1,tmp));
				}
			}

			else if((sets[i] && sets[i+1] && sets[i] > sets[i+1]) 
				|| (sets[i] && !sets[i+1])){
				tmp = sets;

				int pos=0;
				for(int j=n-1;j>=0;j--){
					if(tmp[i] & (1<<j)){
						pos = j;
						break;
					}
				}
				tmp[i] &= ~(1<<pos);
				tmp[i+1] |= (1<<pos);

				int next;
				if(!visited[(next = conv(tmp,n))]){
					visited[next] = cost+1;
					que.push(P(cost+1,tmp));
				}
			}
		}
	}
	return -1;
}

int main(){

	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && m==0) break;
		vector<int> sets(3);
		bool* visited = new bool[mypow(3,n)]();
		for(int i=0;i<3;i++){
			int amount;
			scanf("%d",&amount);
			for(int j=0;j<amount;j++){
				int size;
				scanf("%d",&size);
				sets[i] |= (1<<(size-1)); 
			}
		}

		printf("%d\n",bfs(m,n,sets,visited));
		delete[] visited;
	}
	//printf("%d %d %d\n",mypow(3,0),mypow(3,1),mypow(3,2));
}

