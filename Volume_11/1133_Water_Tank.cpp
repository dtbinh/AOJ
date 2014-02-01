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
typedef pair <int,int> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

class Cell {
public:
  int parent;
  int brother;

  int capacity;
  int height;
  int start_x;
  int end_x;
  Cell(int _h,int _sx,int _ex) : height(_h),start_x(_sx),end_x(_ex){
    capacity = height * (end_x - start_x);
  }

  void pour_water(int _water){
    capacity -= _water;
  }

  bool is_filled(){
    return (capacity <= 0);
  }

  bool operator<(const Cell& c) const{
    return start_x < c.start_x;
  }
};

struct Board{
  int x;
  int height;
  Board(int _x,int _h) : x(_x), height(_h) {}
};

int main(){
  int total_data_sets;
  while(~scanf("%d",&total_data_sets)){
    vector<Cell> cells;
    vector<Board> boards;
    for(int data_set_idx = 0; data_set_idx < total_data_sets; data_set_idx++){
      int total_boards;
      scanf("%d",&total_boards);

      boards.push_back(Board(0,50));
      for(int board_idx = 0; board_idx < total_boards; board_idx++){
	int x,height;
	scanf("%d %d",&x,&height);
	boards.push_back(Board(x,height));
      }
      boards.push_back(Board(100,50));

      for(int src_idx = 0; src_idx < boards.size(); src_idx++){
	if(boards[src_idx].x == 100) continue;

	for(int target_idx = src_idx+1; target_idx < boards.size(); target_idx++){
	  if(boards[target_idx].height < boards[src_idx].height) continue;

	  else if(boards[target_idx].height >= boards[src_idx].height){
	    cells.push_back(Cell(boards[src_idx].height,boards[src_idx].x,boards[target_idx].x));
	    break;
	  }
	}

	for(int target_idx = src_idx-1; target_idx >= 0; target_idx--){
	  if(boards[target_idx].height < boards[src_idx].height) continue;

	  else if(boards[target_idx].height > boards[src_idx].height){
	    cells.push_back(Cell(boards[src_idx].height,boards[src_idx].x,boards[target_idx].x));
	    break;
	  }
	}
      }

      for(int i=0;i<cells.size();i++){
	printf("idx%d sx:%d ex:%d height:%d\n",i,cells[i].start_x,cells[i].end_x,cells[i].height);
      }

      //set brother
      for(int src_idx=0;src_idx<cells.size();src_idx++){
	for(int target_idx = 0; target_idx < cells.size(); target_idx++){
	  if(src_idx == target_idx) continue;

	  int height = cells[src_idx].height;
	  if(cells[src_idx].end_x == cells[target_idx].start_x
	  && height >= cells[target_idx].height){
	    height = cells[target_idx].height;
	    cells[src_idx].brother = target_idx;
	  }
	  if(cells[src_idx].start_x == cells[target_idx].end_x
	     && height >= cells[target_idx].height){
	    height = cells[target_idx].height;
	    cells[src_idx].brother = target_idx;
	  }
	}
      }

      //set parent
      for(int src_idx=0;src_idx<cells.size();src_idx++){
	for(int target_idx = 0; target_idx < cells.size(); target_idx++){
	  if(src_idx == target_idx) continue;
	  int lower_height = cells[src_idx].height;
	  int min_height = INF;

	  if(cells[src_idx].start_x >= cells[target_idx].start_x
	     && cells[src_idx].end_x <= cells[target_idx].end_x
	     && lower_height <= cells[target_idx].height
	     && min_height > cells[target_idx].height){
	    min_height = cells[target_idx].height;
	    cells[src_idx].parent = target_idx;
	  }
	}
      }

      int total_faucets;
      for(int foucet_idx = 0; foucet_idx < total_faucets; foucet_idx++){
	int x,cm3_per_second;
	scanf("%d %d",&x,&cm3_per_second);
      }

      int total_observation_times;
      for(int observation_time_idx = 0; observation_time_idx < total_observation_times; observation_time_idx++){
	int x,time;
	scanf("%d %d",&x,&time);
      }
    }
  }
}
