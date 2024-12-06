// Write a program to sort the elements of an array using Randomized Quick Sort (the
// program should report the number of comparisons)

#include <bits/stdc++.h>
using namespace std;
int comparision = 0;
int partition(vector<int>& arr, int left, int right) {
    int pivot = left + rand() % (right - left + 1); // Random pivot index
    swap(arr[pivot], arr[right]); // Swap the chosen pivot with the last element on the right
    pivot = arr[right]; // Pivot value is now at the end
    int i = left; // Index to place elements less than or equal to the pivot
    for (int j = left; j < right; j++) { // Iterate over the subarray
        comparision++; // Increment the comparison count
        if (arr[j] <= pivot) { // Compare current element with pivot
            swap(arr[i], arr[j]); // Swap if current element is <= pivot
            i++; // Increment the index for smaller elements
        }
    }
    swap(arr[i], arr[right]); // Place the pivot in its correct position
    return i; // Return the index of the pivot
}

void randQS(vector<int>& arr, int left, int right) {
    if (left < right) { // Base condition for recursion
        int pivot_ind = partition(arr, left, right); // Partition the array
        randQS(arr, left, pivot_ind - 1); // Recursively sort the left subarray
        randQS(arr, pivot_ind + 1, right); // Recursively sort the right subarray
    }
}


int main(){
    vector<int>v={3,1,8,5,2,0,7,4};
    randQS(v,0,7);
    for(int i=0; i<8; i++){
        cout<<v[i]<<" ";
    }
    cout<<endl<<"Total Comparisons:"<<comparision<<endl;
}