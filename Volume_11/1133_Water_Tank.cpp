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

  int water;
  int capacity;
  int height;
  int start_x;
  int end_x;
  Cell(int _h,int _sx,int _ex) : height(_h),start_x(_sx),end_x(_ex),
				 parent(-1),brother(-1),water(0){
    capacity = height * (end_x - start_x);
  }

  void pour_water(int _water){
    water += _water;
  }

  bool is_filled(){
    return (capacity <= water);
  }

  bool operator<(const Cell& c) const{
    return start_x < c.start_x;
  }
};

struct Board{
  int x;
  int height;
  Board(int _x,int _h) : x(_x), height(_h) {}
  bool operator<(const Board& b) const{
    return x < b.x;
  }
  bool operator>(const Board& b) const{
    return x > b.x;
  }
};

struct Faucet{
  int x;
  int cm3_per_second;
  Faucet(int _x,int _c) : x(_x), cm3_per_second(_c) {}
  Faucet() : x(0), cm3_per_second(0) {}

  bool operator <(const Faucet& f) const{
    return (x < f.x);
  }

  bool operator >(const Faucet& f) const{
    return (x > f.x);
  }
  bool operator ==(const Faucet& f) const{
    return (x == f.x);
  }

  bool operator <(const int _x) const{
    return (x < _x);
  }
  bool operator >(const int _x) const{
    return (x > _x);
  }
  bool operator ==(const int _x) const{
    return (x == _x);
  }
};

int main(){
  int total_data_sets;
  while(~scanf("%d",&total_data_sets)){
    for(int data_set_idx = 0; data_set_idx < total_data_sets; data_set_idx++){

      vector<Cell> cells;
      vector<Board> boards;
      int total_boards;
      scanf("%d",&total_boards);

      boards.push_back(Board(0,50));
      for(int board_idx = 0; board_idx < total_boards; board_idx++){
	int x,height;
	scanf("%d %d",&x,&height);
	boards.push_back(Board(x,height));
      }
      boards.push_back(Board(100,50));

      sort(boards.begin(),boards.end());
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
	    cells.push_back(Cell(boards[src_idx].height,boards[target_idx].x,boards[src_idx].x));
	    break;
	  }
	}
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


      vector<Faucet> faucets;
      int total_faucets;
      scanf("%d",&total_faucets);
      for(int foucet_idx = 0; foucet_idx < total_faucets; foucet_idx++){
	int x,cm3_per_second;
	scanf("%d %d",&x,&cm3_per_second);
	faucets.push_back(Faucet(x,cm3_per_second));
      }

      sort(faucets.begin(),faucets.end());


      int total_observation_times;
      scanf("%d",&total_observation_times);

      vector<Cell> store = cells;
      for(int observation_time_idx = 0; observation_time_idx < total_observation_times; observation_time_idx++){
	int x,time;
	scanf("%d %d",&x,&time);
	
	for(int cell_idx = 0;cell_idx < cells.size(); cell_idx++){
	  int faucet_idx = lower_bound(faucets.begin(),faucets.end(),cells[cell_idx].start_x) - faucets.begin();

	  if(faucet_idx == faucets.size()) continue;
	  if(faucets[faucet_idx].x > cells[cell_idx].end_x) continue;

	  cells[cell_idx].pour_water(faucets[faucet_idx].cm3_per_second * time);
	}

	for(int i=0;i<cells.size();i++){
	  printf("idx%d sx:%d ex:%d height:%d cap:%d water:%d\n",i,cells[i].start_x,cells[i].end_x,cells[i].height,cells[i].capacity,cells[i].water);
	}

	cells = store;
      }
    }
  }
}
