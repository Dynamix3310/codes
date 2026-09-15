#include<bits/stdc++.h>
using namespace std;

int inv[3000005]={0,1};

int main(){
    ll n,p;
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>p;
    inv[1] = 1;
    for(int i = 1; i <=n; ++ i){
        if(i==1){
            cout<<'1'<<endl;
            continue;
        }
        inv[i] = (p - p / i) * inv[p % i] % p;
        printf("%d\n",inv[i]);
    }
        

}
