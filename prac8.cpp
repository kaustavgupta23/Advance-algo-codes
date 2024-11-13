// Write a program to search a pattern in a given text using the KMP algorithm

#include<bits/stdc++.h>
using namespace std;

// lps => longest prefix suffix
void lps(string &pattern, vector<int>&lpsarr){
    int len=0; // Length of the previous longest prefix suffix
    lpsarr[0]=0; // The first character has no proper prefix or suffix
    int i=1; // Start from the second character of the pattern

    // Compute the LPS array
    while(i<pattern.size()){
        if(pattern[i]==pattern[len]){
            len++; // The current characters match, increase the length of the prefix-suffix
            // KEEPS TRACK THE LENGTH OF LPS
            lpsarr[i]=len; // Store the length of the longest prefix-suffix at position i
            i++;
        }
        else{
            // Mismatch: shift the pattern using the LPS array
            if(len!=0){
                len=lpsarr[len-1]; // Shift the length to the previous longest prefix-suffix
            }
            else{
                lpsarr[i]=0; // No match found, so set the LPS value to 0
                i++;
            }
        }
    }
}


void kmpsearch(string& str, string& pattern){
    bool found=false;
    int m=str.size();
    int n=pattern.size();

    vector<int>lpsarr(n);
    lps(pattern, lpsarr);

    int i=0,j=0;
    while(i<m){
        if(pattern[j]==str[i]){
            j++,i++;
        }
        if(j==n){
            found=true;
            cout<<"Pattern found at index: "<<i-j<<endl;
            j=lpsarr[j-1];
        }
        else if(i<m && pattern[j]!=str[i]){
            if(j!=0){
                j=lpsarr[j-1];
            }
            else{
                i++;
            }
        }   
    }
    if(!found){
        cout<<"Pattern not found!";
    }
}
int main(){
    string text, pattern;
    cout<<"enter text:";
    cin>>text;
    cout<<"enter pattern:";
    cin>>pattern;

    kmpsearch(text, pattern);

}