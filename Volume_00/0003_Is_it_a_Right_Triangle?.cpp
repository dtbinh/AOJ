#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
 
int main()
{
  int T;
  scanf("%d",&T);
  for(int t=0;t<T;t++){
    int edge[3];
    scanf("%d %d %d",edge,edge+1,edge+2);
    sort(edge,edge+3,greater<int>());
    if(edge[0]*edge[0]==edge[1]*edge[1]+edge[2]*edge[2]){
      printf("%s\n","YES");
    }else{
      printf("%s\n","NO");
    }
  }
 
  return 0;
}
