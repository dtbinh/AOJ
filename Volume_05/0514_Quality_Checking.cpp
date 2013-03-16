
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

struct DATA{
	int i;
	int j;
	int k;
};

int safe[301];

int main(){
	int a,b,c;
	while(~scanf("%d %d %d",&a,&b,&c)){
		int N;
		scanf("%d",&N);
		vector<DATA> valid;
		vector<DATA> invalid;
		
		fill((int*)safe,(int*)safe + 301,2);

		for(int n=0;n<N;n++){
			int i,j,k,r;
			//i:battery,j:moter,k:cable,r:1ok
			scanf("%d %d %d %d",&i,&j,&k,&r);
			DATA data = {i,j,k};
			if(r) valid.push_back(data);
			else invalid.push_back(data);
		}

		for(int i=0;i<valid.size();i++){
			safe[valid[i].i] = 1;
			safe[valid[i].j] = 1;
			safe[valid[i].k] = 1;
		}

		for(int i=0;i<invalid.size();i++){
			if(safe[invalid[i].i] == 1
			 && safe[invalid[i].j] == 1)
			{
				safe[invalid[i].k] = 0;
			}

			else if(safe[invalid[i].j] == 1
			 && safe[invalid[i].k] == 1)
			{
				safe[invalid[i].i] = 0;
			}

			else if(safe[invalid[i].i] == 1
			 && safe[invalid[i].k] == 1)
			{
				safe[invalid[i].j] = 0;
			}
		}

		for(int i=1;i<=a;i++){
			printf("%d\n",safe[i]);
		}

		for(int i=a+1;i<=a+b;i++){
			printf("%d\n",safe[i]);
		}

		for(int i=a+b+1;i<=a+b+c;i++){
			printf("%d\n",safe[i]);
		}
	}
}

