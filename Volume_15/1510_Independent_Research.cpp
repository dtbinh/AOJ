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

void simulate(int cells[5][5][5],
	      int days,
	      int birth_condition_num,int birth_conditions[50],
	      int dead_condition_num,int dead_conditions[50]
){
  for(int i=0;i<days;i++){
    int tmp[5][5][5];
    memcpy(tmp,cells,sizeof(int)*5*5*5);

    for(int x=0;x<5;x++){
      for(int y=0;y<5;y++){
	for(int z=0;z<5;z++){
	  int live=0,die=0;
	  for(int tx=-1;tx<=1;tx++){
	    for(int ty=-1;ty<=1;ty++){
	      for(int tz=-1;tz<=1;tz++){
		if(tx == ty && ty == tz && tz == 0) continue;

		int dx = x + tx;
		int dy = y + ty;
		int dz = z + tz;
		if(dx < 0 || dy < 0 || dz < 0 
		   || dx >=5 || dy >=5 || dz >=5) continue;
		if(cells[dx][dy][dz] == 1) live++;
	      }
	    }
	  }
	  if(cells[x][y][z] == 0){

	    bool islive = false;
	    for(int i=0;i<birth_condition_num;i++){
	      if(birth_conditions[i] == live){
		islive = true;
		break;
	      }
	    }

	    if(islive) tmp[x][y][z] = 1;
	  }
	  else if(cells[x][y][z] == 1){
	    bool isdie = true;
	    for(int i=0;i<dead_condition_num;i++){
	      if(dead_conditions[i] == live){
		isdie = false;
	      }
	    }

	    if(isdie) tmp[x][y][z] = 0;
	  }
	}
      }
    }

    memcpy(cells,tmp,sizeof(int)*5*5*5);
  }
}

void print_cage(int cells[5][5][5]){
  for(int z=0;z<5;z++){
    for(int y=0;y<5;y++){
      for(int x=0;x<5;x++){
	printf("%d",cells[x][y][z]);
      }
      printf("\n");
    }
    if(z <= 3)printf("\n");
  }
}

int main(){
  int simulation_days;
  int case_num = 1;
  while(~scanf("%d",&simulation_days)){
    if(simulation_days == 0) break;
    int cells[5][5][5];
    for(int z=0;z<5;z++){
      for(int y=0;y<5;y++){
	string str;
	cin >> str;
	for(int x=0;x<5;x++){
	  cells[x][y][z] = str[x]-'0';
	}
      }
    }
    int birth_condition_num,dead_condition_num;
    int birth_conditions[50],dead_conditions[50];

    scanf("%d",&birth_condition_num);
    for(int i=0;i<birth_condition_num;i++){
      scanf("%d",birth_conditions + i);
    }

    scanf("%d",&dead_condition_num);
    for(int i=0;i<dead_condition_num;i++){
      scanf("%d",dead_conditions + i);
    }
    simulate(cells,simulation_days,
	     birth_condition_num,birth_conditions,
	     dead_condition_num,dead_conditions);

    if(case_num != 1) printf("\n");
    printf("Case %d:\n",case_num);
    case_num++;

    print_cage(cells);
  }
}
