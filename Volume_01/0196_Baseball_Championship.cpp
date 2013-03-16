
#define _USE_MATH_DEFINES
#define INF 10000000
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
#include <list>

using namespace std;

typedef long long ll;
typedef pair<int,string> P;

static const double eps = 1e-8;

class DATA{
public:
	string name;
	int win;
	int lose;
	int draw;
	DATA() : win(0),lose(0),draw(0){}
};

class mycmp{
public:
	bool operator()(const DATA d1, const DATA d2){
		if(d1.win > d2.win) return true;
		if(d1.win == d2.win && d1.lose < d2.lose) return true;
		return false;
	}
};

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;

		vector<DATA> teams;
		for(int i=0;i<n;i++){
			char name[32];
			scanf("%s",&name);
			DATA data;
			data.name = name;
			for(int j=0;j<n-1;j++){
				int result;
				scanf("%d",&result);
				if(result==0) data.win++;
				else if(result==1) data.lose++;
				else if(result==2) data.draw++;
			}

			teams.push_back(data);
		}

		sort(teams.begin(),teams.end(),mycmp());

		for(int i=0;i<teams.size();i++){
			printf("%s\n",teams[i].name.c_str());
		}
	}
}

