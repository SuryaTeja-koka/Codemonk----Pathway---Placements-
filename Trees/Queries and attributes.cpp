#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 14;
const ll inf = 1e18;
 
int n, a[maxn], l[maxn], r[maxn];
ll b[maxn];
multiset<ll> s;
vector<ll> add[maxn], rem[maxn];
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n;
	for(int i = 0; i < n; i++)
		cin >> a[i];
	for(int i = 0; i < n; i++)
		cin >> l[i] >> r[i], l[i]--, r[i]--;
	for(int i = n - 1; i >= 0; i--){
		for(auto x : add[i])
			s.insert(x);
		if(i != n - 1)
			b[i] = s.size() ? *s.begin() : inf;
		if(i){
			add[ r[i] ].push_back(b[i] + a[i]);
			rem[ l[i] ].push_back(b[i] + a[i]);
		}
		for(auto x : rem[i])
			s.erase(s.find(x));
	}
	for(int i = 1; i < n; i++)
		b[i] = min(b[i - 1], b[i]);
	int q;
	cin >> q;
	while(q--){
		int x, y;
		cin >> x >> y;
		cout << b[x - 1] + y << '\n';
	}
}
