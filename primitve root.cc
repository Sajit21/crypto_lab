//finds the primitive root of any number

#include<bits/stdc++.h>
using namespace std;
bool isprimenumber(int n){
if(n<=1)return false;
if(n<=3)return true;
if(n%2==0 || n%3==0)return false;
for(int i=5;i*i<=n;i=i+6)
    if(n%i==0 || n%(i+2)==0)
        return false;
    return true;
}
int power(int x,unsigned int y,int p){
int res=1;
x=x%p;
while(y>0){
    if(y&1)
        res=(res*x)%p;
    y=y>>1;
    x=(x*x)%p;
}
return res;
}
void GeneratePrimes(unordered_set<int>&s,int n){
while(n%2==0){
    s.insert(2);
    n=n/2;

}
for(int i=3;i<=sqrt(n);i=i+2){
    while(n%i==0){
        s.insert(i);
        n=n/i;
    }
}
if(n>2)
    s.insert(n);
}
int findprimitiveroot(int n){
unordered_set<int>s;
if(isprimenumber(n)==false)
    return -1;
    int ETF=n-1;
    GeneratePrimes(s,ETF);
    for(int r=2;r<=ETF;r++){
        bool flag=false;
        for(auto it=s.begin();it!=s.end();it++){
        if(power(r,ETF/(*it),n)==1){
            flag=true;
            break;
        }
    }
    if(flag==false)
        return r;

}
return -1;
}
int main(){
int n;
cout<<"enter a number to find primitive root:";
cin>>n;
cout<<"smallest primitive root of "<<n<<"is"<<findprimitiveroot(n);
}
