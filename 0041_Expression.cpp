
#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
#include <limits>
#include <map>
#include <string>
#include <cstring>

typedef long long ll;
using namespace std;

int calc(int a,int b,int pat)
{
	if(pat == 0) return a*b;
	else if(pat == 1) return a+b;
	else if(pat == 2) return a-b;

	return -1;
}

void dfs(int* idx,int* num,int c,string form,int now,vector<string>& res){

	if(res.size() > 0) return;
	if (now == 10 && c==4){
		res.push_back(form);
	}

	if(c >= 4) return;

	string next;
	next.push_back(num[idx[c]] + '0');

	string form_mu = "(" + form + " * " + next + ")";
	string form_p = "(" + form + " + " + next + ")";
	string form_mi = "(" + form + " - " + next + ")";


	dfs(idx,num,c+1,form_mu,now*num[idx[c]],res);

	dfs(idx,num,c+1,form_mi,now-num[idx[c]],res);

	dfs(idx,num,c+1,form_p,now+num[idx[c]],res);

}

void two_pair(int* idx,int* num,vector<string>& res){
	if(res.size() > 0) return;
	int flag[] = {0,0,1,1};
	char opr[] = {'*','+','-'};

	do{
		vector<int> front;
		vector<int> rear;
		for(int i=0;i<4;i++){
			if(flag[i]) front.push_back(num[idx[i]]);
			else rear.push_back(num[idx[i]]);
		}

		sort(front.begin(),front.end());
		sort(rear.begin(),rear.end());
		do{
			do{

				for(int i=0;i<3;i++){
					for(int j=0;j<3;j++){
						for(int k=0;k<3;k++){
							int tmp1 = calc(front[0],front[1],i);
							int tmp2 = calc(rear[0],rear[1],j);
							int total = calc(tmp1,tmp2,k);

							if(total == 10){
								char buf[256];
								sprintf(buf,"((%d %c %d) %c (%d %c %d))",front[0],opr[i],front[1],opr[k],rear[0],opr[j],rear[1]);
								res.push_back(buf);
							}
						}
					}
				}

			}while(next_permutation(front.begin(),front.end()));

		}while(next_permutation(rear.begin(),rear.end()));

	}while(next_permutation(flag,flag+4));
}

void three_pair(int* idx,int* num,vector<string>& res){
	if(res.size() > 0) return;

	int flag[] = {0,0,0,1};
	char opr[] = {'*','+','-'};

	do{
		vector<int> front;
		vector<int> rear;

		for(int i=0;i<4;i++){
			if(flag[i]) front.push_back(num[idx[i]]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
			else rear.push_back(num[idx[i]]);
		}

		sort(rear.begin(),rear.end());

		do{

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					for(int k=0;k<3;k++){
						int tmp1 = calc(rear[0],rear[1],i);
						int tmp2 = calc(tmp1,rear[2],j);
						int total = calc(front[0],tmp2,k);

						if(total == 10){
							char buf[256];
							sprintf(buf,"(%d %c ((%d %c %d) %c %d))",front[0],opr[k],rear[0],opr[i],rear[1],opr[j],rear[2]);
							res.push_back(buf);
						}
					}
				}
			}

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					for(int k=0;k<3;k++){
						int tmp1 = calc(rear[1],rear[2],i);
						int tmp2 = calc(rear[0],tmp1,j);
						int total = calc(front[0],tmp2,k);

						if(total == 10){
							char buf[256];
							sprintf(buf,"(%d %c (%d %c (%d %c %d)))",front[0],opr[k],rear[0],opr[i],rear[1],opr[j],rear[2]);
							res.push_back(buf);
						}
					}
				}
			}

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					for(int k=0;k<3;k++){
						int tmp1 = calc(rear[1],rear[2],i);
						int tmp2 = calc(rear[0],tmp1,j);
						int total = calc(tmp2,front[0],k);

						if(total == 10){
							char buf[256];
							sprintf(buf,"((%d %c (%d %c %d)) %c %d)",rear[0],opr[j],rear[1],opr[i],rear[2],opr[k],front[0]);
							res.push_back(buf);
						}
					}
				}
			}

			for(int i=0;i<3;i++){
				for(int j=0;j<3;j++){
					for(int k=0;k<3;k++){
						int tmp1 = calc(rear[0],rear[1],i);
						int tmp2 = calc(tmp1,rear[2],j);
						int total = calc(tmp2,front[0],k);

						if(total == 10){
							char buf[256];
							sprintf(buf,"(((%d %c %d) %c %d) %c %d)",rear[0],opr[i],rear[1],opr[j],rear[2],opr[k],front[0]);
							res.push_back(buf);
						}
					}
				}
			}

		}while(next_permutation(rear.begin(),rear.end()));

	}while(next_permutation(flag,flag+4));
}

int main(){
	int num[4];
	while(~scanf("%d %d %d %d",num,num+1,num+2,num+3)){

		bool isend=true;
		for(int i=0;i<4;i++){
			if(num[i] != 0) isend = false;
		}

		if(isend) return 0;

		int idx[] = {0,1,2,3};

		vector<string> ans;

		do{
			string init;
			init.push_back(num[idx[0]] + '0');
			dfs(idx,num,1,init,num[idx[0]],ans);
			two_pair(idx,num,ans);
			three_pair(idx,num,ans);
		}while(next_permutation(idx,idx+4));


		if(ans.size() == 0) cout << 0 << endl;
		else cout << ans[0] << endl;
	}

}


