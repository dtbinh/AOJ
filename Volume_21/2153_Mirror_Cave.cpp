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
  
static const int tx_r[] = {0,1,0,-1};
static const int ty_r[] = {-1,0,1,0};

static const int tx_l[] = {0,-1,0,1};
static const int ty_l[] = {-1,0,1,0};

bool visited[51][51][51][51];
char stage_Len[51][51];
char stage_Rin[51][51];

bool can_reach;
int W,H;

void dfs(int Rin_x,int Rin_y,int Len_x,int Len_y){
  for(int i=0;i<4;i++){
    int Rin_dx = Rin_x + tx_r[i];
    int Rin_dy = Rin_y + ty_r[i];

    int Len_dx = Len_x + tx_l[i];
    int Len_dy = Len_y + ty_l[i];
    cout << Rin_dx << " " << Rin_dy << " " << Len_dx << " " << Len_dy << endl;
    if(Rin_dx < 0 || Rin_dx >= W || Rin_dy < 0 || Rin_dy >= H){
      Rin_dy = Rin_y;
      Rin_dx = Rin_x;
    }
    else if(stage_Rin[Rin_dy][Rin_dx] == '#'){
      Rin_dy = Rin_y;
      Rin_dx = Rin_x;
    }

    if(Len_dx < 0 || Len_dx >= W || Len_dy < 0 || Len_dy >= H){
      Len_dy = Len_y;
      Len_dx = Len_x;
    }
    else if(stage_Len[Len_dy][Len_dx] == '#'){
      Len_dy = Len_y;
      Len_dx = Len_x;
    }

    if(visited[Rin_dx][Rin_dy][Len_dx][Len_dy]){
      continue;
    }

    if(stage_Len[Len_dy][Len_dx] == '%'
       && stage_Rin[Rin_dy][Rin_dx] == '%'){
      can_reach = true;
      return;
    }

    if(stage_Len[Len_dy][Len_dx] != '%'
       && stage_Rin[Rin_dy][Rin_dx] != '%'){
      visited[Rin_dx][Rin_dy][Len_dx][Len_dy] = true;
      dfs(Rin_dx,Rin_dy,Len_dx,Len_dy);
    }
  }
}

int main(){

  while(~scanf("%d %d",&W,&H)){
    if(W==0 && H==0) break;

    for(int y=0;y<H;y++){
      for(int x=0;x<W;x++){
	for(int y2=0;y2<H;y2++){
	  for(int x2=0;x2<W;x2++){
	    visited[x][y][x2][y2] = false;
	  }
	}
      }
    }

    can_reach = false;
    
    int Rin_start_x = 0;
    int Rin_start_y = 0;
    int Len_start_x = 0;
    int Len_start_y = 0;
 
    for(int y=0;y<H;y++){
      string str_Len,str_Rin;
      cin >> str_Len >> str_Rin;
      
      cout << str_Len << endl;
      cout << str_Rin << endl;

      for(int x=0;x<W;x++){
	stage_Len[y][x] = str_Len[x];
	stage_Rin[y][x] = str_Rin[x];

	if(str_Len[x] == 'L'){
	  Len_start_x = x;
	  Len_start_y = y;
	}
	if(str_Rin[x] == 'R'){
	  Rin_start_x = x;
	  Rin_start_y = y;
	}
      }
    }

    visited[Rin_start_x][Rin_start_y][Len_start_x][Len_start_y] = true;
    dfs(Rin_start_x,Rin_start_y,Len_start_x,Len_start_y);
    printf("%s\n",can_reach ? "Yes" : "No");
  }
}
