#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
  
int n;
struct Point{
    int x, y;
    bool operator < (const Point &b) const{
        if (x != b.x) return x < b.x;
        return y < b.y;
    }
};
vector <Point> v;
set <Point> st;
  
bool cmp(Point x, Point y){
    if (x.y != y.y) return x.y < y.y;
    return x.x < y.x;
}
long long sqr(long long x){
    return x*x;
}
long long dis(Point a, Point b){
    return sqr(a.x-b.x) + sqr(a.y-b.y);
}
  
int main() {
    cin >> n;
    for (int i = 0, x, y; i < n; i++){
        cin >> x >> y;
        v.push_back({x, y});
    }
    sort(v.begin(), v.end(), cmp);
    int p = 0;
    st.insert(v[0]);
    st.insert(v[1]);
    long long d = dis(v[0], v[1]);
    for (int i = 2; i < n; i++){
        while (p < i && sqr(v[i].y-v[p].y) > d){
            st.erase(v[p]);
            p++;
        }
        set<Point>::iterator it = st.lower_bound(v[i]);
        set<Point>::iterator tmp = it;
        for (int j = 0; j < 5; j++, tmp++){
            if (tmp == st.end()) break;
            d = min(d, dis(v[i], *tmp));
        }
        tmp = it;
        for (int j = 0; j < 5; j++){
            if (tmp == st.begin()) break;
            tmp--;
            d = min(d, dis(v[i], *tmp));
        }
        st.insert(v[i]);
    }
    cout << d << "\n";
}