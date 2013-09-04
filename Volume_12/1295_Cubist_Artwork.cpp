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
 
const static int tx[] = {0,1,0,-1};
const static int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;

int main(){
  int col_num,row_num;
  int col[32],row[32];
  int freq[32];
  
  while(~scanf("%d %d",&col_num,&row_num)){
    if(col_num == 0 && row_num == 0) break;

    memset(col,0,sizeof(col));
    memset(row,0,sizeof(row));
    memset(freq,0,sizeof(freq));

    int total = 0;
    for(int i=0;i<col_num;i++){
      int num;
      scanf("%d",col+i);
      freq[col[i]]++;
      total += col[i];
    }

    for(int i=0;i<row_num;i++){
      scanf("%d",row+i);
      if(freq[row[i]]>0) {
	freq[row[i]]--;
	continue;
      }
      else{
	total += row[i];
      }
    }
    
    printf("%d\n",total);
  }
}

