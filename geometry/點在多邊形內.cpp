#include <bits/stdc++.h>
using namespace std;
const double EPS=1e-7;
struct point{
    long long int x,y;
    
    point operator * (int a){return{x*a,y*a};};
    point operator / (int a){return{x/a,y/a};};
    point operator + (point a){return{x+a.x,y+a.y};};
    point operator - (point a){return{x-a.x,y-a.y};};
 
    long long int operator * (point a){return x*a.x + y * a.y;}
    long long int operator ^ (point a){return x*a.y - y * a.x;}
 
    void print(){
        cerr<<x<<" "<<y<<"\n";
    }
};
double abs(point a){
    return sqrt(a.x*a.x + a.y*a.y);
}
//test for sign
int sign(long long int a){
    if(abs(a)<EPS)return 0;
    if(a>0)return 1;
    return -1;
}
//ab to ac
int ori(point a,point b,point c){
    return sign((b-a)^(c-a));
}
//test ab and ac are colinear
bool colinear(point a,point b,point c){
    if(sign(ori(a,b,c))==0)return 1;
    return 0;
}
//test if c between a and b
bool between(point a,point b,point c){
    if(!colinear(a,b,c))return 0;
    return sign((a-c)*(b-c))<=0;
}
bool intersection(point a,point b,point c,point d){
    //a.print();
    //b.print();
    //c.print();
    //d.print();
    int abc=ori(a,b,c);
    int abd=ori(a,b,d);
    int cda=ori(c,d,a);
    int cdb=ori(c,d,b);
    if(abc==0 && abd==0){
        return between(a,b,c) || between(a,b,d) || between(c,d,a) || between(c,d,b);
    }
    return abc*abd<=0 && cda*cdb<=0;
}
int n,m;
point poly[1010];
bool test(point b,point a){
    for(int i=0;i<n;i++){
        if(between(a,b,poly[i])){
            return 1;
        }
    }
    return 0;
}
 
void solve(point a){
    for(int i=0;i<n;i++){
        if(sign(abs(poly[i]-a))==0){
            cout<<"BOUNDARY\n";
            return;
        }
    }
    for(int i=0;i<n;i++){
        if(between(poly[i],poly[(i+1)%n],a)){
            cout<<"BOUNDARY\n";
            return;
        }
    }
    //a.print();
    //cerr<<"\n";
    point b=a+point{1,(long long int)2e9+(long long int)(5)};
    while(test(b,a)){
        b.y++;
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        if(intersection(poly[i],poly[(i+1)%n],a,b)){
            cnt++;
        }
    }
    //cerr<<cnt<<"\n\n";
    if(cnt%2==0){
        cout<<"OUTSIDE\n";
    }else{
        cout<<"INSIDE\n";
    }
    return;
}
int main() {
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    //cerr<<intersection(point{1,1},point{5,5},point{1,5},point{5,1})<<"\n";
    cin>>n>>m;
    for(int i=0;i<n;i++){
        cin>>poly[i].x>>poly[i].y;
    }
    while(m--){
        point tmp;
        cin>>tmp.x>>tmp.y;
        solve(tmp);
    }
    return 0;
}