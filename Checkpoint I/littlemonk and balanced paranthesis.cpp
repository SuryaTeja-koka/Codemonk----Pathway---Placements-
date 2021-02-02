

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
int n,count=0,max_count=0;
cin>>n;
int a[n];
for(int i=0;i<n;i++)cin>>a[i];
stack<int> s;
for(int i=0;i<n;i++){
if(!s.empty() && a[i]==-1*s.top() && s.top()>0)
{ count+=2;
//cout<<s.top();
s.pop();
//cout<<count<<endl;
}
else if(!s.empty() && s.top()>0){s.push(a[i]);max_count=max(count,max_count);count=0;}
else s.push(a[i]);

}
max_count=max(count,max_count);
cout<<max_count;
}

