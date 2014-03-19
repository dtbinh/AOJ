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

template <class T> class Point{
private:
  T x;
  T y;
public:
  Point(T _x,T _y):x(_x),y(_y){}
  Point():x(0),y(0){}
  T getX() const{
    return x;
  }
  T getY() const{
    return y;
  }

  Point operator-(const Point &p) const{
    return Point(x - p.x, y - p.y);
  }
  Point operator+(const Point &p) const{
    return Point(x + p.x, y + p.y);
  }
  Point operator+(const double num) const{
    return Point(x + num, y + num);
  }
  void operator+=(const Point &p){
    x += p.x;
    y += p.y;
  }
  Point operator/(const T div) const{
    return Point(x / div, y / div);
  }
  void operator/=(const T div){
    x /= div;
    y /= div;
  }
};

class Block{
private:
  vector<Point<double> > cells;
  Point<double> center_of_gravity;
  vector<int> children;
  void _compute_center_of_gravity(){
    Point<double> tmp;
    for(int i=0;i<cells.size();i++){
      tmp += (cells[i] + 0.5);
    }
    if(cells.size() > 0){
      tmp /= cells.size();
    }
    center_of_gravity = tmp;
  }

public:
  Block(const vector<Point<double> >& _cells){
    cells = _cells;
    _compute_center_of_gravity();
  }
  Point<double> get_center_of_gravity() const{
    return center_of_gravity;
  }
};


void dfs(char stage[60][10],bool visited[60][10],
	 char root,int sx,int sy,vector<Point<double> >& cells,int W,int H){
  visited[sy][sx] = true;
  cells.push_back(Point<double>(sx,sy));
  for(int i=0;i<4;i++){
    int dx = sx + tx[i];
    int dy = sy + ty[i];
    if(dx < 0 || dy < 0 || dx >= W || dy >= H) continue;
    if(stage[dy][dx] != root) continue;
    if(visited[dy][dx]) continue;
    dfs(stage,visited,root,dx,dy,cells,W,H);
  }
}

void add_id(char stage[60][10],int W,int H){
  bool visited[60][10];
  memset(visited,false,sizeof(visited));

  vector<Block> blocks;
  for(int y=0;y<H;y++){
    for(int x=0;x<W;x++){
      if(visited[y][x]) continue;
      if(0 <= stage[y][x]-'0'
	 && stage[y][x]-'0' <= 9){
	vector<Point<double> > cells;
	dfs(stage,visited,stage[y][x],x,y,cells,W,H);
	cout << cells.size() << endl;
	for(int i=0;i<cells.size();i++){
	  printf("%lf %lf\n",cells[i].getX(),cells[i].getY());
	}
	Block block(cells);
	cout << block.get_center_of_gravity().getX() << endl;
	cout << block.get_center_of_gravity().getY() << endl;
	blocks.push_back(block);
	
      }
    }
  }
}

int main(){
  int W,H;
  while(~scanf("%d %d",&W,&H)){
    char stage[60][10];
    for(int y=0;y<H;y++){
      string line;
      cin >> line;
      for(int x=0;x<W;x++){
	stage[y][x] = line[x];
      }
    }

    add_id(stage,W,H);
    vector<Point<double> > points;
  }
}
