
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

int main(){
	int n,m;
	while(~scanf("%d %d",&n,&m)){
		if(n==m && n==0) break;
		bool* joseph = new bool[n+1];
		fill((bool*)joseph,(bool*)joseph+n+1,true);

		joseph[0]=false;

		int idx = 1;
		int c = 0;
		int total=0;
		while(1){
			if(n-total==1) break;
			if(joseph[idx%(n+1)]) c++;
			if(c == m){
				joseph[idx%(n+1)] = false;
				total++;
				c = 0;
			}
			idx++;
		}
		cout << find(joseph,joseph+n+1,true) - joseph << endl;
	}
}

