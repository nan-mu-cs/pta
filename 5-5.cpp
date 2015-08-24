#include <iostream>
#include <stack>
#include <vector>
#define SIZE 31

using namespace std;
struct tree{
    int left,right;
} node[SIZE];
int status[SIZE];
stack<int>st;
vector<int> result;
int n;
void postorder(int s){
    if(node[s].left)
        postorder(node[s].left);
    if(node[s].right)
        postorder(node[s].right);
    result.push_back(s);
}
int main(){
    cin >> n;
    int s,parentl,parentr = -1;
    string cmd;
    for(int i = 1;i<=2*n;i++){
        cin >> cmd;
        if(cmd == "Push"){
            int index;
            cin >> index;
            st.push(index);
            status[index] = 1;
            if(i == 1)
            {
                s = parentl = index;
                continue;
            }
            if(status[parentl] == 1)
                node[parentl].left = index;
            parentl = index;
            if(parentr!=-1&&node[parentr].right == 0)
                node[parentr].right = index;
        }
        else {
            int index = st.top();
            st.pop();
            status[index] = 2;
            //if(parentr!=-1)
              //  node[parentr].right = index;
            parentr = index;
        }
    }
    postorder(s);
    for(int i = 0;i<result.size();i++)
        if(i == result.size()-1)
            cout << result[i] << endl;
        else cout << result[i] << ' ';
    return 0;
}