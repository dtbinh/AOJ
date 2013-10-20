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

bool Rin_visited[50][50];
bool Len_visited[50][50];
char stage_Len[50][50];
char stage_Rin[50][50];

bool can_reach;
int W,H;

void Rin_dfs(int Rin_x,int Rin_y,int Len_x,int Len_y){
  for(int i=0;i<4;i++){
    int Rin_dx = Rin_x + tx_r[i];
    int Rin_dy = Rin_y + ty_r[i];

    int Len_dx = Len_x + tx_l[i];
    int Len_dy = Len_y + ty_l[i];
    if(Rin_dx < 0 || Rin_dx >= W || Rin_dy < 0 || Rin_dy >= H){
	continue;
    }
    if(Len_dx < 0 || Len_dx >= W || Len_dy < 0 || Len_dy >= H){
	continue;
    }
    if(stage_Rin[Rin_dy][Rin_dx] == '#'){
      continue;
    }
    if(stage_Len[Len_dy][Len_dx] == '#'){
      Len_dy = Len_y;
      Len_dx = Len_x;
    }

    if(Rin_visited[Rin_dy][Rin_dx]){
      continue;
    }


    if(stage_Len[Len_dy][Len_dx] == '%'
       && stage_Rin[Rin_dy][Rin_dx] == '%'){
      can_reach = true;
      return;
    }

    if(stage_Len[Len_dy][Len_dx] != '%'
       && stage_Rin[Rin_dy][Rin_dx] != '%'){
      Rin_visited[Rin_dy][Rin_dx] = true;
      Rin_dfs(Rin_dx,Rin_dy,Len_dx,Len_dy);
    }
  }
}

void Len_dfs(int Rin_x,int Rin_y,int Len_x,int Len_y){
  for(int i=0;i<4;i++){
    int Rin_dx = Rin_x + tx_r[i];
    int Rin_dy = Rin_y + ty_r[i];

    int Len_dx = Len_x + tx_l[i];
    int Len_dy = Len_y + ty_l[i];
    if(Rin_dx < 0 || Rin_dx >= W || Rin_dy < 0 || Rin_dy >= H){
	continue;
    }
    if(Len_dx < 0 || Len_dx >= W || Len_dy < 0 || Len_dy >= H){
	continue;
    }
    if(stage_Rin[Rin_dy][Rin_dx] == '#'){
      Rin_dy = Rin_y;
      Rin_dx = Rin_x;
    }
    if(stage_Len[Len_dy][Len_dx] == '#'){
      continue;
    }

    if(Len_visited[Len_dy][Len_dx]){
      continue;
    }

    Len_visited[Len_dy][Len_dx] = true;
    if(stage_Len[Len_dy][Len_dx] == '%'
       && stage_Rin[Rin_dy][Rin_dx] == '%'){
      can_reach = true;
      return;
    }

    if(stage_Len[Len_dy][Len_dx] != '%'
       && stage_Rin[Rin_dy][Rin_dx] != '%'){
      Len_visited[Len_dy][Len_dx] = true;
      Len_dfs(Rin_dx,Rin_dy,Len_dx,Len_dy);
    }
  }
}

int main(){

  while(~scanf("%d %d",&W,&H)){
    if(W==0 && H==0) break;

    memset(Len_visited,false,sizeof(Len_visited));
    memset(Rin_visited,false,sizeof(Rin_visited));
    can_reach = false;
    
    int Rin_start_x = 0;
    int Rin_start_y = 0;
    int Len_start_x = 0;
    int Len_start_y = 0;
 
    for(int y=0;y<H;y++){
      string str_Len,str_Rin;
      cin >> str_Len >> str_Rin;
      
      // cout << str_Len << endl;
      // cout << str_Rin << endl;

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

    Len_dfs(Rin_start_x,Rin_start_y,Len_start_x,Len_start_y);
    Rin_dfs(Rin_start_x,Rin_start_y,Len_start_x,Len_start_y);
    printf("%s\n",can_reach ? "Yes" : "No");
  }
}
