//他會修改s(中間加@)和z，請注意
void z_value_pal(string &s,int len,vll &z){
    rep(i,0,len+1)s+=' ';
  len=(len<<1)+1;
  z.assign(len,0);
  for(int i=len-1;i>=0;i--)
    s[i]=i&1?s[i>>1]:'@';
  z[0]=1;
  for(int i=1,l=0,r=0;i<len;i++){
    z[i]=i<r?min(z[l+l-i],(ll)r-i):1;
    while(i-z[i]>=0&&i+z[i]<len&&s[i-z[i]]==s[i+z[i]])++z[i];
    if(i+z[i]>r) l=i,r=i+z[i];
} }