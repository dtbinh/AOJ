
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

int tx[] = {1,0};
int ty[] = {0,1};

int main(){
	int p[3];
	int ju[2];
	for(int i=0;i<3;i++){
		scanf("%d",p+i);
	}

	for(int i=0;i<2;i++){
		scanf("%d",ju+i);
	}

	int res = INF;
	for(int i=0;i<3;i++){
		for(int j=0;j<2;j++){
			res = min(res,p[i]+ju[j] -50);
		}
	}
	printf("%d\n",res);
}

