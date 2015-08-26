#include <iostream>
#include <map>

using namespace std;

map<string,string>account;

int main(){
    int n;
    cin >> n;
    while(n--){
        string cmd,id,psw;
        cin >> cmd >> id >> psw;
        if(cmd == "R"){
            if(account.find(id)!=account.end())
                cout << "ERROR: Account Number Already Exists"<<endl;
            else{
                account[id] = psw;
                cout << "Register Successful" << endl;
            }
        }
        else if(cmd == "L"){
            if(account.find(id)==account.end())
                cout << "ERROR: Account Not Exist" << endl;
            else if(account[id]!=psw)
                cout << "ERROR: Wrong Password" << endl;
            else cout << "Log in Successful" << endl;
        }
    }
    return 0;
}