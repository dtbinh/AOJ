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
 
//int tx[] = {0,1,0,-1};
//int ty[] = {-1,a0,1,0};
 
const int tx[] = {0,1,1,0};
const int ty[] = {0,0,1,1};
 
static const double EPS = 1e-8;
 
ll mypow(ll x,int power){
    ll res = 1;
    while(power>0){
        if(power & 1) res *= x;
        x *= x;
        power >>= 1;
    }
    return res;
}
 
void init_format(vector<vector<string> >& bit_format){
    bit_format.resize(4);
 
    bit_format[0].push_back("0xxxxxxx");
 
    bit_format[1].push_back("110yyyyx");
    bit_format[1].push_back("10xxxxxx");
 
    bit_format[2].push_back("1110yyyy");
    bit_format[2].push_back("10yxxxxx");
    bit_format[2].push_back("10xxxxxx");
 
    bit_format[3].push_back("11110yyy");
    bit_format[3].push_back("10yyxxxx");
    bit_format[3].push_back("10xxxxxx");
    bit_format[3].push_back("10xxxxxx");
}
 
ll CountPatterns(int start,int last,const vector<vector<string> >& bit_format,const vector<string>& bits,int len){
    bool isok = true;
 
    int x_num = 0;
    int y_num = 0;
    int y1_num = 0;
    int y0_num = 0;
 
    for(int i=start,k=0;i<bits.size() && i <= last && k< bit_format[len-1].size();i++,k++){
 
        for(int j=0;j<bits[i].size() && j< bit_format[len-1][k].size();j++){
 
            if(bits[i][j]=='x'){
                if(bit_format[len-1][k][j] == 'x'){
                    x_num++;
                }
 
                else if(bit_format[len-1][k][j] == 'y'){
                    y_num++;
                }
            }
 
            else if(bits[i][j]=='1'){
                if(bit_format[len-1][k][j] =='0'){
                    isok = false;
                }
 
                else if(bit_format[len-1][k][j] == 'y'){
                    y1_num++;
                }
                else{
                    continue;
                }
            }
            else if(bits[i][j] == '0'){
                if(bit_format[len-1][k][j] =='1'){
                    isok = false;
                }
                else if(bit_format[len-1][k][j] == 'y'){
                    y0_num++;
                }
            }
        }
    }
 
    if(y_num==0 && y1_num==0 && y0_num > 0) isok = false;
 
    ll x_patterns = mypow(2,x_num);
    ll y_patterns = 1;
 
    if(y1_num > 0){
        y_patterns = mypow(2,y_num);
    }
    else{
        y_patterns = mypow(2,y_num)-1;
    }
 
    if(y_patterns == 0) y_patterns = 1;
    if(!isok) return 0;
 
    x_patterns %= 1000000;
    y_patterns %= 1000000;
 
    return x_patterns*y_patterns % 1000000LL;
}
 
ll dp[1001];
 
int main(){
    vector<vector<string> > bit_format;
    init_format(bit_format);
 
    int N;
    while(cin >> N){
        if(N==0) break;
 
        string line;
        vector<string> bits;
        for(int i=0;i<N;i++){
            string line;
            cin >> line;
            bits.push_back(line);
        }
 
         
        memset(dp,0,sizeof(dp));
        for(int start=0;start<N ;start++){
            for(int len = 4; len >=1; len--){
                if(start-len+1 < 0) continue;
                ll patterns = CountPatterns(start-len+1,start,bit_format,bits,len); 
                dp[start] += patterns * (start-len >=0 ? dp[start-len] : 1);
                dp[start] %= 1000000LL;
            }
        }
        printf("%ld\n",dp[N-1]%1000000LL);
    }
}
