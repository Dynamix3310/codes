#include<bits/stdc++.h>
using namespace std;

bool a[100000010]={0};
vector<int >b;//質數陣列
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    long long int q,n;
    cin>>q>>n;//q是範圍
    for(int i=2; i<=q; i++){
	  if(a[i]==false)
		b.push_back(i);
	  for(int j=0; j<b.size()&&i*b[j]<=q; j++){
		a[i*b[j]] = true ;
	      if(i%b[j]==0)
		      break;
	    } 
	}
    
    for(auto e:b){
        cout<<e<<endl;
    }
    return 0;
}

