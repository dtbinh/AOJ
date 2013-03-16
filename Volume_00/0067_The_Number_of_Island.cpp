
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

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;

int bfs(int stage[12][12]){

	int count = 0;
	for(int y=0;y<12;y++){
		for(int x=0;x<12;x++){
			if(stage[y][x]==0) continue;
			count++;
			queue<P> que;
			que.push(P(x,y));

			while(!que.empty()){
				int x = que.front().first;
				int y = que.front().second;

				que.pop();

				stage[y][x] = 0;

				for(int i=-1;i<=1;i++){
					for(int j=-1;j<=1;j++){
						if(i*j != 0 || (i==j && i==0)) continue;
						int dx = x + i;
						int dy = y + j;

						if(dx < 0 || dx >=12 || dy < 0 || dy >= 12) continue;
						if(stage[dy][dx]==0) continue;
						que.push(P(dx,dy));
					}
				}
			}
		}
	}
	return count;
}

int main(){
	string str;

	int stage[12][12];

	while(getline(cin,str)){
		if(str.empty()) continue;

		for(int y=0;y<12;y++){
			for(int x=0;x<12;x++){
				stage[y][x]=str[x]-'0';
			}
			getline(cin,str);
		}

		cout << bfs(stage) << endl;
	}
}

