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
#include <complex>
 
using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P > PP;

typedef complex<double> Point;
const static double EPS = 1e-12;

int main(){
  int bit_length;
  int run_length;
  while(~scanf("%d %d",&bit_length,&run_length)){
    int bits = 0;
    for(int i = 0; i < bit_length; i++){
      int bit;
      scanf("%d",&bit);
      if(bit > 0) bits |= (1<<i);
    }
    
    vector<int> width;
    for(int i = 0; i < run_length; i++){
      int run;
      scanf("%d",&run);
      width.push_back(run);
    }

    for(int S = 0; S < (1<<bit_length); S++){
      int offset = 0;
      bool isok = true;
      for(int i = 0; i < width.size(); i++){
	if(offset > 0 && ((S >> offset) & 1) == ((S >> (offset-1)) & 1)){
	  isok = false;
	  break;
	}
	for(int j = offset; j + 1 < offset + width[i]; j++){
	  if(((S >> j) & 1) != ((S >> (j+1)) & 1)){
	    isok = false;
	    break;
	  }
	}
	offset += width[i];
	if(!isok) break;
      }

      if(isok){
	for(int i = 0; i < bit_length; i++){
	  printf("%d",(S & (1<<i)) ? 1 : 0);
	}
	printf("\n");
      }
    }
  }
}
