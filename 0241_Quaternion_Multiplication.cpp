
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
typedef pair <int,P> PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
struct Data{
    int pos;
    int op;
};
 
int main(){
    Data table[4][4];
    table[0][0].pos = 0;
    table[0][0].op = 1;
 
    table[0][1].pos = 1;
    table[0][1].op = 1;
 
    table[0][2].pos = 2;
    table[0][2].op = 1;
 
    table[0][3].pos = 3;
    table[0][3].op = 1;
 
    table[1][0].pos = 1;
    table[1][0].op = 1;
 
    table[1][1].pos = 0;
    table[1][1].op = -1;
 
    table[1][2].pos = 3;
    table[1][2].op = 1;
 
    table[1][3].pos = 2;
    table[1][3].op = -1;
 
    table[2][0].pos = 2;
    table[2][0].op = 1;
 
    table[2][1].pos = 3;
    table[2][1].op = -1;
 
    table[2][2].pos = 0;
    table[2][2].op = -1;
 
    table[2][3].pos = 1;
    table[2][3].op = 1;
 
    table[3][0].pos = 3;
    table[3][0].op = 1;
 
    table[3][1].pos = 2;
    table[3][1].op = 1;
 
    table[3][2].pos = 1;
    table[3][2].op = -1;
 
    table[3][3].pos = 0;
    table[3][3].op = -1;
 
    int n;
    while(~scanf("%d",&n)){
        if(n==0) break;
        int co1[4];
        int co2[4];
         
        for(int i=0;i<n;i++){
            for(int j=0;j<4;j++){
                scanf("%d",co1+j);
            }
            for(int j=0;j<4;j++){
                scanf("%d",co2+j);
            }
 
            int res[4];
            memset(res,0,sizeof(res));
 
            for(int a=0;a<4;a++){
                for(int b=0;b<4;b++){
                    res[table[a][b].pos] += co1[a] * co2[b] * table[a][b].op;
                }
            }
 
            printf("%d %d %d %d\n",res[0],res[1],res[2],res[3]);
        }
    }
}

