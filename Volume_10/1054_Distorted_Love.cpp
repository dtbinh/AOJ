
#define _USE_MATH_DEFINES
#define INF 100000000
#include <iostream>
#include <sstream>
#include <cmath>
#include <cstdlib>
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
typedef pair <int,int> P;
typedef pair <int,P> PP;

static const double EPS = 1e-8;

const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

class Button{
public:
	int lu_x,lu_y,rl_x,rl_y;
	string name;
	Button() : lu_x(0),lu_y(0),rl_x(0),rl_y(0),name(""){}
	Button(int lu_x,int lu_y,int rl_x,int rl_y,string name): lu_x(lu_x),lu_y(lu_y),rl_x(rl_x),rl_y(rl_y),name(name){}
};

int main(){
	int n;
	int W,H;
	
	while(~scanf("%d",&n)){
		if(n==0) break;
		map<string,vector<Button> > page;
		vector<string> browsed;
		scanf("%d %d",&W,&H);
		for(int i=0;i<n;i++){
			string name;
			int num;
			cin >> name >> num;
			for(int j=0;j<num;j++){
				string next;
				int lu_x,lu_y,rl_x,rl_y;
				cin >> lu_x >> lu_y >> rl_x >> rl_y >> next;
				page[name].push_back(Button(lu_x,lu_y,rl_x,rl_y,next));
				if(browsed.size()==0) browsed.push_back(name);
			}
		}

		int m;
		int pos = 0;
		scanf("%d",&m);
		for(int i=0;i<m;i++){
			string act;
			cin >> act;
			if(act=="click"){
				int x,y;
				cin >> x >> y;
				string now = browsed[pos];
				for(int j=0;j<page[now].size();j++){
					if((page[now][j].lu_x <= x && x <= page[now][j].rl_x)
						&& (page[now][j].lu_y <= y && y <= page[now][j].rl_y)){
							//printf("to %s\n",page[now][j].name.c_str());

							browsed.erase(browsed.begin()+pos+1,browsed.end());
							browsed.push_back(page[now][j].name);
							pos++;
							break;
					}
				}
			}
			else if(act=="back"){

				if(pos>0){
					pos--;
					//printf("back\n");
				}
			}
			else if(act=="forward"){
				if(pos<browsed.size()-1){
					pos++;
					//printf("forwardk\n");
				}
			}
			else if(act=="show"){
				cout << browsed[pos] << "\n";
			}
		}
	}
	return 0;
}


