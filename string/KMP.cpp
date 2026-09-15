#include <bits/stdc++.h>
using namespace std;

struct KMP{
    long long int n;
    string S;
    vector<int> KMP;
    void init(int N,string S2){
        S=S2;
        n=N;
        KMP.assign(n+1,0);
        for(int i=1;i<n;i++){
            int j=KMP[i-1];
            while(j>0 && S[i]!=S[j])j=KMP[j-1];
            KMP[i]=j+(S[i]==S[j]);
        }
    }
};
int n,w;
long long int a[200010];
long long int A[200010];
long long int W[200010];
long long int kmp[200010];
int main() {
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n>>w;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n-1;i++){
        A[i]=a[i+1]-a[i];
    }
    A[n]=-1e18;
    for(int i=0;i<w;i++){
        cin>>a[i];
    }
    for(int i=0;i<w-1;i++){
        W[i]=a[i+1]-a[i];
    }
    W[w]=-1e18;
    for(int i=1;i<w-1;i++){
        int j=kmp[i-1];
        while(j>0 && W[i]!=W[j]){
            j=kmp[j-1];
        }
        kmp[i]=j+(W[i]==W[j]);
    }
    long long int answer=0;
    for(int i=0,j=0;i<n-1;i++){
        while(j>0 && A[i]!=W[j]){
            j=kmp[j-1];
        }
        j+=(A[i]==W[j]);
        if(j==w-1){
            answer++;
            j=kmp[j-1];
        }
    }
    if(w==1){
        cout<<n;
        return 0;
    }
    cout<<answer;
    return 0;
}
