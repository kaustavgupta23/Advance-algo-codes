// . Write a program to find the ith smallest element of an array using Randomized Select.

#include <bits/stdc++.h>
#include <iostream>
using namespace std;
int partition(vector<int>&arr, int left, int right){
    int pivot = left + rand() % (right - left + 1);
    swap(arr[pivot], arr[right]);
    pivot=arr[right];
    int i=left;
    for(int j=left; j<right; j++){
        if(arr[j]<=pivot){
            swap(arr[i],arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

int randQS(vector<int>&arr, int left, int right, int i){
    if(left==right){ // when array has only 1 element
        return arr[left];
    }
    int pivot_ind=partition(arr, left, right);
    int len=pivot_ind-left+1; 
    
    if(i==len){
        return arr[pivot_ind]; // single element
    }
    else if(i<len){
        return randQS(arr,left,pivot_ind-1, i);
    }
    else{
        return randQS(arr,pivot_ind+1, right, i-len);
    }
}


int main() {
    vector<int> arr(100);
    int n;
    cout << "Enter array size: ";
    cin >> n;

    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Find the ith smallest element
    cout << "Enter value of i for ith smallest element: ";
    int i;
    cin >> i;
    int ithSmallest = randQS(arr, 0, n - 1, i);
    cout << "The " << i << "th smallest element is: " << ithSmallest << endl;

    //Find the kth largest element
    cout << "Enter value of k for kth largest element: ";
    int k;
    cin >> k;
    int kthLargest = randQS(arr, 0, n - 1, n - k + 1);
    cout << "The " << k << "th largest element is: " << kthLargest << endl;

    return 0;
}
