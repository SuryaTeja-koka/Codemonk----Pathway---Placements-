#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for(int i = 0; i < (n); i++)
const int N = 111;
int a[N];
int main() {
	int n, m, t, mx = -1, ans = 0;
	cin >> n >> m >> t;
	rep(i, n)
		cin >> a[i];
	sort(a, a + n);
	rep(i, n - 1)
		mx = max(mx, a[i + 1] - a[i]);
	rep(i, m) {
		cin >> t;
		if(t <= mx)
			ans++;
	}
	cout << ans << endl;
	return 0;
}
