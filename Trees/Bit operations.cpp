#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 17;
int n, q, a[maxn];
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> n >> q;
	while(q--){
		int t, l, r, x;
		cin >> t >> l >> r;
		l--;
		if(t < 4){
			cin >> x;
			while(l < r)
				if(t == 1)
					a[l++] |= x;
				else if(t == 2)
					a[l++] &= x;
				else
					a[l++] ^= x;
		}
		else if(t == 4)
			cout << accumulate(a + l, a + r, 0ll) << '\n';
		else
			cout << accumulate(a + l, a + r, 0, [](int a, int b){  return a ^ b;  }) << '\n';
		// for(int i = 0; i < n; i++)
		// 	cerr << a[i] << ' ';
		// cerr << '\n';
	}
}
