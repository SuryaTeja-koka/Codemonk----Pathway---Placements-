    #include<bits/stdc++.h>
     
    using namespace std;
     
    typedef long long ll;
    typedef pair<int, int> pii;
    typedef long double ld;
     
    #define F first
    #define S second
     
    const int MOD = 1e9 + 7;//XXX
    const int C = 26;//XXX
     
    void add(int &x, int y){
    	x += y;
    	while (x >= MOD) x -= MOD;
    	while (x < 0) x += MOD;
    }
     
    int fix(int x){
    	while (x >= MOD) x -= MOD;
    	while (x < 0) x += MOD;
    	return x;
    }
     
    int pw(int a, int b){
    	int ret = 1;
    	while (b){
    		if (b & 1)
    			ret = 1ll*ret*a%MOD;
    		b >>= 1;
    		a = 1ll*a*a%MOD;
    	}
    	return ret;
    }
     
    const int MAXN = 2e5 + 10;
    const int LOG = 18;
     
    int n, q;
     
    int lz[LOG][MAXN<<2];
    int seg[LOG][MAXN<<2];
     
    void apply(int v, int b, int e, int w, int t) {
    	if (!t) return;
    	if (t == 3) {
    		seg[w][v] = (e - b) - seg[w][v];
    		lz[w][v] = 3 - lz[w][v];
    	} else if (t == 2) {
    		seg[w][v] = 0;
    		lz[w][v] = 2;
    	} else {
    		seg[w][v] = e-b;
    		lz[w][v] = 1;
    	}
    }
     
    void pushDown(int v, int b, int e, int mid, int w) {
    	if (!lz[w][v]) return;
     
    	apply(v<<1, b, mid, w, lz[w][v]);
    	apply(v<<1^1, mid, e, w, lz[w][v]);
     
    	lz[w][v] = 0;
    }
     
    void updSeg(int v, int b, int e, int l, int r, int w, int t) {
    	if (l <= b && e <= r) {
    		apply(v, b, e, w, t);
    		return;
    	}
    	if (r <= b || e <= l) return;
     
    	int mid = b + e >> 1;
    	pushDown(v, b, e, mid, w);
    	updSeg(v<<1, b, mid, l, r, w, t);
    	updSeg(v<<1^1, mid, e, l, r, w, t);
    	seg[w][v] = seg[w][v<<1] + seg[w][v<<1^1];
    }
     
    int getSeg(int v, int b, int e, int l, int r, int w) {
    	if (l <= b && e <= r)
    		return seg[w][v];
    	if (r <= b || e <= l) return 0;
     
    	int mid = b + e >> 1;
    	pushDown(v, b, e, mid, w);
    	return getSeg(v<<1, b, mid, l, r, w) + getSeg(v<<1^1, mid, e, l, r, w);
    }
     
    void solve() {
    	int q;
    	cin >> n >> q;
    	while (q--) {
    		int t; cin >> t;
    		if (t <= 3) {
    			int l, r, x; cin >> l >> r >> x, l--;
    			for (int w = 0; w < LOG; w++) {
    				int z = (x>>w&1);
    				if (t == 1) {
    					if (z)
    						updSeg(1, 0, n, l, r, w, 1);
     
    				} else if (t == 2) {
    					if (!z)
    						updSeg(1, 0, n, l, r, w, 2);
    				} else {
    					if (z)
    						updSeg(1, 0, n, l, r, w, 3);
    				}
    			}
    		} else {
    			int l, r; cin >> l >> r, l--;
    			ll ans = 0;
    			for (int w = 0; w < LOG; w++) {
    				int cnt = getSeg(1, 0, n, l, r, w);
    				if (t == 4) {
    					ans += 1ll*cnt*(1ll<<w);
    				} else if (cnt & 1){
    					ans += 1ll<<w;
    				}
    			}
    			cout << ans << "\n";
    		}
    	}
    }
     
    int main(){
    	ios::sync_with_stdio(false);
    	cin.tie(0);
    	cout.tie(0);
    	//cout << fixed << setprecision(6);
    	
    	int te = 1;	
    	//cin >> te;
    	for (int w = 1; w <= te; w++){
    		//cout << "Case #" << w << ": ";
    		solve();
    	}
    	return 0;
    }
