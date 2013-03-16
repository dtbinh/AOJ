
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
typedef pair <int,P> PP;
 
static const double EPS = 1e-8;
 
int tx[] = {0,1,1,1,0,-1,-1,-1};
int ty[] = {-1,-1,0,1,1,1,0,-1};
 
 
int gSum=0;
 
string shrink(const string& stage,int x1,int y1,int x2,int y2){
    string res="";
 
    for(int i=0;i<stage.size();i++){
 
        if( i % 4 == x1 && i / 4 == y1) continue;
        if( i % 4 == x2 && i / 4 == y2) continue;
        res.push_back(stage[i]);
    }
 
    res.push_back('-');
    res.push_back('-');
    return res;
}
 
void dfs(const string& stage,map<string,char>& visited,int count){
    for(int y=0;y<5;y++){
        for(int x=0;x<4;x++){
            char c = stage[y*4+x];
            if(c=='-') continue;
            for(int i=0;i<8;i++){
                int dx = x + tx[i];
                int dy = y + ty[i];
                if(dx < 0 || dx >= 4 || dy < 0 || dy >= 5) continue;
                if(stage[dy*4+dx] == '-') continue;
                if(c == stage[dy*4+dx]){
                    string next = shrink(stage,x,y,dx,dy);
                    if(visited.find(next) != visited.end()) continue;
                    if(visited.find(next) != visited.end() && visited[next] >= count+1) continue;
                    visited[next] = count+1;
                    dfs(next,visited,count+1);
                    gSum = max(count+1,gSum);
                }
            }
        }
    }
}
 
int main(){
    int n;
    string stage;
    while(~scanf("%d",&n)){
        for(int i=0;i<n;i++){
            gSum = 0;
            stage="";
            for(int y=0;y<5;y++){
                for(int x=0;x<4;x++){
                    string str;
                    cin >> str;
                    stage += str;
                }
            }
 
            map<string,char> visited;
 
            dfs(stage,visited,0);       
            printf("%d\n",20-gSum*2);
        }
    }
 
}

