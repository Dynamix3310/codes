#include <bits/stdc++.h>
using namespace std;
const double EPS = 1e-7;
struct point{
    double x,y;
    point operator * (int a){return {x*a,y*a};};
    point operator / (int a){return {x/a,y/a};};
    point operator + (point b){return {x+b.x,y+b.y};};
    point operator - (point b){return {x-b.x,y-b.y};};
 
    double operator * (point b){return x * b.x + y * b.y;}
    double operator ^ (point b){return x * b.y - y * b.x;}
};
 
double abs(point a){
    return sqrt(a.x*a.x + a.y*a.y);
}
int sign(double a){
    if(abs(a)<EPS)return 0;
    if(a>0)return 1;
    return -1;
}
int ori(point a,point b,point c){//外積
    return sign((b-a)^(c-a));
}
// test if a and b and c are colinear
bool colinear(point a,point b,point c){
    return (sign((b-a)^(c-a))==0);
}
// test if c between a and b
bool between(point a,point b,point c){
    if(!colinear(a,b,c))return 0;
    return (sign((a-c)*(b-c))<=0);
}
//test if segment ab and segment cd are intersect
bool intersect(point a,point b,point c,point d){
    int abc,abd,cda,cdb;
    abc=ori(a,b,c);//c點對ab線段外積
    abd=ori(a,b,d);//d點對ab線段外積
    cda=ori(c,d,a);//以此類推
    cdb=ori(c,d,b);
    if(abc==0 && abd==0){
        return ( between(a,b,c) || between(a,b,d) || between(c,d,a) || between(c,d,b) );
    }
    return abc*abd<=0 && cda*cdb<=0;
}
 
void solve(){
    point a[4];
    for(int i=0;i<4;i++){
        cin>>a[i].x>>a[i].y;
    }
    if(intersect(a[0],a[1],a[2],a[3])){
        cout<<"YES\n";
    }else{
        cout<<"NO\n";
    }
    return;
}
int main() {
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}