#include<bits/stdc++.h>
#include<iostream>

using namespace std;
//Karatsuba's algorithm.🙋🏼‍♂️

vector<int> naive_approach(string a,string b){
    vector<int>product(a.size()+b.size(),0);
    for(int i=a.size()-1;i>=0;i--){
        for(int j=b.size()-1;j>=0;j--){
            int temp=(a[i]-'0')*(b[j]-'0');
            product.at(i+j+1)+=temp;
        }
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
//Time complexity is O(MN),where M and N represent length of two numbers.

vector<int>Add(vector<int> a,vector<int> b){
    if(a.size()<b.size())
        swap(a, b);
    a.insert(a.begin(), 0);
    while(b.size()!=a.size())
        b.insert(b.begin(), 0);
    for (int i=a.size()-1; i>0; i--) {
        a.at(i)+=b.at(i);
        a.at(i-1)+=a.at(i)/10;
        a.at(i)%=10;
    }
    while(*a.begin()==0&&a.size()>1)
        a.erase(a.begin());
    return a;
}

vector<int>Subtract(vector<int> a,vector<int> b){
    //e2 is always positive, so return value is positive.
    int size=max(a.size(), b.size());
    while (a.size()<size)
        a.insert(a.begin(), 0);
    while (b.size()<size)
        b.insert(b.begin(), 0);
    for(int i=a.size()-1;i>=0;i--){
        a.at(i)-=b.at(i);
        if(a.at(i)<0){
            a.at(i)+=10;
            int j=i-1;
            while (j>=0) {
                if(a.at(j)!=0){a.at(j)-=1;break;}
                else {a.at(j)=9;j--;}
            }
        }
    }
    while(*a.begin()==0&&a.size()>1)
        a.erase(a.begin());
    return a;
}

vector<int>karatsuba_approach(vector<int> a,vector<int> b){

    if(a.size()==b.size()&&a.size()==1){
        vector<int>res;
        int m=a.at(0)*b.at(0);
        res.push_back(m/10);
        res.push_back(m%10);
        while(*res.begin()==0&&res.size()>1)
            res.erase(res.begin());
        return res;
    }
    
    if(a.size()<b.size())
        swap(a, b);
    if(a.size()%2)
        a.insert(a.begin(), 0);
    while(b.size()!=a.size())
        b.insert(b.begin(), 0);

    vector<int>a_first_half(a.begin(),
                            a.begin()+a.size()/2);
    vector<int>b_first_half(b.begin(),
                            b.begin()+b.size()/2);
    
    vector<int>a_second_half(a.begin()+a.size()/2,
                             a.end());
    vector<int>b_second_half(b.begin()+b.size()/2,
                             b.end());
    
    vector<int>a1=karatsuba_approach(a_first_half,
                                     b_first_half);
    vector<int>d1=karatsuba_approach(a_second_half,
                                     b_second_half);
    vector<int>e1=Subtract(karatsuba_approach(Add(a_first_half,
                                                  a_second_half),
                                              Add(b_first_half,
                                                  b_second_half)),
                           Add(a1,d1));
    
    for(int i=0;i<a.size();i++)
        a1.push_back(0);
    for(int i=0;i<a.size()/2;i++)
        e1.push_back(0);
    vector<int>res=Add(Add(a1, e1), d1);
    while(*res.begin()==0&&res.size()>1)
        res.erase(res.begin());
    return res;
}
//Time complexity is O(nlog2(3))=O(n**1.584),where n represent vector.size().

vector<int>str_to_vector(string s){
    vector<int>arr;
    for(auto ch:s)
        arr.push_back(ch-'0');
    return arr;
}

int main(){
    string a,b;cin>>a>>b;
    vector<int>ans_naive=naive_approach(a, b);
    for(auto it:ans_naive)cout<<it;;cout<<endl;
    vector<int>ans_karatsuba=karatsuba_approach(str_to_vector(a), str_to_vector(b));
    for(auto it:ans_karatsuba)cout<<it;;cout<<endl;
}
