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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

struct Star {
  int x;
  int y;
  int brightness;
  Star(int x,int y,int brightness) 
    : x(x), y(y), brightness(brightness) {}
  bool operator>(const Star& s) const {
    return brightness > s.brightness;
  }
};

int main(){
  int total_stars;
  int brightness_limit;
  while(~scanf("%d %d",
	       &total_stars,
	       &brightness_limit)){

    priority_queue<Star,vector<Star>,greater<Star> > que;
    for(int star_i = 0; star_i < total_stars; star_i++){
      int x;
      int y;
      int brightness;
      scanf("%d %d %d",&x,&y,&brightness);
      que.push(Star(x,y,brightness));
    }

    int lower_idx = 0;
    vector<Star> stars;

    multiset<int> xs;
    multiset<int> ys;

    ll res = 0;
    while(!que.empty()){
      Star s = que.top();
      que.pop();

      while(lower_idx < stars.size()
	    && s.brightness - stars[lower_idx].brightness > brightness_limit){
	xs.erase(xs.find(stars[lower_idx].x));
	ys.erase(ys.find(stars[lower_idx].y));
	lower_idx++;
      }
      xs.insert(s.x);
      ys.insert(s.y);
      stars.push_back(s);

      res = max(res,(ll)(*(--xs.end()) - *xs.begin()) * (ll)(*(--ys.end()) - *ys.begin()));
    }
    printf("%lld\n",res);
  }
}
