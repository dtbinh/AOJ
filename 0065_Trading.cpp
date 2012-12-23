
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

	int num,date;
	map<int,set<int> > m1;
	map<int,set<int> > m2;
	string str;
	bool next=false;

	while(getline(cin,str)){
		if (str.empty()){
			next = true;
			continue;
		}
		sscanf(str.c_str(),"%d,%d",&num,&date);		

		if(!next) m1[num].insert(date + 100);

		else{
			if(m1[num].size()>0){
				if(m2[num].size() == 0) m2[num] = m1[num];
				m2[num].insert(date);
			}
			
		}
	}

	for(map<int,set<int> >::iterator it = m2.begin(); it != m2.end(); it++){
		printf("%d %d\n",it->first,it->second.size());
	}
}

