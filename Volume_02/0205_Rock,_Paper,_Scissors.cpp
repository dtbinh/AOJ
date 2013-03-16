
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
typedef pair<int,string> P;

static const double eps = 1e-8;

int main(){
	int gesture[5];
	while(~scanf("%d",&gesture)){
		if(gesture[0]==0) break;
		for(int i=0;i<4;i++){
			scanf("%d",gesture+i+1);
		}

		for(int i=0;i<5;i++){
			int bit,player;
			bit = player = (1 << (gesture[i]-1));

			for(int j=0;j<5;j++){
				if(i==j) continue;
				bit |= (1 << (gesture[j]-1));
			}

			if(bit == ((1<<3)-1)){
				printf("3\n");
			}

			else if(bit == 1 
				|| bit == (1<<1)
				|| bit == (1<<2)){
					printf("3\n");
			}

			else{
				bit &= ~player;
				if(player == 1 && bit == (1<<1)){
					printf("1\n");
				}
				else if(player == 1 && bit == (1<<2)){
					printf("2\n");
				}

				else if(player == (1<<1) && bit == 1){
					printf("2\n");
				}
				else if(player == (1<<1) && bit == (1<<2)){
					printf("1\n");
				}

				else if(player == (1<<2) && bit == 1){
					printf("1\n");
				}
				else if(player == (1<<2) && bit == (1<<1)){
					printf("2\n");
				}
			}
		}
		
	}

}

