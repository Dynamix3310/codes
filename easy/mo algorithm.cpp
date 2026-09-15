#include <bits/stdc++.h>
using namespace std;
int n,q;
long long int BB=25;
long long int AA=317;
long long int a[100010];
long long int ans[100010];
unordered_set<int> ccnt[100010];
vector<tuple<int,int,int> > use;
unordered_set<int> num;
long long int cnt=0;

void ad(int x,int i){
    if(a[x]<i*BB || a[x]>=(i+1)*BB)return;
    if(num.count(a[x])==1){
        cnt++;
        num.erase(a[x]);
    }else{
        num.insert(a[x]);
    }
    return;
}
void pp(int x,int i){
    if(a[x]<i*BB || a[x]>=(i+1)*BB)return;
    if(num.count(a[x])==0){
        cnt--;
        num.insert(a[x]);
    }else{
        num.erase(a[x]);
    }
}

int main() {
    ios::sync_with_stdio(0),cin.tie(0);
    cin>>n>>q;
    long long int MMMax=0;
    sort(use.begin(),use.end(),[&](tuple<int,int,int> A,tuple<int,int,int> B){
        return (make_pair(get<0>(A)/AA,get<1>(A))<make_pair(get<0>(B)/AA,get<1>(B)));
    });
    for(int i=0;i<MMMax/BB+1;i++){
        int curL=1,curR=0;
        for(auto u:use){
            int l=get<0>(u),r=get<1>(u);
            int id=get<2>(u); 
            while(curL<l){
                pp(curL,i);
                curL++;
            }
            while(curR>r){
                pp(curR,i);
                curR--;
            }
            while(curR<r){
                curR++;
                ad(curR,i);
                // curR++;
            }
            
            while(curL>l){
                curL--;
                ad(curL,i);
                // curL--;
            }
            ans[id]+=cnt;
            for(auto u:num){
                if(ccnt[id].count(u)==1){
                    ans[id]++;
                    ccnt[id].erase(u);
                }else{
                    ccnt[id].insert(u);
                }
            }
        }
        for(int j=0;j<q;j++){
            ccnt[j].clear();
        }
        num.clear();
        cnt=0;
    }
    for(int i=0;i<q;i++){
        cout<<ans[i]<<'\n';
    }
    return 0;
}