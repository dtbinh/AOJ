
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
typedef pair<string,int> P;

class mycmp{
public:
	bool operator()(const P p1, const P p2){
		return p1.second > p2.second;
	}
};

int main(){
	char buf[64];
	int win,lose,draw;	
	int n;
	bool isnl = false;
	while(~scanf("%d",&n)){
		if(n==0) break;
		if(isnl){
			cout << endl;
		}
		vector<P> data;
		for(int i=0,j=0;i<n;i++){
			scanf("%s %d %d %d",buf,&win,&lose,&draw);
			data.push_back(P(buf,win*3+draw*1));
		}
		
		sort(data.begin(),data.end(),mycmp());

		for(int i=0;i<data.size();i++){
			printf("%s,%d\n",data[i].first.c_str(),data[i].second);
		}
		isnl=true;
	}
}


