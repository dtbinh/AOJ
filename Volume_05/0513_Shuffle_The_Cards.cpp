
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

int main(){
	int n;
	while(~scanf("%d",&n)){
		int* cards = new int[2*n]();
		int* cardA = new int[2*n]();
		int* cardB = new int[2*n]();

		for(int i=0;i<2*n;i++){
			cards[i]=i+1;
		}

		int m;
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			int k;
			scanf("%d",&k);
			if(k==0){
				for(int i=0;i<n;i++){
					cardA[i]=cards[i];
				}
				for(int i=0,j=n;i<n;i++,j++){
					cardB[i]=cards[j];
				}

				for(int i=0;i<n;i++){
					cards[2*i] = cardA[i];
					cards[2*i+1] = cardB[i];
				}
			}
			else{
				for(int i=0;i<k;i++){
					cardA[i] = cards[i];
				}
				for(int i=k,j=0;i<2*n;i++,j++){
					cardB[j] = cards[i];
				}

				for(int i=0;i<2*n-k;i++){
					cards[i] = cardB[i];
				}

				for(int i=2*n-k,j=0;i<2*n;i++,j++){
					cards[i] = cardA[j];
				}
			}
		}

		for(int i=0;i<2*n;i++){
			printf("%d\n",cards[i]);
		}
	}
}

