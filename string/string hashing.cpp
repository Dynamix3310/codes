struct hash_string{
    vector<long long int> power;
    vector<long long int> table;
    long long int Prime_A;
    long long int Prime_B;
    string s;
    void init(int length,long long int primea,long long int primeb,string tmp2){
        power.resize(length+1);
        table.resize(length+1);
        Prime_A=primea;
        Prime_B=primeb;
        s=tmp2;
        power[0]=1;
        for(int i=1;i<=length;i++){
            power[i]=(power[i-1]*Prime_A)%Prime_B;
        }
        table[0]=0;
        for(int i=0;i<s.size();i++){
            table[i+1]=((table[i]*Prime_A)%Prime_B+s[i])%Prime_B;
        }
    }
    long long int search(long long int a,long long int b){
        if(table[b]>=(table[a-1]*power[b-a+1])%Prime_B){
            return table[b]-(table[a-1]*power[b-a+1])%Prime_B;
        }else{
            return (table[b]+Prime_B-(table[a-1]*power[b-a+1])%Prime_B)%Prime_B;
        }
    }
};
