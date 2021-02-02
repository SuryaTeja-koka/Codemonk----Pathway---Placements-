

    #include <bits/stdc++.h>
    using namespace std;
    const int MAXN = 100100, INF = 1E9 + 100;
    int a[MAXN], n, k, l[MAXN], r[MAXN];
    void solve() {
    	scanf("%d%d", &n, &k);
    	assert(1 <= n && n <= 100000);
    	assert(1 <= k && k <= 100000);
    	for (int i = 1; i <= n; i++) {
    		scanf("%d", &a[i]);
    		assert(1 <= a[i] && a[i] <= 1E9);
    	}
    	a[0] = a[n + 1] = INF;
    	vector<int> st;
    	st.push_back(0);
    	for (int i = 1; i <= n; i++) {
    		while ( a[st.back() ]<= a[i] ) {
    			st.pop_back();
    		}
    		l[i] = st.back();
    		st.push_back(i);
    	}
    	st.clear();
    	st.push_back(n + 1);
    	for (int i = n; i > 0; i--) {
    		while ( a[st.back() ]<= a[i] ) {
    			st.pop_back();
    		}
    		r[i] = st.back();
    		st.push_back(i);
    	}
    	for (int i = 1; i <= k; i++) {
    		int x;
    		scanf("%d", &x);
    		assert(1 <= x && x <= n);
    		int ans = x - l[x] + r[x] - x - 1;
    		printf("%d\n", ans);
    	}
    }
    int main()
    {
        int test;
        cin>>test;
        assert(1 <= test && test <= 50);
        while (test--) {
        	solve();
        }
        return 0;
    }

