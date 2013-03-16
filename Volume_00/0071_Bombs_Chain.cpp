
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
typedef pair<int,int> P;

void printData(int stage[8][8],int n){
	printf("Data %d:\n",n+1);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			cout << stage[i][j];
		}
		cout << endl;
	}
}

void bfs(int stage[8][8],int sx,int sy){
	queue<P> que;
	que.push(P(sx,sy));

	while(!que.empty()){
		int x = que.front().first;
		int y = que.front().second;

		que.pop();
		stage[y][x] = 0;
		for(int i=-3; i<=3; i++){
			for(int j=-3;j<=3;j++){
				if(i*j != 0 || (i==j && i==0)) continue;

				int dx = x+i;
				int dy = y+j;

				if(dx < 0 || dx >=8 || dy < 0 || dy >= 8) continue;

				if(stage[dy][dx] == 1){
					que.push(P(dx,dy));
				}
			}
		}
	}
}



int main(){

	string str;
	int stage[8][8];

	int n=0;

	getline(cin,str);
	sscanf(str.c_str(),"%d",&n);
	getline(cin,str);

	for(int idx=0;idx<n;idx++){
		for(int i=0;i<8;i++){
			getline(cin,str);
			for(int j=0;j<8;j++){
				stage[i][j]=str[j]-'0';
			}

		}

		int x,y;

		getline(cin,str);
		sscanf(str.c_str(),"%d",&x);

		getline(cin,str);
		sscanf(str.c_str(),"%d",&y);

		bfs(stage,x-1,y-1);
		printData(stage,idx);

		getline(cin,str);
	}
}

