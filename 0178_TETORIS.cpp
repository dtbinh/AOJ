
#define _USE_MATH_DEFINES
#define MAX_N 1000000
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

static const double eps = 1e-8;

int gStage[6000][5];

void putBlock(int dir,int len,int pos){
	if(dir == 1){
		for(int i=6000-1;i>=0;i--){
			bool isok=true;
			for(int j=pos;j<pos+len;j++){
				if(gStage[i][j]==1) isok=false;
			}
			
			if(!isok){
				for(int j=pos;j<pos+len;j++){
					gStage[i+1][j] = 1;
				}
				return;
			}

			else if(isok && i==0){
				for(int j=pos;j<pos+len;j++){
					gStage[i][j] = 1;
				}
				return;
			}
		}
	}
	else{
		for(int i=6000-1;i>=0;i--){
			bool isok=true;
			if(gStage[i][pos]==1) isok=false;

			if(!isok){
				for(int j=i+1;j<i+1+len;j++){
					gStage[j][pos] = 1;
				}
				return;
			}

			else if(isok && i==0){
				for(int j=i;j<i+len;j++){
					gStage[j][pos] = 1;
				}
				return;
			}
		}
	}
}

int countBlock(){
	int res=0;
	for(int i=0;i<6000;i++){
		for(int j=0;j<5;j++){
			res += gStage[i][j];
		}
	}

	return res;
}

void eraseBlock(){
	for(int i=0;i<6000;i++){
		bool isok=true;
		for(int j=0;j<5;j++){
			if(gStage[i][j]==0) isok = false;
		}

		if(isok){
			for(int j=i;j+1<6000;j++){
				for(int k=0;k<5;k++){
					gStage[j][k] = gStage[j+1][k];
				}
			}
			i--;
		}
	}
}

void printBlock(){
	for(int i=0;i<50;i++){
		for(int j=0;j<5;j++){
			printf("%d",gStage[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		memset(gStage,0,sizeof(gStage));
		for(int i=0;i<n;i++){
			int dir,len,pos;
			scanf("%d %d %d",&dir,&len,&pos);
			pos-=1;
			putBlock(dir,len,pos);
			//printBlock();
			eraseBlock();
			//printBlock();
		}

		printf("%d\n",countBlock());
	}
}

