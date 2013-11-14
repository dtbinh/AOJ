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

struct Sector {
  int file_id;
  int first;
  int last;
  Sector(int _f,int _s,int _l) : file_id(_f), first(_s), last(_l) {}
  int size() {return last - first + 1;}
};

class FileSystem {
private:
  vector<Sector> sectors;
public:
  FileSystem(){
    sectors.clear();
    sectors.push_back(Sector(-1,0,1000000007));
  }
  void write_sectors(int file_id,int required_sectors){
    for(vector<Sector>::iterator it = sectors.begin();
	it != sectors.end();
	it++){
      if(it->file_id == -1){
	it->file_id = file_id;
	if(required_sectors < it->size()){
	  int l = it->last;
	  it->last = it->first + required_sectors - 1;
	  int f = it->last + 1;
	  it++;
	  sectors.insert(it,1,Sector(-1,f,l));
	  break;
	}
	else {
	  required_sectors -= it->size();
	}
      }
    }
  }

  void delete_sectors(int file_id){
    for(vector<Sector>::iterator it = sectors.begin();
	it != sectors.end();
	it++){
      if(it->file_id == file_id){
	it->file_id = -1;
      }
    }
  }

  int refer_file_id(int sector_id){
    for(vector<Sector>::iterator it = sectors.begin();
	it != sectors.end();
	it++){
      if(it->first <= sector_id
	 && sector_id <= it->last){
	return it->file_id;
      }
    }
    return -1;
  }
};

int main(){
  int total_commands;
  while(~scanf("%d",&total_commands)){
    FileSystem fs;
    for(int command_idx = 0; command_idx < total_commands; command_idx++){
      char operation[2];
      scanf("%s",operation);
      if(operation[0] == 'W'){
	int file_id,required_sectors;
	scanf("%d %d",&file_id,&required_sectors);
	fs.write_sectors(file_id,required_sectors);
      }
      else if(operation[0] == 'D'){
	int file_id;
	scanf("%d",&file_id);
	fs.delete_sectors(file_id);
      }
      else if(operation[0] == 'R'){
	int sector_id;
	scanf("%d",&sector_id);
	cout << fs.refer_file_id(sector_id) << endl;
      }
    }
    if(total_commands !=0) cout << "\n";
  }
}
