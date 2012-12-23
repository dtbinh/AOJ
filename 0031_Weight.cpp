
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>

typedef long long ll;
using namespace std;

typedef pair<int,int> P;

int main()
{
	int n;
	queue<int> que;
	while(~scanf("%d",&n)){
		for(int i = 0; i < 10; i++){
			if((n >> i) & 1) que.push(pow(2,(double)i));
		}

		while(!que.empty()){
			printf("%d%s",que.front(),que.size() == 1 ? "\n" : " ");
			que.pop();
		}
	}
}

