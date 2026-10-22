#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MAXN = 200005;

ll LOG = 21;
vector<vector<ll>> up;
vector<vector<ll>> adjls;
vector<ll> tin, tout;
ll timer;

void dfs(ll u, ll p){
    tin[u] = ++timer;
    up[u][0] = p;

    for(ll i=1; i<LOG; i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }

    for(auto v: adjls[u]){
        if(v == p){
            continue;
        }

        dfs(v, u);
    }

    tout[u] = ++timer;
}

ll get_kth_ancestor(ll u, ll k){
    for(ll i=0; i<LOG; i++){
        if(k&(1LL<<i)){
            u = up[u][i];
            if(u == 0){
                break;
            }
        }
    }

    return u;
}

void solve(){
    ll n, k, q;
    cin >> n >> k >> q;

    adjls.assign(n+1, vector<ll>());
    up.assign(n+1, vector<ll> (LOG));
    tin.assign(n+1, 0);
    tout.assign(n+1, 0);
    timer = 0;

    for(ll i=0; i<n-1; i++){
        ll u, v;
        cin >> u >> v;

        adjls[u].push_back(v);
        adjls[v].push_back(u);
    }

    dfs(1, 0);

    for(ll i=0; i<q; i++){
        ll node;
        cin >> node;
        cout << get_kth_ancestor(node, k) << " ";
    }
    cout << endl;
}

#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

signed main(){
    fast;

    solve();

    return 0;
}