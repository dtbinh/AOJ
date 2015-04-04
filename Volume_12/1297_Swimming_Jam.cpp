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
#include <iterator>
#include <complex>
#include <assert.h>
 
using namespace std;
 
typedef long long ll;
typedef pair <double,double> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};//URDL
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

ll GCD(ll a ,ll b){
  return b > 0 ? GCD(b,a%b) : a;
}

ll LCM(ll a ,ll b){
  return a / GCD(a,b) * b;
}

class Swimmer{
public:
  int current_pace;
  int natural_pace;
  int laps;
  int pos;
  int prev_pos;
  int dir;
  Swimmer(int current_pace,int natural_pace,int laps)
    : current_pace(current_pace),natural_pace(natural_pace),laps(laps),pos(0),prev_pos(0),dir(0) {}
};

int main(){
  int num_of_swimmers;
  while(~scanf("%d",&num_of_swimmers)){
    if(num_of_swimmers == 0) break;
    
    int length = 1;
    vector<Swimmer> swimmers;
    for(int i = 0; i < num_of_swimmers; i++){
      int natural_pace;
      int laps;
      scanf("%d %d",&natural_pace,&laps);
      length = LCM(natural_pace,length);
      swimmers.push_back(Swimmer(natural_pace,natural_pace,laps));
    }

    int res = 0;
    for(int time = 0; time <= 150000; time++){
      bool has_swimmer = false;
      for(int i = 0; i < swimmers.size(); i++){
	if(swimmers[i].laps == 0) continue;
	has_swimmer = true;
	int speed = length / swimmers[i].current_pace;
	swimmers[i].prev_pos = swimmers[i].pos;
	swimmers[i].pos += speed * 1;
      }

      if(!has_swimmer){
	res = time;
	break;
      }

      for(int i = 0; i < swimmers.size(); i++){
	for(int j = i+1; j < swimmers.size(); j++){
	  if(swimmers[i].laps == 0 || swimmers[j].laps == 0) continue;
	  if(swimmers[i].dir == swimmers[j].dir
	     && swimmers[i].pos != 0){
	    if(swimmers[i].pos > swimmers[j].pos
	       && swimmers[i].prev_pos < swimmers[j].prev_pos){
	      swimmers[i].pos = swimmers[j].pos;
	      swimmers[i].current_pace = swimmers[j].current_pace;
	    }
	    else if(swimmers[i].pos < swimmers[j].pos
		    && swimmers[i].prev_pos > swimmers[j].prev_pos){
	      swimmers[j].pos = swimmers[i].pos;
	      swimmers[j].current_pace = swimmers[i].current_pace;
	    }
	    else if(swimmers[i].pos == swimmers[j].pos){
	      swimmers[i].current_pace = max(swimmers[i].current_pace,swimmers[j].current_pace);
	      swimmers[j].current_pace = max(swimmers[i].current_pace,swimmers[j].current_pace);
	    }
	  }
	}
      }

      for(int i = 0; i < swimmers.size(); i++){
	if(swimmers[i].pos == length){
	  if(swimmers[i].dir == 1){
	    swimmers[i].laps--;
	  }

	  swimmers[i].dir = (swimmers[i].dir == 1 ? 0 : 1);
	  swimmers[i].current_pace = swimmers[i].natural_pace;
	  swimmers[i].pos = 0;
	}
      }


    }
    printf("%d\n",res);
  }
}
