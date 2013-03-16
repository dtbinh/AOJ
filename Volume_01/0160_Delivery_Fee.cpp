
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

static const double eps = 10e-8;

struct DATA{
	int size;
	int weight;
	int fee;
};

int main(){
	struct DATA data[6] = {
		60,2,600,
		80,5,800,
		100,10,1000,
		120,15,1200,
		140,20,1400,
		160,25,1600,
	};

	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		int sum=0;
		for(int i=0;i<n;i++){
			int x,y,h,w;
			scanf("%d %d %d %d",&x,&y,&h,&w);
			int size = x+y+h;
			for(int i=0;i<6;i++){
				if(size <= data[i].size
					&& w <= data[i].weight){
						sum += data[i].fee;
						break;
				}
			}
		}
		printf("%d\n",sum);
	}
}

