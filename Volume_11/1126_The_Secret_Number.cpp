
#define _USE_MATH_DEFINES
#define INF 100000000
 
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
 
 
static const double EPS = 1e-8;
 
int tx[] = {-1,0,1,0};
int ty[] = {0,1,0,-1};
 
char stage[101][101];
int W,H;
 
string larger(const string& str1,const string& str2){
    if(str1.size() > str2.size()) return str1;
    if(str1.size() < str2.size()) return str2;
 
    for(int i=0;i<str1.size();i++){
        if(str1[i] > str2[i] ) return str1;
        if(str1[i] < str2[i] ) return str2;
    }
 
    return str1;
}
 
int main()
{
    while(~scanf("%d %d",&W,&H)){
        if(W==H && H==0) break;
        for(int y=0;y<H;y++){
            char buf[128];
            scanf("%s",buf);
            for(int x=0;x<W;x++){
                stage[y][x] = buf[x];
            }
        }
 
        string dp[101][101];
 
        for(int y=0;y<H;y++){
            for(int x=0;x<W;x++){
                string left="";
                if(isdigit(stage[y][x])){
                    if(!(dp[y+1][x].size() == 0 && stage[y][x]=='0')){
                        left = dp[y+1][x] + stage[y][x];
                    }
                }
 
                string up="";
                if(isdigit(stage[y][x])){
                    if(!(dp[y][x+1].size() == 0 && stage[y][x]=='0')){
                        up = dp[y][x+1] + stage[y][x];
                    }
                }
 
                dp[y+1][x+1] = larger(left,up);
            }
        }
 
        string res="0";
        for(int y=0;y<=H;y++){
            for(int x=0;x<=W;x++){   
                res = larger(res,dp[y][x]);
            }
        }
        cout << res << endl;
    }
 
}

