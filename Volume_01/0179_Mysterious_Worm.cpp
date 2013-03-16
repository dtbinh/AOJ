
#define _USE_MATH_DEFINES
#define MAX_N 1000000
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
typedef pair<int,string> P;

static const double eps = 1e-8;

static const char a[] = {'r','g','b'};

bool checkColor(const string& str){

	bool res = false;
	for(int i=0;i<3;i++){
		if(count(str.begin(),str.end(),a[i]) == str.size()) res=true;
	}

	return res;
}

int changeColor(string str,int cost,map<string,int>& visited){

	if(checkColor(str)) return 0;

	priority_queue<P,vector<P>,greater<P> > que;
	que.push(P(0,str));

	while(!que.empty()){
		int cost = que.top().first;
		string now = que.top().second;

		que.pop();
		for(int i=0;i+1<now.size();i++){
			string tmp = now;
			if(now[i] != now[i+1]){
				for(int j=0;j<3;j++){
					if(a[j] != now[i] && a[j] != now[i+1]){
						tmp[i] = a[j];
						tmp[i+1] = a[j];
						break;
					}
				}

				if(visited.find(tmp) != visited.end()) continue;

				visited[tmp] = cost + 1;
				if(checkColor(tmp)) return cost+1;
				que.push(P(cost+1,tmp));
			}
		}
	}

	return -1;

}

int main(){
	string str;

	while(cin>>str){
		if(str.size() == 1 && str[0] == '0') break;
		map<string,int> visited;
		visited[str] = 0;

		int res = changeColor(str,0,visited);

		if(res==-1) printf("%s\n","NA");
		else printf("%d\n",res);
	}
}

