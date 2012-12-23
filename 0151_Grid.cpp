
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
#include <bitset>

using namespace std;

typedef long long ll;
typedef pair<int,int> P;

static const double eps = 10e-6;

int diagLLUR(int n,int** mat){
	int res = 0;
	for(int y=0;y<n;y++){
		int c = 0;
		for(int x=0,dy=y;x<n && dy>=0;x++,dy--){
			if(mat[dy][x] == 0) { res = max(res,c); c = 0; }
			else c++;
		}
		res = max(c,res);
	}

	for(int x=0;x<n;x++){
		int c=0;
		for(int dx=x,y=n-1;dx<n && y>=0;dx++,y--){
			if(mat[y][dx] == 0) { res = max(res,c); c = 0; }
			else c++;
		}
		res = max(c,res);
	}

	return res;
}

int diagULLR(int n,int** mat){
	int res = 0;
	for(int x=n-1;x>=0;x--){
		int c=0;
		for(int dx=x,y=0;dx<n && y<n;dx++,y++){
			if(mat[y][dx] == 0) { res = max(res,c); c = 0; }
			else c++;
		}
		res = max(c,res);
	}

	for(int y=0;y<n;y++){
		int c = 0;
		for(int x=0,dy=y;x<n && dy<n;x++,dy++){
			if(mat[dy][x] == 0) { res = max(res,c); c = 0; }
			else c++;
		}
		res = max(c,res);
	}

	return res;
}

int vert(int n,int** mat){
	int res = 0;
	for(int x=0;x<n;x++){
		int c=0;
		for(int y=0;y<n;y++){
			if(mat[y][x] == 0) { res = max(res,c); c = 0; }
			else c++;
		}

		res = max(c,res);
	}

	return res;
}

int hori(int n,int** mat){
	int res = 0;
	for(int y=0;y<n;y++){
		int c=0;
		for(int x=0;x<n;x++){
			if(mat[y][x] == 0) { res = max(res,c); c = 0; }
			else c++;
		}

		res = max(c,res);
	}

	return res;
}

int main(){

	int n;	

	while(~scanf("%d",&n)){
		if(n==0) break;

		int** mat = new int*[n];
		for(int i=0;i<n;i++) mat[i] = new int[n]();

		for(int y=0;y<n;y++){
			char buf[512];
			scanf("%s",buf);
			for(int x=0;x<n;x++){
				mat[y][x] = buf[x]-'0';
			}
		}

		printf("%d\n",max(max(diagLLUR(n,mat),hori(n,mat)),max(diagULLR(n,mat),vert(n,mat))));

		for(int i=0;i<n;i++) delete[] mat[i];
		delete[] mat;
	}
}

