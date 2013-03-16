
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
typedef pair <string,string> P;
typedef pair <int,P > PP;
 
int tx[] = {0,1,0,-1};
int ty[] = {-1,0,1,0};
 
static const double EPS = 1e-8;
 
 
string kang[] = {"a", "b", "c","d", "e", "f", "g", "h", "i","j", "k", "l","m","n", "o","p","q","r", "s","t", "u", "v", "w", "x", "y","z",
    "ld", "mb", "mp", "nc", "nd", "ng", "nt", "nw", "ps", "qu", "cw","ts"};
 
int main(){
    string str;
    map<string,vector<string> > dubStr;
    dubStr["m"].push_back("mb");
    dubStr["m"].push_back("mp");
 
    dubStr["l"].push_back("ld");
 
    dubStr["n"].push_back("nc");
    dubStr["n"].push_back("nd");
    dubStr["n"].push_back("ng");
    dubStr["n"].push_back("nt");
    dubStr["n"].push_back("nw");
 
    dubStr["p"].push_back("ps");
 
    dubStr["q"].push_back("qu");
 
    dubStr["c"].push_back("cw");
 
    dubStr["t"].push_back("ts");
 
    int n;
    while(getline(cin,str)){
 
        n = atoi(str.c_str());
 
        map<P,int> kangPair;
        for(int line=0;line<n;line++){
            getline(cin,str);
            stringstream ss(str);
            while(ss >> str){
                map<string,int> freq;
 
                string prev = "";
                for(int s = 0; s<str.size();){
 
                    string key = str.substr(s,1);
                    string key2="";
                    if(s<str.size()-1) key2 = str.substr(s,2);
 
 
                    if(dubStr.find(key) != dubStr.end()){
                        for(int i=0;i<dubStr[key].size();i++){
                            if(key2 == dubStr[key][i]){
 
                                if(prev != ""){
                                    kangPair[P(prev,key2)]++;
                                }
 
                                prev = key2;
                                s+=2;
                                goto next;
                            }
                        }
 
                        if(prev != ""){
                            kangPair[P(prev,key)]++;
                        }
                        prev = key;
                        s+=1;
                    }
                    else{
                        if(prev != ""){
                            kangPair[P(prev,key)]++;
                        }
                        prev = key;
                        s+=1;
                    }
next:;
                }
            }
        }
 
        for(int i=0;i<38;i++){
            int maxv = 0;
            int to=0;
            for(int j=0;j<38;j++){
                map<P,int>::iterator it;
                if((it = kangPair.find(P(kang[i],kang[j]))) == kangPair.end()) continue;
                if(maxv < it->second){
                    maxv = it->second;
                    to = j;
                }
            }
            //cout << kang[i] << endl;
            if(maxv == 0) printf("%s %s %d\n",kang[i].c_str(),"a",0);
            else printf("%s %s %d\n",kang[i].c_str(),kang[to].c_str(),maxv);
        }
    }
}

