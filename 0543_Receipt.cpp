
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

int main(){
	int sum;
	while(~scanf("%d",&sum)){
		if(sum==0) break;
		for(int i=0;i<9;i++){
			int val;
			scanf("%d",&val);
			sum-=val;
		}
		printf("%d\n",sum);
	}
}

