// Very Large Fib Modulo

// Computes F(n) mod 10^18 for extremely large n represented as a binary string.
// Exact computation of F(n) is infeasible for such enormous n (e.g., n = 2^(10^6)),
// so storing the result modulo 10^18 preserves the last 18 decimal digits while remaining computationally practical.

// L = length of binary string

#include <bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

#define ll long long
#define endl '\n'

#define i128 __int128

const ll MOD = 1e18; // Store the last 18 decimal digits of Fibonacci numbers
const ll N = 1e6;

vector<ll> ele00(N+1), ele10(N+1);

vector<vector<ll>> multiply(const vector<vector<ll>>& a, const vector<vector<ll>>& b)
{
    ll r1 = a.size(), r2 = b.size(), c2 = b[0].size();
    vector<vector<ll>> c(r1, vector<ll>(c2));
    
    for(ll i=0;i<r1;i++)
    {
        for(ll k=0;k<r2;k++)
        {
            for(ll j=0;j<c2;j++)
            {
                c[i][j] = (c[i][j] + (i128) a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    
    return c;
}
// TC: O(1) (2×2 matrix)
// SC: O(1)

void precompute()
{
    vector<vector<ll>> trans = {{1,1},{1,0}};
    
    ele00[0] = 1;
    ele10[0] = 1;
    
    for(ll i=1;i<=N;i++)
    {
        trans = multiply(trans, trans);
        
        ele00[i] = trans[0][0];
        ele10[i] = trans[1][0];
    }
    // Retrieve T^(2^i)
}
// TC: O(N)
// SC: O(N)

ll fib(const string &str)
{
    ll n = str.size();
    
    vector<vector<ll>> res(2, vector<ll>(2));
    
    for(ll i=0;i<2;i++)
    {
        res[i][i] = 1;
    }
    
    ll bitPos, ele11;
    vector<vector<ll>> mat(2, vector<ll>(2));
    
    for(ll i=0;i<n;i++)
    {
        if(str[i] == '1')
        {
           bitPos = n - 1 - i;
           ele11 = (ele00[bitPos] - ele10[bitPos] + MOD) % MOD;
           
           mat[0][0] = ele00[bitPos];
           mat[0][1] = ele10[bitPos];
           mat[1][0] = ele10[bitPos];
           mat[1][1] = ele11;
           
           res = multiply(res, mat);
        }
    }
    
    return res[1][0];
}
// TC: O(L)
// SC: O(1) auxiliary (excluding the input string)

void solve()
{ 
    // Input in binary string as such a large number can't be taken as normal input
    string str;
    cin >> str;
    
    cout << fib(str) ;
}
// TC: O(L)
// SC: O(1)

int main()
{
    fastio();
    precompute();
    
    solve();
}
// TC: O(N + L)
// SC: O(N)
