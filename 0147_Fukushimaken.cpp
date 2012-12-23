
#define _USE_MATH_DEFINES
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

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

struct group{
	int num;
	int eatTime;
	int idx;
};

int isEmpty(int table[17],int n){
	for(int i=0;i<17;i++){
		if(table[i] > 0) continue;
		for(int j=i+1;j<17;j++){
			if(table[j] > 0) break;
			if(j-i+1 == n){
				return i;
			}
		}
	}

	return -1;
}

void checkTable(int table[17],queue<group>& que,map<int,int>& waitTime){

	int time=0;
	while(!que.empty()){
		while(!que.empty() && (que.front().idx * 5 <= time)){
			int idx;
			if((idx = isEmpty(table,que.front().num)) != -1){
				for(int k=idx; k<idx+que.front().num;k++){
					table[k] = que.front().eatTime;
				}
				waitTime[que.front().idx] = abs(time - que.front().idx * 5);
				que.pop();
			}
			else break;
		}
		for(int i=0;i<17;i++) if(table[i]>0) table[i]--;
		time++;	
	}
}

int main(){
	int n;
	int table[17];
	memset(table,0,sizeof(table));
	queue<group> que;
	map<int,int> waitTime;

	for(int i=0;i<100;i++){
		int num = (i % 5 == 1) ? 5 : 2;
		int eat = 17*(i%2)+3*(i%3)+19;
		group g;
		g.eatTime = eat;
		g.idx = i;
		g.num = num;
		que.push(g);		
	}

	checkTable(table,que,waitTime);

	while(~scanf("%d",&n)){
		cout << waitTime[n] << endl;
	}
}

