
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
 
const int tx[] = {0,1,0,-1};
const int ty[] = {1,0,-1,0};
 
int main(){
    int n,r;
    while(~scanf("%d %d",&n,&r)){
        if(n==r && r==0) break;
        vector<int> pile;
        for(int i=n;i>=1;i--){
            pile.push_back(i);
        }
        for(int i=0;i<r;i++){
            int p,c;
            scanf("%d %d",&p,&c);
 
            vector<int> tmp;
            for(int j=p-1;j<p+c-1;j++){
                tmp.push_back(pile[j]);
            }
 
            for(int j=0;j<p-1;j++){
                tmp.push_back(pile[j]);
            }
 
            for(int j=p+c-1;j<n;j++){
                tmp.push_back(pile[j]);
            }
 
            pile = tmp;
        }
 
        printf("%d\n",*pile.begin());
    }
}

