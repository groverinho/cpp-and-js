#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

#define pii pair<int, int>

#define MAX 46656
#define LMT 216
#define LEN 4830
#define RNG 100032

unsigned base[MAX / 64], segment[RNG / 64], primes[LEN];

#define sq(x) ((x)*(x))
#define mset(x,v) memset(x,v,sizeof(x))
#define chkC(x,n) (x[n>>6]&(1<<((n>>1)&31)))
#define setC(x,n) (x[n>>6]|=(1<<((n>>1)&31)))

// http://zobayer.blogspot.com/2009/09/segmented-sieve.html
void sieve()
{
    unsigned i, j, k;
    for (i = 3; i<LMT; i += 2)
        if (!chkC(base, i))
            for (j = i*i, k = i << 1; j<MAX; j += k)
                setC(base, j);
    primes[0] = 2;
    for (i = 3, j = 1; i<MAX; i += 2)
        if (!chkC(base, i))
            primes[j++] = i;
}


//http://www.geeksforgeeks.org/print-all-prime-factors-of-a-given-number/
vector <pii> factors;
void primeFactors(int num)
{
    int expo = 0;
    for (int i = 0; primes[i] <= sqrt(num); i++)
    {
        expo = 0;
        int prime = primes[i];
        while (num % prime == 0){
            expo++;
            num = num / prime;
        }
        if (expo>0)
            factors.push_back(make_pair(prime, expo));
    }

    if ( num >= 2)
        factors.push_back(make_pair(num, 1));

}

vector <int> divisors;
void setDivisors(int n, int i) {
    int j, x, k;
    for (j = i; j<factors.size(); j++) {
        x = factors[j].first * n;
        for (k = 0; k<factors[j].second; k++) {
            divisors.push_back(x);
            setDivisors(x, j + 1);
            x *= factors[j].first;
        }
    }
}

int main() {

    sieve();
    int a,b,c,d,n;
    while (cin>>a>>b>>c>>d) {
        n=-1;
        primeFactors(c);
        setDivisors(1, 0);
        divisors.push_back(1);
        sort(divisors.begin(), divisors.end());
        for (int j = 0; j < divisors.size(); j++) {
            if(divisors[j]%a==0&&divisors[j]%b!=0&&d%divisors[j])
            {
                n=divisors[j];
                break;
            }
        }
        cout << n<<endl;
        divisors.clear();
        factors.clear();
    }
    return 0;
}
