
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

bool space[100];
int W,Q;

void fillSpace(int id,int pos,int wid,map<int,P>& data){
	for(int i=pos;i<pos+wid;i++){
		space[i] = true;
	}
	data[id]=P(pos,wid);
}

void eraseSpace(int id,int pos,int wid){
	for(int i=pos;i<pos+wid;i++){
		space[i] = false;
	}
}

bool stay(int id,int wid,map<int,P>& data){
	for(int i=0;i<W;i++){
		bool isok = true;
		if(i+wid > W) isok = false;
		for(int j=i;j<i+wid && j<W;j++){
			if(space[j]) {
				isok = false;
				break;
			}
		}
		if(isok){
			fillSpace(id,i,wid,data);
			printf("%d\n",i);
			return true;
		}
	}

	return false;
}


int main(){
	while(~scanf("%d %d",&W,&Q)){
		if(W==0 && Q==0) break;
		string sw;
		map<int,P> data;
		memset(space,0,sizeof(space));

		for(int i=0;i<Q;i++){
			cin >> sw;
			if(sw == "s"){
				int id,wid;
				scanf("%d %d",&id,&wid);
				if(!stay(id,wid,data)){
					printf("impossible\n");
				}
			}
			else{
				int id;
				scanf("%d",&id);
				eraseSpace(id,data[id].first,data[id].second);
			}
		}
		printf("END\n");
	}
}



