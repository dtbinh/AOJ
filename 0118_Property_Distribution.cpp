
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


void dfs(char** stage,int W,int H,int x,int y,char fruit){

	stage[y][x]='x';
	for(int i=-1;i<=1;i++){
		for(int j=-1;j<=1;j++){
			if(i*j!=0 || (i==j && j==0)) continue;
			int dx = x+i;
			int dy = y+j;

			if(dx<0 || dx>=W || dy<0 || dy>=H) continue;

			if(stage[dy][dx]!=fruit || stage[dy][dx]=='x') continue;
			dfs(stage,W,H,dx,dy,fruit);
		}
	}
}

int distribute(char** stage,int W,int H){
	int res=0;

	for(int x=0;x<W;x++){
		for(int y=0;y<H;y++){
			if(stage[y][x]=='x') continue;
			res++;
			char fruit = stage[y][x];
			dfs(stage,W,H,x,y,fruit);
		}
	}

	return res;
}


int main(){
	string str;
	while(getline(cin,str)){
		int W,H;		
		sscanf(str.c_str(),"%d %d",&H,&W);
		if(H==W && W==0) break;

		char** stage = new char*[H];
		for(int i=0;i<H;i++){
			stage[i] = new char[W];
		}

		for(int i=0;i<H;i++){
			getline(cin,str);
			for(int j=0;j<W;j++){
				stage[i][j] = str[j];
			}
		}

		cout << distribute(stage,W,H) << endl;

		for(int i=0;i<H;i++){
			delete[] stage[i];
		}
		delete[] stage;
	}
}



