
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
#include <cstdlib>
using namespace std;
 
int block[100];
 
int main(){
  int T;
  while(~scanf("%d",&T)){
    for(int t=0;t<T;t++){
      int N;
      scanf("%d",&N);
      for(int i=0;i<N;i++){
    scanf("%d",block+i);
      }
 
      int up=0,down=0;
      for(int i=0;i+1<N;i++){
    int tmp;
    if((tmp = block[i+1]-block[i])>=0) up = max(up,tmp);
    else down = max(down,abs(tmp));
      }
     
      printf("%d %dn",up,down);
    }
  }
}

