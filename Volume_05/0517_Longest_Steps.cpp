
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
 
bool cards[1000000]; 
 
int main(){
    int n,k;
    while(~scanf("%d %d",&n,&k)){
        if(n==0 && k==0) break;
         
        memset(cards,0,sizeof(cards));
 
        bool hasWhite = false;
        for(int i=0;i<k;i++){
            int num;
            scanf("%d",&num);
            cards[num] = true;
            if(num == 0) hasWhite = true;
        }
 
        if(hasWhite){
            int suc = 0;
            for(int i=1;i<=n;i++){
                int tmp = 0;
                bool mistake = false;
                for(int j=i;j<=n;j++){
                    if(cards[j]){
                        tmp++;
                        suc = max(tmp,suc);
                    }
                    else{
                        if(!mistake){
                            mistake = true;
                            tmp++;
                            suc = max(tmp,suc);
                            continue;
                        }
                        break;
                    }
                }
            }
 
            printf("%d\n",suc);
        }
        else{
            int suc = 0;
            for(int i=1;i<=n;i++){
                int tmp = 0;
                for(int j=i;j<=n;j++){
                    if(cards[j]){
                        tmp++;
                        suc = max(tmp,suc);
                    }
                    else{
                        i=++j;
                        break;
                    }
                }
            }
 
            printf("%d\n",suc);
        }
    }
}

