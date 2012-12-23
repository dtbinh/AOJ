
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
typedef pair <int,int> P;
typedef pair <int,P> PP;
typedef pair <int,PP> PPP;

static const double eps = 1e-8;

struct Player{
	int load;
	int arv;
	int dpt;
};

struct Load{
	int time;
	int w;
};

class mycmp{
public:
	bool operator()(const Player p1,const Player p2){
		return p1.arv < p2.arv;
	}
};

int main(){
	int n;
	while(~scanf("%d",&n)){
		if(n==0) break;
		Load* load = new Load[n+1];
		Player* player = new Player[n];
		for(int i=0;i<n;i++){
			int m,a,b;
			scanf("%d %d %d",&m,&a,&b);
			Player p = {m,a,b};
			player[i] = p;
		}

		sort(player,player+n,mycmp());

		load[0].w = 0;
		load[0].time = -1;
		for(int i=0;i<=n;i++){
			Load l = {player[i].arv,player[i].load + load[i].w};
			load[i+1] = l;
		}

		for(int i=0;i<n;i++){
			for(int j=0;j<=n;j++){
				if(player[i].dpt <= load[j].time){
					for(int k=j;k<=n;k++){
						load[k].w -= player[i].load;
					}
					goto next;
				}
			}
next:;
		}

		int max_v = -1;
		for(int i=0;i<=n;i++){
			//printf("i=%d time=%d load=%d\n",i,load[i].time,load[i].w);
			max_v = max(load[i].w,max_v);
		}

		if(max_v > 150) printf("NG\n");
		else printf("OK\n");

	}
}

