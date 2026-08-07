// Precomputation with the help of Matrix Exponentiation without three extra vector
// ele[i] stores T^(i-1)

// Notice that the res[0][0] is actually fib[i], we never need four elements but only the first number to represent fib[i] as we multiply with F1, we can see the result clearly

// fib[i] = res[0][0] * 1 + res[0][1] * 0 = res[0][0]

#include <bits/stdc++.h>
using namespace std;

#define fastio() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int N = 1e6;
const int MOD = 1e9 + 7;

vector<int> fib(N+1);

vector<vector<int>> multiply(const vector<vector<int>> &a, const vector<vector<int>> &b)
{
    int r1 = a.size(), r2 = b.size(), c2 = b[0].size();
    
    vector<vector<int>> c(r1,vector<int>(c2));
    
    for(int i=0;i<r1;i++)
    {
        for(int k=0;k<r2;k++)
        {
            for(int j=0;j<c2;j++)
            {
                c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j] % MOD) % MOD;
            }
        }
    }
    
    return c;
}
// TC: O(1) // O(R1 × R2 × C2) for general matrices
// SC: O(1)     // O(R1 × C2) for general matrices

void precompute()
{
    vector<vector<int>> trans = {{1,1},{1,0}}, res = trans;
    fib[1] = fib[2] = 1;
    
    for(int i=3;i<=N;i++)
    {
        res = multiply(res, trans);
        
        fib[i] = res[0][0];
    }
}
// TC: O(N)
// SC: O(N)

void solve()
{
    int n;
    cin >> n;
    
    cout << fib[n];
}
// TC: O(1)
// SC: O(1)

int main()
{
    fastio();
    precompute();
    
    solve();
}
// TC: O(N)
// SC: O(N)
