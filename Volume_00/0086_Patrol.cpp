
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
	int u,v;
	map<int,int> m;
	while(~scanf("%d %d",&u,&v)){
		
		if(u==v && u==0){
			bool isok = true;
			for(map<int,int>::iterator it =m.begin();it != m.end(); it++){
				if(it->first == 1 && it->second % 2 == 0) isok = false;
				else if(it->first == 2 && it->second % 2 == 0) isok = false;
				else if(it->first > 2 && it->second % 2){
					isok = false;
					break;
				}
			}
			printf("%s\n",isok ? "OK" : "NG");
			m.clear();
			continue;
		}		
		m[u]++;
		m[v]++;
	}
}

