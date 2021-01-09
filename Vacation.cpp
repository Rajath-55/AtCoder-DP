/* Author : Rajath V 
   Challenge : Codechef
*/

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;
#define fastio() ios_base::sync_with_stdio(false), cin.tie(NULL)
typedef long long ll;
typedef long int l;
#define endl '\n';
ll mod = 1000000007;
const long long mxN = 1e18;
const ll INF = 10000000000000000LL;

//Template functions

template <typename T>
bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
    return (v1.size() == v2.size() &&
            std::equal(v1.begin(), v1.end(), v2.begin()));
}

bool prime_check(ll n)
{
    if (n < 2)
        return false;
    for (ll i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}

vector<ll> sieve(ll n)
{
    vector<ll> primes, is_prime(n + 1, 1);
    for (ll i = 2; i * i <= n; i++)
        if (is_prime[i])
            for (ll j = i + i; j <= n; j += i)
                is_prime[j] = 0;
    for (ll i = 2; i <= n; i++)
        if (is_prime[i])
            primes.push_back(i);
    return primes;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);

    return elems;
}

ll power(ll x, unsigned long long y, ll p)
{
    ll res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

vector<ll> inp(ll n)
{
    vector<ll> a;
    for (int i = 0; i < n; ++i)
    {
        ll inp;
        cin >> inp;
        a.push_back(inp);
    }
    return a;
}

void outp(vector<ll> a)
{
    for (auto x : a)
        cout << x << " ";
    cout << endl;
}

ll sum(vector<ll> a)
{
    ll s = 0;
    for (auto x : a)
        s += x;
    return s;
}

inline ll ceiling(ll n, ll x)
{
    return (n % x ? n / x + 1 : n / x);
}

vector<ll> preFix(vector<ll> a)
{
    vector<ll> preSum(a.size(), 0);
    preSum[0] = a[0];
    for (ll i = 1; i < a.size(); ++i)
    {
        preSum[i] = preSum[i - 1] + a[i];
    }
    return preSum;
}

/****** Template of some basic operations *****/
template <typename T, typename U>
inline void amin(T &x, U y)
{
    if (y < x)
        x = y;
}
template <typename T, typename U>
inline void amax(T &x, U y)
{
    if (x < y)
        x = y;
}
/**********************************************/

/****** Template of Fast I/O Methods *********/
template <typename T>
inline void write(T x)
{
    int i = 20;
    char buf[21];
    // buf[10] = 0;
    buf[20] = '\n';

    do
    {
        buf[--i] = x % 10 + '0';
        x /= 10;
    } while (x);
    do
    {
        putchar(buf[i]);
    } while (buf[i++] != '\n');
}

template <typename T>
inline T readInt()
{
    T n = 0, s = 1;
    char p = getchar();
    if (p == '-')
        s = -1;
    while ((p < '0' || p > '9') && p != EOF && p != '-')
        p = getchar();
    if (p == '-')
        s = -1, p = getchar();
    while (p >= '0' && p <= '9')
    {
        n = (n << 3) + (n << 1) + (p - '0');
        p = getchar();
    }

    return n * s;
}

ll minLenSubArray(vector<ll> a, ll k)
{
    ll n = a.size();
    unordered_map<ll, ll> counts;
    counts[a[0]] = 0;
    for (ll i = 1; i < n; ++i)
    {
        a[i] = a[i] + a[i - 1];
        counts[a[i]] = i;
    }
    ll len = INT_MAX;
    for (ll i = 0; i < n; ++i)
    {
        if (a[i] < k)
            continue;
        else
        {
            ll x = a[i] - k;

            if (x == 0)
            {
                len = min(len, i);
            }
            if (counts.find(x) == counts.end())
            {
                continue;
            }
            else
            {
                len = min(len, i - counts[x]);
            }
        }
        cout << endl;
    }
    return len;
}
/************************************/

/******* Debugging Class Template *******/
#define DEBUG

#ifdef DEBUG

#define debug(args...) (Debugger()), args

class Debugger
{
public:
    Debugger(const std::string &_separator = " - ") : first(true), separator(_separator) {}

    template <typename ObjectType>
    Debugger &operator,(const ObjectType &v)
    {
        if (!first)
        std:
            cerr << separator;
        std::cerr << v;
        first = false;
        return *this;
    }
    ~Debugger()
    {
    std:
        cerr << endl;
    }

private:
    bool first;
    std::string separator;
};

#else
#define debug(args...) // Just strip off all debug tokens
#endif

//Solve function for t test cases

void solve()
{

    ll n;
    cin >> n;

    /*
   Dp[i][0]  = the amount of happiness gained by doing activity a on the ith day'
   dp[i][1] = by doing the activity b
   dp[i][2] = by doing the activity c
   so max of the last day's dp is the answer basically
   */
    ll dp[n][3];
    for (ll i = 0; i < n; ++i)
    {
        for (ll j = 0; j < 3; ++j)
        {
            dp[i][j] = 0;
        }
    }

    ll a[n], b[n], c[n];
    for (ll i = 0; i < n; ++i)
    {
        cin >> a[i] >> b[i] >> c[i];
    }
    dp[0][0] = a[0];
    dp[0][1] = b[0];
    dp[0][2] = c[0];

    for (ll i = 1; i < n; ++i)
    {
        dp[i][0] = max(dp[i - 1][1], dp[i - 1][2]) + a[i];
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + b[i];
        dp[i][2] = max(dp[i - 1][1], dp[i - 1][0]) + c[i];
    }

    ll h = dp[n - 1][0];

    ll i = dp[n - 1][1];
    ll j = dp[n - 1][2];
    //    for (ll i = 0; i < n; ++i)
    //    {
    //     //    cout << "dang\n";
    //        cout << dp[i][0] << " " << dp[i][1] << " " << dp[i][2] << endl;
    //    }
    cout << (ll)max({h, i, j}) << endl;
}

int main()
{
    fastio();
    // int t;
    // cin >> t;

    // while (t--)
    // {
    //     solve();
    // }
    solve();

    return 0;
}
