#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MAXN = 200005;

vector<vector<ll>> adjls;
vector<ll> childs;
vector<ll> subtree_sum;
vector<ll> dp;

void dfs1(ll u, ll p){
    childs[u] = 1;
    subtree_sum[u] = 0;

    for(auto v: adjls[u]){
        if(v == p){
            continue;
        }

        dfs1(v, u);

        childs[u] += childs[v];
        subtree_sum[u] += subtree_sum[v];
        subtree_sum[u] += childs[v];
    }
}

void dfs2(ll u, ll p, ll n){
    dp[u] = subtree_sum[u];

    if(p != 0){
        ll rem_child = n-childs[u];
        ll parent_contribution = dp[p]-dp[u]-childs[u];
        dp[u] += parent_contribution;
        dp[u] += rem_child;
    }

    for(auto v: adjls[u]){
        if(v == p){
            continue;
        }

        dfs2(v, u, n);
    }
}

void solve(){
    ll n;
    cin >> n;

    adjls.assign(n+1, vector<ll>());
    for(ll i=0; i<n-1; i++){
        ll u, v;
        cin >> u >> v;

        adjls[u].push_back(v);
        adjls[v].push_back(u);
    }

    childs.assign(n+1, 0);
    subtree_sum.assign(n+1, 0);
    dfs1(1, 0);

    dp.assign(n+1, 0);
    dfs2(1, 0, n);

    for(ll i=1; i<=n; i++){
        cout << dp[i] << " ";
    }
    cout << endl;
}

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

signed main(){
    fast;

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }

    return 0;
}