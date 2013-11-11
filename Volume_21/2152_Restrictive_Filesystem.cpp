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
  int start;
  int last;
  Sector(int _s,int _l) : start(_s), last(_l) {}
};

class File {
public:
  int file_id;
  vector<Sector> sectors;
};

class FileSystem {
public:
  vector<File> files;

  void write_sectors(int file_id,int required_sectors){
    for(int i=0;i<files.size();i++){
      if(files[i].file_id == -1){
	files[i].file_id = file_id;
	  for(int j=0;j<files[i].sectors.size();j++){
	    int size = files[i].sectors[j].last - files[i].sectors[j].start + 1;
	    if(required_sectors >= size){
	      required_sectors -= size;
	    }
	    else{
	      files[i].sectors[j].last
		= files[i].sectors[j].start + (size - required_sectors);
	      return;
	    }
	  }
      }
    }
  }
  void delete_sectors(int file_id){
    for(int i=0;i<files.size();i++){
      for(int j=0;j<files[i].sectors.size();j++){
      }
      if(file_id==files[i].file_id){
	files[i].file_id = -1;
      }
    }
  }

  int refer_file_id(int sector_id){
    for(int i=0;i<files.size();i++){
      for(int j=0;j<files[i].sectors.size();j++){
	if(files[i].sectors[j].start <= sector_id 
	   && sector_id <= files[i].sectors[j].last){
	  return files[i].file_id;
	}
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
  }
}
