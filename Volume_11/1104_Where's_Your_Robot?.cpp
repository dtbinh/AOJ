
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
typedef pair <double,double> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};

//up
//right
//down
//left
void move(int sx,int sy,int dir,
	int* dx,int* dy,int dist,int W,int H,string cmd){
		if(cmd=="forw"){
			*dx = (sx + tx[dir]*dist >= W ? W-1 : (sx + tx[dir]*dist < 0 ? 0 : sx + tx[dir]*dist));
			*dy = (sy + ty[dir]*dist >= H ? H-1 : (sy + ty[dir]*dist < 0 ? 0 : sy + ty[dir]*dist));
		}
		else{
			*dx = (sx + tx[(dir+2)%4]*dist >= W ? W-1 : (sx + tx[(dir+2)%4]*dist < 0 ? 0 : sx + tx[(dir+2)%4]*dist));
			*dy = (sy + ty[(dir+2)%4]*dist >= H ? H-1 : (sy + ty[(dir+2)%4]*dist < 0 ? 0 : sy + ty[(dir+2)%4]*dist));
		}
}

int main(){
	int W,H;
	while(cin >> W >> H){
		if(W==0 && H==0) break;
		int posX=0,posY=0;
		string cmd;
		int dir = 0;
		while(cin >> cmd){
			if(cmd == "FORWARD"){
				int dist;
				cin >> dist;
				move(posX,posY,dir,&posX,&posY,dist,W,H,"forw");
			}
			else if(cmd == "BACKWARD"){
				int dist;
				cin >> dist;
				move(posX,posY,dir,&posX,&posY,dist,W,H,"back");
			}
			else if(cmd == "RIGHT"){
				dir++;
				if(dir >= 4) dir = 0;
			}
			else if(cmd == "LEFT"){
				dir--;
				if(dir < 0) dir = 3;
			}
			else if(cmd == "STOP"){
				break;
			}
		}
		printf("%d %d\n",posX+1,posY+1);
	}
}

