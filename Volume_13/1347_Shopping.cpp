#define _USE_MATH_DEFINES
#define INF 0x3f3f3f3f
#include <cstdio>
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
#include <cctype>
#include <utility>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

const static double EPS = 1e-12;

class Restriction{
public:
  int first;
  int last;
  Restriction(int first,int last)
    : first(first),last(last) {}
  bool operator<(const Restriction& r) const{
    return last < r.last;
  }
  bool operator>(const Restriction& r) const{
    return last > r.last;
  }
};

int main(){
  int num_of_shops;
  int num_of_restrictions;

  while(~scanf("%d %d",&num_of_shops,&num_of_restrictions)){
    int cost = 0;
    vector<Restriction> restrictions;
    for(int restriction_i = 0; restriction_i < num_of_restrictions; restriction_i++){
      int to,from;
      scanf("%d %d",&to,&from);
      restrictions.push_back(Restriction(to,from));
    }

    sort(restrictions.begin(),restrictions.end(),greater<Restriction>() );

    int pos = 0;
    int last = 0;
    int first = 0;
    if(restrictions.size() > 0){
      last = restrictions[pos].last;
      first = restrictions[pos].first;
    }
    while(pos < restrictions.size()){
      if(first < restrictions[pos].last){
	first = min(first,restrictions[pos].first);
      }
      else{
	cost += 2 * (last - first);
	last = restrictions[pos].last;
	first = restrictions[pos].first;
      }
      pos++;
    }
    cost += 2 * (last - first);
    cost += num_of_shops + 1;
    printf("%d\n",cost);
  }
}
