#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
const int MOD = 1000000007;
const int MAXN = 200005;

// Ordered Set (PBDS)
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
/* ORDERED SET (PBDS)
    find_by_order(k) -> element at index k
    order_of_key(x)  -> count of elements < x
    insert(x), erase(x)
*/

ll fact[MAXN], invFact[MAXN];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void precomputefactorials() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
    invFact[MAXN - 1] = modInverse(fact[MAXN - 1]);
    for (int i = MAXN - 2; i >= 1; i--) {
        invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
    }
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    long long num = fact[n];
    long long den = (invFact[r] * invFact[n - r]) % MOD;
    return (num * den) % MOD;
}

vector<ll> dp;
vector<ll> value;
vector<vector<ll>> adjls;
ll ans = 0;

void dfs(ll node, ll parent){
    dp[node] = value[node];

    for(auto child: adjls[node]){
        if(child == parent){
            continue;
        }

        dfs(child, node);

        dp[node] += dp[child]; 
    }
}

void solve(){
    ll n;
    cin >> n;

    value.resize(n+1);
    for(ll i=1; i<=n; i++){
        cin >> value[i];
    }

    adjls.resize(n+1);
    for(ll i=0; i<n-1; i++){
        ll a, b;
        cin >> a >> b;

        adjls[a].push_back(b);
        adjls[b].push_back(a);
    }

    dp.resize(n+1);
    dfs(1, 0);

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