    #include<bits/stdc++.h>
    using namespace std;
    int main(){
      int n;cin>>n;
      string arr[1010];
      arr[0] = "A";
      for(int i=1; i<=n; i++){
        string str="";cin>>str;
        int j;
        for(j=i-1; j>=0; j--){
          if(arr[j] >= str){
            arr[j+1] = arr[j];
          }
          else break;
        }
        cout<<j<<endl;
        arr[j+1] = str;
      }
      return 0;
    }
