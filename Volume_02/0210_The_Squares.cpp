
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
typedef pair<int,int> P;

static const double eps = 1e-8;

char stage[50][50];

static const int moveTo[][2] = {{1,0},{0,-1},{-1,0},{0,1}};

void changeDir(int W,int H){
	map<char,int> dir;
	dir['N'] = 0; dir['W'] = 1; dir['S'] = 2; dir['E'] = 3;
	const char num2dir[] = {'E','N','W','S'};
	//# 壁
	//.(ピリオド)床
	//X 非常口
	//E 東を向いている人
	//N 北を向いている人
	//W 西を向いている人
	//S 南を向いている人

	for(int y=0;y<H;y++){
		for(int x=0;x<W;x++){
			switch(stage[y][x]){
			case '#':			  
				break;
			case 'X':
				break;
			case 'N': case 'W': case 'S': case 'E':
				for(int i=0;i<4;i++){
					int dx = x + moveTo[(i+dir[stage[y][x]])%4][0];
					int dy = y + moveTo[(i+dir[stage[y][x]])%4][1];
					if(dy < 0 || dy >= H || dx < 0 || dx >= W) continue;
					if(stage[dy][dx] == '.' || stage[dy][dx] == 'X'){
						stage[y][x] = num2dir[(i+dir[stage[y][x]])%4];
						break;
					}
				}

				break;
			default :
				break;
			}

		}
	}
}

void movePlayer(int W,int H){
	map<char,int> dir;
	dir['N'] = 0; dir['W'] = 1; dir['S'] = 2; dir['E'] = 3;
	const char num2other_dir[] = {'W','S','E','N'};
	//# 壁
	//.(ピリオド)床
	//X 非常口
	//E 東を向いている人
	//N 北を向いている人
	//W 西を向いている人
	//S 南を向いている人

	bool used[30][30];
	fill((bool*)used,(bool*)used+30*30,false);
	for(int dy=0;dy<H;dy++){
		for(int dx=0;dx<W;dx++){
			
			switch(stage[dy][dx]){
			case '#':			  
				break;
			case 'X':
				for(int i=0;i<4;i++){
					int sx = dx + moveTo[i][0];
					int sy = dy + moveTo[i][1];
					
					if(sy < 0 || sy >= H || sx < 0 || sx >= W) continue;
					if(used[sy][sx]) continue;
					if(used[dy][dx]) continue;
					if(stage[sy][sx] == num2other_dir[i]){
						stage[sy][sx] = '.';
						used[dy][dx] = true;
						used[sy][sx] = true;
						break;
					}
				}
				break;
			case '.':
				for(int i=0;i<4;i++){
					int sx = dx + moveTo[i][0];
					int sy = dy + moveTo[i][1];
					
					if(sy < 0 || sy >= H || sx < 0 || sx >= W) continue;
					if(used[sy][sx]) continue;
					if(used[dy][dx]) continue;
					if(stage[sy][sx] == num2other_dir[i]){
						stage[dy][dx] = num2other_dir[i];
						stage[sy][sx] = '.'; 
						used[dy][dx] = true;
						used[sy][sx] = true;
						break;
					}
				}
				break;
			case 'N': case 'W': case 'S': case 'E':
				break;
			default :
				break;
			}

		}
	}
}

void printStage(int W,int H){
	for(int y=0;y<H;y++){
		for(int x=0;x<W;x++){
			printf("%c",stage[y][x]);
		}
		printf("\n");
	}
	printf("\n");
}

bool isClear(int W,int H){
	for(int y=0;y<H;y++){
		for(int x=0;x<W;x++){
			switch(stage[y][x]){
			case 'N': case 'W': case 'S': case 'E':
				return false;
				break;
			default:
				break;
			}
		}
	}
	return true;
}

int main(){
	int W,H;
	while(~scanf("%d %d",&W,&H)){
		if(W==H && H==0) break;
		memset(stage,'#',sizeof(stage));
		for(int y=0;y<H;y++){
			char buf[64];
			scanf("%s",buf);
			for(int x=0;x<W;x++){
				stage[y][x] = buf[x];
			}
		}

		int res=0;
		//printStage(W,H);
		while(!isClear(W,H)){
			
 			changeDir(W,H);
			//printStage(W,H);
 			movePlayer(W,H);
			//printStage(W,H);
			res++;
			if(res > 180) break;
		}

		if(res > 180) printf("NA\n");
		else printf("%d\n",res);

	}

}

