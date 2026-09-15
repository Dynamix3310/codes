//可以找出線性組合的一組整數解 ax+by=c
//擴展歐積李德模板
ll exgcd(ll a,ll b,ll &x1, ll &y1){
    if(!b){
        x1=1;
        y1=0;
        return a;
    }
    ans=exgcd(b,a%b,x1,y1);
    ll t=x1;
    x1=y1;
    y1=t-a/b*y1;
    return ans;
}
int main(){
	ll x,y,c;
    ll g=exgcd(3,2,x,y);
    cout<<g<<endl;
	cout<<x<<" "<<y<<endl; 
    if(c%g!=0){
        cout<<"c無解";
    }else{
        ll final_x,final_y;
        final_x = x*(c/g);
        final_y = y*(c/g);
        cout<<final_x<<" "<<final_y;
    }
    //他會找出3x+2y=c的一組解，然後x跟 y 多少
}
