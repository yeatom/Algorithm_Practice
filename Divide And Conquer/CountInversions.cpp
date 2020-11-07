#include<bits/stdc++.h>
#include<iostream>

using namespace std;

void read_array(vector<int>&arr,string dir){
    ifstream fin;
    fin.open(dir);
    int a;
    while(fin>>a)
        arr.push_back(a);
    fin.close();
}

int naive_approach(vector<int>arr){
    int count_inversions=0;
    for(int i=0;i<arr.size()-1;i++)
        for(int j=i+1;j<arr.size();j++)
            if(arr[i]>arr[j])count_inversions++;
    return count_inversions;
}

long long AVL_tree_approach_2(vector<int>arr){
    long long count_inversions=0;
    set<int> Myset;
    set<int>::iterator Myiterator;
    Myset.insert(arr.at(0));
    for (int i=1; i<arr.size(); i++) {
        Myset.insert(arr.at(i));
        Myiterator=Myset.upper_bound(arr.at(i));
        count_inversions+=distance(Myiterator, Myset.end());
    }
    return count_inversions;
}

int main(){
    vector<int>arr;
    read_array(arr, "/Users/chosen1/Desktop/IntegerArray.txt");
    assert(naive_approach({6,4,3,1})==AVL_tree_approach_2({6,4,3,1}));
    cout<<AVL_tree_approach_2(arr);
}
