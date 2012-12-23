
#define _USE_MATH_DEFINES
#define INF 10000000
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
typedef pair <int,int> P;
typedef pair <P,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

int main(){
	char a[32],b[32];
	while(~scanf("%s %s",a,b)){
		if(a[0]==b[0] && b[0] == '0') break;
		int hit=0;
		int brow=0;

		for(int i=0;i<4;i++){
			if(a[i]==b[i]){
				hit++;
				continue;
			}
			for(int j=0;j<4;j++){
				if(i==j) continue;
				if(b[i] == a[j]){
					brow++;
					break;
				}
			}

		}

		printf("%d %d\n",hit,brow);
	}
}

