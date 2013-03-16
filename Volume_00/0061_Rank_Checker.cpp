
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

int main(){

	
	int idx,cor;
	map<int,int> info;
	set<int,greater<int> > rank;
	while(~scanf("%d,%d",&idx,&cor)){
		if(idx == cor && idx == 0) break;
		rank.insert(cor);
		info[idx] = cor;
	}

	while(~scanf("%d",&idx)){
		int i=1;
		for(set<int,greater<int> >::iterator it = rank.begin(); it != rank.end(); it++,i++){
			if(*it == info[idx]){
				cout << i << endl;
			}
		}
	}
}

