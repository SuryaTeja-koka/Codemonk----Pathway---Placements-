

    // I can't tell you what it really is,
    // I can only tell you what it feels like.
    #include "bits/stdc++.h"
    using namespace std;
     
    #define int long long
    #define F first
    #define S second
    #define siz(x) ((int)x.size())
    #define rep(i,a,n) for (int i = a; i <= n; ++i)
    #define all(v)  v.begin(), v.end()
    #define pb push_back
    #define P pair < int, int >
    #define E cout << '\n'
    const int mod = 1e9 + 7;
    const int N = 100000 + 5;
    int a[N], sz[N];
    int dp[N], idx[N], ctr;
    int arr[N], n;
    multiset<int>st;
    vector<int>v[N];
    class merge_sort_tree{
        public:
        vector < P > tree[N << 2];
        vector<int>suff_max[N<<2];    
        void build(int l, int r, int node){
            if (l > r)return;
            if(l == r){
                int x = arr[l];
                tree[node].pb({a[x], x});
                return ;
            }
            int mid = l + r >> 1, lc = node + node, rc = 1 + lc;
            build(l, mid, lc);    build(mid + 1, r, rc);
            merge(all(tree[lc]), all(tree[rc]), back_inserter(tree[node]));
        }
        int query(int l, int r, int ql, int qr, int val, int node){
            if(qr < l || r < ql || l > r || ql > qr)
                return 0;
            if(ql <= l and r <= qr){           
                if (tree[node].empty() || tree[node].back().first <= val) return 0;
                int lo = 0, hi = siz(tree[node])-1, mid;
                while (lo <= hi) {
                    mid = (lo+hi)/2;
                    if (tree[node][mid].first > val) hi = mid - 1;
                    else lo = mid+1;
                }
                assert(hi+1>=0 && hi+1<siz(tree[node]));
               return suff_max[node][hi+1];
            }
            int mid = l + r >> 1, lc = node + node, rc = 1 + lc;
            return max(query(l, mid, ql, qr, val, lc),query(mid + 1, r, ql, qr, val, rc));
        }
        void make_suffix_max() {
            for (int i = 1; i < 4*N; ++i) {
                if (tree[i].empty()) continue;
                suff_max[i].resize(siz(tree[i]));
                suff_max[i].back() = dp[tree[i].back().second];
                for (int j = siz(tree[i])-2; j >= 0; --j) {
                  suff_max[i][j] = max(dp[tree[i][j].second], suff_max[i][j+1]);
                }
            }
        }
    };
    merge_sort_tree obj; 
    int dfs(int node, int p = 0) {
        assert(ctr <= 1e5);
        idx[node] = ++ctr;
        arr[ctr] = node;
        sz[node] = 1;   
        int mx = a[node];
        for (int x: v[node]) {
            if (x != p) {
                mx = max(mx, dfs(x, node)); 
                sz[node] += sz[x];
            }
        }
        return dp[node] = mx;
    }
    int dfs2(int x, int p) {
        st.insert(a[x]);
        int ans = 0;
        if (dp[x]) {
           auto it = st.lower_bound(a[x]);
           if (it != st.begin()) {
            int ok = obj.query(1, n, idx[x]+1, idx[x]+sz[x]-1, a[x], 1);
            if (ok) {
                --it;
                ans = max(ans, ok+a[x]+*it);
            }
           }
        }
        for (int ok: v[x]) {
            if (ok != p) {
                ans = max(ans, dfs2(ok,x));
            }
        }
        st.erase(st.find(a[x]));
        return ans;
    }
    inline void solve() {
       int ans = 0;
       cin >> n;
       rep(i,1,n) {
        cin >> a[i];
       }
       int l, r;
       rep(i,2,n) {
        cin >> l >> r;
        v[l].push_back(r);
        v[r].push_back(l);
       }   
       dfs(1);
       rep(i,1,n) {
        dp[i] += (dp[i]==a[i] ? -dp[i]:a[i]);
       }   
       obj.build(1,n,1);
       obj.make_suffix_max();
       cout << dfs2(1, 0);  
    }
    signed main() {
      ios_base::sync_with_stdio(0);
      cin.tie(NULL);
      cout.tie(NULL);
      int t = 1;
      //cin >> t; while(t--)
      solve();
      return 0;
    }

