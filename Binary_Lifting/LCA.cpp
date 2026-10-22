#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MAXN = 200005;

vector<vector<ll>> adjls;
vector<vector<ll>> up;
vector<ll> depth;

ll LOG = 21;

void dfs1(ll u, ll p){
    depth[u] = depth[p]+1;
    
    up[u][0] = p;
    for(ll i=1; i<LOG; i++){
        up[u][i] = up[up[u][i-1]][i-1];
    }

    for(auto v: adjls[u]){
        if(v == p){
            continue;
        }

        dfs1(v, u);
    }
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

ll get_LCA(ll u, ll v){
    if(u == v){
        return u;
    }

    if(depth[u] != depth[v]){
        if(depth[u] > depth[v]){
            swap(u, v);
        }

        v = get_kth_ancestor(v, depth[v]-depth[u]);
        if(u == v){
            return u;
        }
    }

    for(ll i=LOG-1; i>=0; i--){
        ll a = up[u][i];
        ll b = up[v][i];

        if(a == b){
            continue;
        }
        
        u = up[u][i];
        v = up[v][i];
    }

    return up[u][0];
}

void solve(){
    ll n, q;
    cin >> n >> q;

    adjls.assign(n+1, vector<ll>());
    for(ll i=0; i<n-1; i++){
        ll u, v;
        cin >> u >> v;

        adjls[u].push_back(v);
        adjls[v].push_back(u);
    }

    up.assign(n+1, vector<ll> (LOG));
    depth.assign(n+1, 0);

    dfs1(1, 0);

    for(ll i=0; i<q; i++){
        ll u, v;
        cin >> u >> v;

        cout << get_LCA(u, v) << " ";
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