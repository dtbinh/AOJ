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

int search_diagonal(int sx,int sy,int sz,
		    int stage[10][10][10],int WH,int seq_num);
int search_virtical(int sx,int sy,int sz,
		    int stage[10][10][10],int WH,int seq_num);
int search_horizontal_x(int sx,int sy,int sz,
		    int stage[10][10][10],int WH,int seq_num);
int search_horizontal_y(int sx,int sy,int sz,
		    int stage[10][10][10],int WH,int seq_num);

string isClear(int stage[10][10][10],int WH,int seq_num){
  for(int sx=0;sx<WH;sx++){
    for(int sy=0;sy<WH;sy++){
      for(int sz=0;sz<WH;sz++){
	int ans = 0;
	ans = search_diagonal(sx,sy,sz,stage,WH,seq_num);
	if(ans == -seq_num) return "Black";
	else if(ans == seq_num) return "White";

	ans = search_virtical(sx,sy,sz,stage,WH,seq_num);
	if(ans == -seq_num) return "Black";
	else if(ans == seq_num) return "White";

	ans = search_horizontal_x(sx,sy,sz,stage,WH,seq_num);
	if(ans == -seq_num) return "Black";
	else if(ans == seq_num) return "White";

	ans = search_horizontal_y(sx,sy,sz,stage,WH,seq_num);
	if(ans == -seq_num) return "Black";
	else if(ans == seq_num) return "White";
      }
    }
  }
  return "Draw";
}
int search_virtical(int sx,int sy,int sz,
		    int stage[10][10][10],int WH,int seq_num){
  int sum1 = 0;
  for(int z=sz;z<sz+seq_num && z < WH;z++){
    sum1 += stage[sx][sy][z];
  }
  return sum1;
}

int search_horizontal_x(int sx,int sy,int sz,
		      int stage[10][10][10],int WH,int seq_num){
  int sum1 = 0;
  for(int x=sx;x<sx+seq_num && x < WH;x++){
    sum1 += stage[x][sy][sz];
  }
  return sum1;
}

int search_horizontal_y(int sx,int sy,int sz,
		      int stage[10][10][10],int WH,int seq_num){
  int sum1 = 0;
  for(int y=sy;y<sy+seq_num && y < WH;y++){
    sum1 += stage[sx][y][sz];
  }
  return sum1;
}

int search_diagonal(int sx,int sy,int sz,
		     int stage[10][10][10],int WH,int seq_num){
  //x++,y++,z++
  int sum1 = 0;
  for(int x=sx,y=sy,z=sz;
      x<sx+seq_num && x < WH 
	&& y<sy+seq_num && y < WH
	&& z<sz+seq_num && z < WH;
      x++,y++,z++){
	sum1 += stage[x][y][z];
  }
  if(abs(sum1) == seq_num) return sum1;
  
  //y++,z++
  int sum2 = 0;
  for(int y=sy,z=sz;
      y<sy+seq_num && y < WH
	&& z<sz+seq_num && z < WH;
      y++,z++){
    sum2 += stage[sx][y][z];
  }
  if(abs(sum2) == seq_num) return sum2;

  //y++,z--
  int sum2_a = 0;
  for(int y=sy,z=sz;
      y<sy+seq_num && y < WH
	&& z >= 0;
      y++,z--){
    sum2_a += stage[sx][y][z];
  }
  if(abs(sum2_a) == seq_num) return sum2_a;
  
  //z++,x++
  int sum3 = 0;
  for(int x=sx,z=sz;
      x<sx+seq_num && x < WH
	&& z<sz+seq_num && z < WH;
      x++,z++){
    sum3 += stage[x][sy][z];
  }
  if(abs(sum3) == seq_num) return sum3;

  //z++,x--
  int sum3_a = 0;
  for(int x=sx,z=sz;
      x >= 0
	&& z<sz+seq_num && z < WH;
      x--,z++){
    sum3_a += stage[x][sy][z];
  }
  if(abs(sum3_a) == seq_num) return sum3_a;

  //x++,y++
  int sum4 = 0;
  for(int x=sx,y=sy;
      x<sx+seq_num && x < WH
	&& y<sy+seq_num && y < WH;
      x++,y++){
    sum4 += stage[x][y][sz];
  }
  if(abs(sum4) == seq_num) return sum4;

  //x++,y--
  int sum4_a = 0;
  for(int x=sx,y=sy;
      x<sx+seq_num && x < WH
	&& y >= 0;
      x++,y--){
    sum4_a += stage[x][y][sz];
  }
  if(abs(sum4_a) == seq_num) return sum4_a;

  //x--,y--,z++
  int sum5 = 0;
  for(int x=sx,y=sy,z=sz;
      x >= 0 
	&& y >= 0
	&& z<sz+seq_num && z < WH;
      x--,y--,z++){
	sum5 += stage[x][y][z];
  }
  if(abs(sum5) == seq_num) return sum5;

  //x--,y++,z++
  int sum6 = 0;
  for(int x=sx,y=sy,z=sz;
      x >= 0
	&& y<sy+seq_num && y < WH
	&& z<sz+seq_num && z < WH;
      x--,y++,z++){
	sum6 += stage[x][y][z];
  }
  if(abs(sum6) == seq_num) return sum6;

  //x++,y--,z++
  int sum7 = 0;
  for(int x=sx,y=sy,z=sz;
      x<sx+seq_num && x < WH 
	&& y >= 0
	&& z<sz+seq_num && z < WH;
      x++,y--,z++){
	sum7 += stage[x][y][z];
  }
  if(abs(sum7) == seq_num) return sum7;
  
  return 0;
}

int main(){
  int WH,seq_num,move_num;
  while(~scanf("%d %d %d",&WH,&seq_num,&move_num)){
    if(WH == 0) break;

    int freq[10][10];
    int stage[10][10][10];
    memset(freq,0,sizeof(freq));
    memset(stage,0,sizeof(stage));

    string res_str = "Draw";
    int res_move = -1;
    for(int i=1;i<=move_num;i++){
      int tmp_x,tmp_y;
      scanf("%d %d",&tmp_x,&tmp_y);
      
      int x = tmp_x - 1;
      int y = tmp_y - 1;
      int z = freq[x][y];

      //black
      if(i % 2){
	stage[x][y][z] = -1;
      }
      
      //white
      else{
	stage[x][y][z] = 1;
      }
      freq[x][y]++;

      string judge = isClear(stage,WH,seq_num);
      if(res_move == -1 && (judge == "Black" || judge == "White")){
	res_str = judge;
	res_move = i;
      }
    }

    if(res_move == -1){
      printf("Draw\n");
    }
    else{
      printf("%s %d\n",res_str.c_str(),res_move);
    }
  }
}
