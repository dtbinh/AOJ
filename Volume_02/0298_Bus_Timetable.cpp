#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <iostream>
#include <sstream>
#include <cstdio>
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

static const double EPS = 1e-8;

int main(){
  int total_imori_buses;
  while(~scanf("%d",&total_imori_buses)){
    set<int> buses;
    for(int imori_i = 0; imori_i < total_imori_buses; imori_i++){
      int hour,minute;
      scanf("%d %d",&hour,&minute);
      buses.insert(hour * 60 + minute);
    }
    int total_tsuruga_buses;
    scanf("%d",&total_tsuruga_buses);
    for(int tsuruga_i = 0; tsuruga_i < total_tsuruga_buses; tsuruga_i++){
      int hour,minute;
      scanf("%d %d",&hour,&minute);
      buses.insert(hour * 60 + minute);
    }

    bool is_first = true;
    for(set<int>::iterator it = buses.begin();
	it != buses.end();
	it++){
      printf("%s%d:%02d",is_first ? "" : " ",*it / 60,*it % 60);
      is_first = false;
    }
    printf("\n");
  }
}
