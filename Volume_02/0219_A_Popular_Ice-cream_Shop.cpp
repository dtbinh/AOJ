
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
typedef pair <int,P > PP;

static const double eps = 1e-8;

void printIce(int* freq,int kind){
	if(freq[kind] == 0){
		printf("-\n");
		return;
	}

	for(int i=0;i<freq[kind];i++){
		printf("%s",(i == freq[kind] - 1) ? "*\n" : "*");
	}
}

int main(){
	int n;	
	while(~scanf("%d",&n)){
		if(n==0) break;

		int* freq = new int[10]();
		for(int i=0;i<n;i++){
			int kind;
			scanf("%d",&kind);
			freq[kind]++;
		}

		for(int i=0;i<10;i++){
			printIce(freq,i);
		}

		delete[] freq;
	}
}

