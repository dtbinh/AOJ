#define _USE_MATH_DEFINES
#define INF 100000000
 
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

struct Purse{
  int possess10;
  int possess100;
  Purse(int _p10,int _p100){
    possess10 = _p10;
    possess100 = _p100;
  }
};

int main(){
  int total_2DRespecters;
  int storage10;
  int storage100;
  int upper_storage10;
  while(~scanf("%d %d %d %d",
	       &total_2DRespecters,
	       &storage10,
	       &storage100,
	       &upper_storage10)){

    vector<Purse> respecters;
    for(int respect_idx = 0; respect_idx < total_2DRespecters; respect_idx++){
      int possess10,possess100;
      scanf("%d %d",&possess10,&possess100);
      respecters.push_back(Purse(possess10,possess100));
    }
    
    int res = 0;
    int sum = 0;
    for(int round = 0; round < 10000000; round++){
      int idx = round % total_2DRespecters;
;
      if(respecters[idx].possess10 > 0){
	sum += 10;
	respecters[idx].possess10--;
	storage10++;
      }
      else if(respecters[idx].possess100 > 0){
	sum += 100;
	respecters[idx].possess100--;
	storage100++;
      }
      else{
	res = idx+1;
	break;
      }
      
      if(storage10 > upper_storage10){
	res = idx + 1;
	break;
      }
      
      if(sum >= 90){
	int diff = sum - 90;
	int limit100 = diff / 100;
	
	bool isok = false;
	for(int limit=0;limit<=limit100;limit++){
	  int pay100 = limit;
	  int pay10 = (diff - (limit * 100)) / 10;
	  if(pay10 <= storage10 && pay100 <= storage100){
	    storage10 -= pay10;
	    storage100 -= pay100;
	    
	    sum = 0;
	    respecters[idx].possess10 += pay10;
	    respecters[idx].possess100 += pay100;
	    isok = true;
	    break;
	  }
	}

	if(!isok){
	  res = idx + 1;
	  break;
	}
      }
      
    }
    printf("%d\n",res);
  }
}
