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
  
static const int tx[] = {0,1,0,-1};
static const int ty[] = {-1,0,1,0};

double ComputeEfficiency(int seed_price,
		      int seed2spear_duration,
		      int spear2leaflet_duration,
		      int leaflet2leaf_duration,
		      int leaf2flower_duration,
		      int flower2berry_duration,
		      int berry_per_seed,
		      int berry_price,
		      int seed2berry_limit){
  //ある種に対する収入は，その種から成った全ての実を売った金額から，種の値段を引いた値である．
  //また，その種の収入効率は，その収入を，種を植えてから全ての実が成り終わるまでの時間で割った値である．
  int income = (berry_price * berry_per_seed) * seed2berry_limit - seed_price;
  int time = seed2spear_duration
    + spear2leaflet_duration
    + leaflet2leaf_duration
    + seed2berry_limit * (leaf2flower_duration + flower2berry_duration);
  return (double)income/(double)time;
}

class Crop {
public:
  string name;
  double efficiency;

  Crop(string _name,double _efficiency) : name(_name),efficiency(_efficiency){}

  bool operator>(const Crop& c) const{
    if(efficiency - EPS <= c.efficiency
       && c.efficiency <= efficiency + EPS){
      return name < c.name;
    }
    return efficiency > c.efficiency;
  }
  
  bool operator<(const Crop& c) const{
    if(efficiency - EPS <= c.efficiency
       && c.efficiency <= efficiency + EPS){
      return name < c.name;
    }
    return efficiency < c.efficiency;
  }
  
};

int main(){
  int crop_num;
  
  while(~scanf("%d",&crop_num)){
    if(crop_num == 0) break;
    
    char crop_name[32];
    int seed_price,seed2spear_duration,
      spear2leaflet_duration,leaflet2leaf_duration,
      leaf2flower_duration,flower2berry_duration,
      berry_per_seed,berry_price,seed2berry_limit;

    vector<Crop> crops;
    for(int i=0;i<crop_num;i++){
      scanf("%s %d %d %d %d %d %d %d %d %d",
	    crop_name,
	    &seed_price,
	    &seed2spear_duration,
	    &spear2leaflet_duration,
	    &leaflet2leaf_duration,
	    &leaf2flower_duration,
	    &flower2berry_duration,
	    &berry_per_seed,
	    &berry_price,
	    &seed2berry_limit);
      double efficiency
	= ComputeEfficiency(seed_price,
			    seed2spear_duration,
			    spear2leaflet_duration,
			    leaflet2leaf_duration,
			    leaf2flower_duration,
			    flower2berry_duration,
			    berry_per_seed,
			    berry_price,
			    seed2berry_limit);
      crops.push_back(Crop(crop_name,efficiency));
    }

    sort(crops.begin(),crops.end(),greater<Crop>());
    for(int i=0;i<crops.size();i++){
      cout << crops[i].name << endl;
    }
    printf("#\n");
  }
}
