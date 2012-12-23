
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

void set_pos(int* x,int* y,int n,int** table){

	bool isok = true;
	while(1){
		if(*x >= n){
			*x = 0;
			isok=false;
		}

		if(*x < 0){
			*x = n-1;
			isok=false;
		}

		if(*y >= n){
			*y = 0;
			isok=false;
		}

		if(*y>=0 && *y<n && *x>=0 && *x<n && table[*y][*x]!=0){
			*y += 1;
			*x -= 1;
			isok=false;
		}

		if(isok) break;

		isok=true;
	}
}

int main(){
	int n;
	while(scanf("%d",&n)){
		if(n==0) break;
		int** table = new int*[n];
		for(int i=0;i<n;i++) table[i] = new int[n]();

		int cx = n/2;
		int cy = n/2;

		int dx = cx;
		int dy = cy + 1;

		table[dy][dx] = 1;

		for(int i=2;i<=n*n;i++){
			dx++;
			dy++;
			set_pos(&dx,&dy,n,table);
			table[dy][dx] = i;
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				printf("%4d%s",table[i][j],j==n-1 ? "\n" : "");
			}
		}


		for(int i=0;i<n;i++) delete[] table[i];
		delete[] table;
	}
}

