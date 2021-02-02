

    #include <bits/stdc++.h>
    using namespace std;
    long long N , M , L , R , k , ans;
    void print(vector<long long> v)
    {
        for(auto u : v)
            cout<<u<<" ";
        cout<<"\n";
    }
    void divisors(vector<long long>&a , long long target )
    {
        for(long long i = 1;i*i<=target ; i++)
        {
            if(target % i==0)
            {
                if(i>=L && i<=R && i>ans && i!=M)
                    a.push_back(i);
                if(target/i>=L && target/i<=R&& target/i>ans && target/i!=M)
                    a.push_back(target/i);
            }
        }
    }
    void solve()
    {
        vector<long long > A;
        long long sz = 0;
        if(N<M)
        {
            L = max( L , N+1);
            if(L<=R)
            {
                sz =R-L+1 - ( M>=L && M<=R );
                if( sz<=k)
                {
                    for(int i = L;i<=R;i++){
                        if(i==M)
                            continue;
                        A.push_back(i);
                    }
                }
            }
        }
        else
        {
            divisors(A , N-ans);
            sort(A.begin() , A.end());
            A.resize(unique(A.begin() , A.end()) - A.begin() );
            sz = A.size();
        }
        cout<<sz<<"\n";
        if(sz<=k)
            print(A);
        else
            cout<<-1;
    }
    int main() {
        cin>>N>>M;
        cin>>L>>R;
        cin>>k;
        ans = N%M;
        solve();
        return 0;
    }

