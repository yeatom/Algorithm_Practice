#include<bits/stdc++.h>
#include<iostream>

using namespace std;
//Karatsuba's algorithm.

vector<int> naive_approach(string a,string b){
    vector<int>product(a.size()+b.size(),0);
    int current_digit=a.size();
    for(int i=a.size()-1;i>=0;i--){
        for(int j=b.size()-1;j>=0;j--){
            int temp=(a[i]-'0')*(b[j]-'0');
            product.at(current_digit+j)+=temp;
        }
        current_digit--;
    }
    for(int i=product.size()-1;i>0;i--){
        if(product.at(i)>9){
            product.at(i-1)+=product.at(i)/10;
            product.at(i)%=10;
        }
    }
    while(!*product.begin())product.erase(product.begin());
    return product;
}

int main(){
    string a,b;cin>>a>>b;
    vector<int>ans=naive_approach(a, b);for(auto it:ans)cout<<it;
}
