#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f

#include <iostream>
#include <cstdio>
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
#include <cctype>
#include <utility>
  
using namespace std;
  
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
  
static const double EPS = 1e-8;
  
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};

struct TimeTable{
  int dpt;
  int arv;
};

int main(){
  int N,T;
  while(~scanf("%d %d",&N,&T)){
    map<string,TimeTable> trains;
    vector<string> stations;
    string start,last;

    for(int i=0;i<N;i++){
      char from[64];
      int from_h,from_m;

      char to[64];
      int to_h,to_m;

      scanf("%d:%d %s %d:%d %s",&from_h,&from_m,from,&to_h,&to_m,to);
      trains[from].dpt = from_h*60 + from_m;
      trains[to].arv = to_h*60 + to_m;
      stations.push_back(from);
    }

    vector<string> outputs;
    for(int i=1;i<stations.size();i++){
      if(abs(trains[stations[i]].arv - trains[stations[i]].dpt) >= T){
	char buf[128];
	sprintf(buf,"%s %d",stations[i].c_str(),abs(trains[stations[i]].arv - trains[stations[i]].dpt));
	outputs.push_back(buf);
      }
    }

    cout << outputs.size() << endl;
    for(int i=0;i<outputs.size();i++){
      cout << outputs[i] << endl;
    }
  }
}
