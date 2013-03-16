
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

using namespace std;

typedef long long ll;
typedef pair<char,int> P;

void flip(int x,int y,int stage[10][10]){
	const int t[][2] = {{0,0},{-1,0},{1,0},{0,1},{0,-1}};
	for(int i=0;i<5;i++){
		int dx = x+t[i][0];
		int dy = y+t[i][1];

		if(dx < 0 || dx >= 10 || dy < 0 || dy >= 10) continue;

		stage[dy][dx]*=-1;
	}
}

bool checkStage(int store[10][10],int x,int y){
	return store[y][x] == -1 ? true : false;
}

bool isClear(int store[10][10]){
	for(int y=0;y<10;y++){
		for(int x=0;x<10;x++){
			if(store[y][x]==1) return false;
		}
	}

	return true;
}

void writeResult(int result[10][10]){
	for(int y=0;y<10;y++){
		for(int x=0;x<10;x++){
			printf("%d%s",result[y][x],x==9 ? "\n" : " ");
		}
	}
}

int main(){

	int n;
	while(~scanf("%d",&n)){
		for(int i=0;i<n;i++){
			int stage[10][10];
			
			for(int y=0;y<10;y++){
				for(int x=0;x<10;x++){
					int num;
					scanf("%d",&num);
					stage[y][x] = (num == 0 ? -1 : 1);
				}
			}
			
			for(int S=0;S<=(1 << 10)-1;S++){
				int store[10][10];
				int result[10][10];
				memset(result,0,sizeof(result));
				//memset(store,0,sizeof(store));
				memcpy(store,stage,sizeof(stage));

				for(int j=0;j<10;j++){
					if((S>>j) & 1){
						flip(j,0,store);
						result[0][j]=1;
					}
				}

				for(int y=1;y<10;y++){
					for(int x=0;x<10;x++){
						flip(x,y,store);
						if(!checkStage(store,x,y-1)){
							flip(x,y,store);
						}
						else{
							result[y][x] = 1;
						}
					}
				}

				if(isClear(store)){
					writeResult(result);
					break;
				}
			}

		}
	}
}


