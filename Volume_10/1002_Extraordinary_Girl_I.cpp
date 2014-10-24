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
#include <cstdio>

using namespace std;
 
typedef long long ll;
typedef pair <int,int> P;
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
const int tx[] = {0,1,0,-1};
const int ty[] = {-1,0,1,0};

int nodes[1001][1001];

int main(){
  int num_of_test_cases;
  while(~scanf("%d",&num_of_test_cases)){
    for(int case_i = 0; case_i < num_of_test_cases; case_i++){
      int shelves_per_line;
      scanf("%d",&shelves_per_line);
      string shelves;
      cin >> shelves;

      memset(nodes,0,sizeof(nodes));
      for(int y = 1,i=0; y <= 4; y+=2,i++){
	for(int x = 0; x <= shelves_per_line; x++){
	  if(x == 0){
	    if(shelves[(i * shelves_per_line * 2)] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	  if(x == shelves_per_line){
	    if(shelves[(i * shelves_per_line * 2) + (shelves_per_line * 2 - 1)] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	  else{
	    if(shelves[(i * shelves_per_line * 2) + 2 * x - 1] == 'Y' 
	       || shelves[(i * shelves_per_line * 2) + 2 * x] == 'Y'){
	      nodes[y][x] = 1;
	    }
	  }
	}
      }

      for(int y = 0; y < 5; y++){
	for(int x = 0; x < 10; x++){
	  printf("%d ",nodes[y][x]);
	}
	printf("\n");
      }
      printf("\n");
    }
  }
}
