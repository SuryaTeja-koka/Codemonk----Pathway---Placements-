#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string.h>
#include <math.h>
#include <stdio.h>
//#include "D:\C++\test_lib_projects\testlib.h"
using namespace std;
#define ll long long
#define pii pair<int,int>
bool debug=true;
/*
   Write In New Computer
    By XiaoGeNintendo
	     gwq2017
	Type:Sol 
*/
//void fo(int id){
//	freopen((toString(id)+".txt").c_str(),"w",stdout);
//}
set<pii> st;
bool stand=true;
ll n,m,q;
ll ans;
int main(int argc,char* argv[]){
	scanf("%lld%lld%lld",&n,&m,&q);
	for(int i=0;i<q;i++){
		int mode;
		scanf("%d",&mode);
		if(mode==1){
			int x,y;
			scanf("%d%d",&x,&y);
			set<pii>::iterator pos=st.find(make_pair(x,y));
			if(pos!=st.end()){
				st.erase(pos);
				if(stand){
					ans--;
				}else{
					ans++;
				}
			}else{
				st.insert(make_pair(x,y));
				if(stand){
					ans++;
				}else{
					ans--;
				}
			}
		}else{
			ans=n*m-ans;
			stand=!stand;
		}
	}
	
	cout<<ans;
	return 0;
}
