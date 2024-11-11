#include <bits/stdc++.h>
using namespace std;
int comp=0;
int partition(vector<int>&arr, int left, int right){
    int pivot = left + rand() % (right - left + 1);
    swap(arr[pivot], arr[right]);

    pivot=arr[right];
    int i=left;
    for(int j=left; j<right; j++){
        comp++;
        if(arr[j]<=pivot){
            swap(arr[i],arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

void randQS(vector<int>&arr, int left, int right){
    if(left<right){
        int pivot_ind=partition(arr, left, right);
        randQS(arr, left, pivot_ind-1);
        randQS(arr, pivot_ind+1, right);
    }
    
}

int main(){
    vector<int>v={3,1,8,5,2,0,7,4};
    randQS(v,0,7);
    for(int i=0; i<8; i++){
        cout<<v[i]<<" ";
    }
    cout<<endl<<"Total Comparisons:"<<comp<<endl;
}