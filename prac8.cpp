#include<bits/stdc++.h>
using namespace std;

void lps(string &pattern, vector<int>&lpsarr){
    int len=0;
    lpsarr[0]=0;
    int i=1; 

    while(i<pattern.size()){
        if(pattern[i]==pattern[len]){
            len++;
            lpsarr[i]=len;
            i++;
        }
        else{
            if(len!=0){
                len=lpsarr[len-1];
            }
            else{
                lpsarr[i]=0;
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