#include <bits/stdc++.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;
int main()
{
    set<pair<string,string>>s;
    s.insert({"anasmurtaza33@gmail.com","asdfg123"});
    s.insert({"xyz@gmail.com","12345"});
    cout<<"Email id: ";
    string emailid; cin>>emailid;
    cout<<"Password :";
    string pass; cin>>pass;
    pair<string ,string>p={emailid, pass};
    if(s.find(p)!=s.end())
    {
    cout<<"-------------------------------------------"<<endl;    
    cout<<"ACCESS GRANTED"<<endl;
    cout<<"-------------------------------------------"<<endl;
    //sleep(3);
    cout<<"Here is your saved items link--->"<<endl;
    cout<<"https://drive.google.com/xghegdhdhd"<<endl;
    }
    else
    cout<<"ACCESS DENIED"<<endl;
    char c;
    cin>>c;

    return 0;
}
