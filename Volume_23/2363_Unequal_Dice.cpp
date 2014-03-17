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
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-14;

struct Spot{
  int num;
  double probability;
  Spot(int _n,double _p) : num(_n),probability(_p){}
};

int main(){
  int total_dices;
  while(~scanf("%d",&total_dices)){
    vector<double> exp_v;
    for(int dice_idx=0;dice_idx<total_dices;dice_idx++){
      int total_surface;
      int total_numbered_surface;
      scanf("%d %d",
	    &total_surface,
	    &total_numbered_surface);
      
      double remaining = 1.0;
      double exp = 0.0;
      
      vector<Spot> dice;
      for(int surface_idx=0;surface_idx<total_numbered_surface;surface_idx++){
	int num;
	double probability;
	scanf("%d %lf",&num,&probability);
	dice.push_back(Spot(num,probability));
	
	remaining -= probability;
	exp += num * probability;
      }
      
      while(remaining >= EPS){
	double tmp = 0.0;
	for(int surface_idx=0;surface_idx<total_numbered_surface;surface_idx++){
	  exp += dice[surface_idx].num * remaining * dice[surface_idx].probability;
	  tmp += remaining * dice[surface_idx].probability;
	  
	}
	remaining -= tmp;
      }
      exp_v.push_back(exp);
    }

    int total_boss_surface;
    int total_numbered_boss_surface;
    scanf("%d %d",
	  &total_boss_surface,
	  &total_numbered_boss_surface);
    
    double boss_remaining = 1.0;
    double boss_exp = 0.0;
    
    vector<Spot> boss_dice;
    for(int surface_idx=0;surface_idx<total_numbered_boss_surface;surface_idx++){
      int num;
      double probability;
      scanf("%d %lf",&num,&probability);
      boss_dice.push_back(Spot(num,probability));
      
      boss_remaining -= probability;
      boss_exp += num * probability;
    }
    
    while(boss_remaining >= EPS){
      double tmp = 0.0;
      for(int surface_idx=0;surface_idx<total_numbered_boss_surface;surface_idx++){
	boss_exp += boss_dice[surface_idx].num * boss_remaining * boss_dice[surface_idx].probability;
	tmp += boss_remaining * boss_dice[surface_idx].probability;
	
      }
      boss_remaining -= tmp;
    }

    bool is_win = false;
    for(int exp_idx=0;exp_idx<exp_v.size();exp_idx++){
      if(exp_v[exp_idx] > boss_exp + 1e-7) is_win = true;
    }
    printf("%s\n",is_win ? "YES" : "NO");
  }
}
