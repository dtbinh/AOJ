
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
typedef pair<int,int> P;

int main(){

	string str;
	int idx;
	char buf[64];
	map<string,set<int> > pages;
	while(~scanf("%s %d",buf,&idx)){
		pages[buf].insert(idx);
	}

	for(map<string,set<int> >::iterator it = pages.begin(); it != pages.end(); it++){
		printf("%s\n",it->first.c_str());

		int i=0;
		for(set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++){

			printf("%d%s",*it2,i==it->second.size()-1 ? "\n" : " ");
			i++;
		}
	}
}

