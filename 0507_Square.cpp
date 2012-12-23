
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

bool check(const vector<int>& blocks){
	for(int i=0;i+1<blocks.size();i++){
		if(blocks[i] < blocks[i+1]) return false;
	}
	return true;
}

void dfs(vector<int>& blocks,int n,int remnants){	
	if(remnants==0){
		for(int i=0;i<blocks.size();i++){
			printf("%s%d",i==0 ? "" : " ",blocks[i]);
		}
		printf("\n");
		return;
	}

	for(int i=remnants;i>=1;i--){
		vector<int> next = blocks;
		next.push_back(i);
		if(!check(next)) continue;

		dfs(next,n,remnants-i);
	}
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		vector<int> blocks;
		if(n==0) break;
		dfs(blocks,n,n);
	}
}

