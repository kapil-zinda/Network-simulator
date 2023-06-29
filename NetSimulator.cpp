#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
set<int>ssk; //for hub
vector<pair<int,int>>table; // CAM
map<int,int>devdetails; // to map device number to mac address
queue<int> tokenqueue; // for token passing

struct udpdata {
  int sourceport;
  int destport;
  int tlength;
  int checksum;
  string data;
};
class devices{
public:
	int mac;
	int epport;
	int wkport;
	string s;
	string ip;
	string subnet="255.255.255.0";
	devices(){
       mac=(rand()%888888888) + 111111111;
       s="NULL";
	}
	string decimalToBinary(int n)
   {
    string s = bitset<64> (n).to_string();
    const auto loc1 = s.find('1');
    if(loc1 != string::npos)
        return s.substr(loc1);
     
    return "0";
   }
   
string strToBinary(string s1)
{
    int n = s1.length();
    string sss="";//string having binary bits of data
    for (int i = 0; i <n; i++)
    {
        int val = int(s1[i]);
        string bin = "";
        while (val > 0)
        {
            (val % 2)? bin.push_back('1') : bin.push_back('0');
            val/=2;
        }
        reverse(bin.begin(), bin.end());
        sss=sss+bin+" ";
    }
    return sss;
    
}
	void senddata(){
		//cout<<"Enter the data you want to send : ";
		cout<<"Enter 1 to enter data in binary, \nor Enter 2 to enter data in decimal, \nEnter 3 to enter string :"<<endl;
		int ts;
		cin>>ts;
		switch(ts)
		{
		 case 1:
		 {
		 cout<<"Enter the data you want to send : ";
		 cin>>s;
		 break;
		 }
		 case 2:
		 {
		     int numdec;
		     cout<<"Enter the data you want to send : ";
		 cin>>numdec;
		 s=decimalToBinary(numdec);
		 break;
		 }
		 case 3:
		 {
		     string sdata;
		     cout<<"Enter the data you want to send : ";
		 cin>>sdata;
		 s=strToBinary(sdata);
		 }
		 default:
		 cout<<"error"<<endl;
		}
	}
	void receiveddata(){
		cout<<"Recieved data : ";
		cout<<s<<endl;
	}
};


void bridgenetwork(devices sen,devices rec, set<int> &lan1, set<int> &lan2){
    if((lan1.find(sen.mac)!=lan1.end() && lan1.find(rec.mac)!=lan1.end()) || (lan2.find(sen.mac)!=lan2.end() && lan2.find(rec.mac)!=lan2.end()))
    {
        cout<<"--------------------------------------------"<<endl;
        cout<<"Data exchange within the LAN"<<endl;
    cout<<"Data was send from device with MAC "<<sen.mac<<" from LAN 1 and was send to "<<rec.mac<<" of LAN 1"<<endl;
    cout<<"--------------------------------------------"<<endl;
    }
    else
    {
        cout<<"--------------------------------------------"<<endl;
    cout<<"Data exchange across the LAN"<<endl;
    cout<<"Data was send from device with MAC "<<sen.mac<<" from LAN 1 and was send to "<<rec.mac<<" of LAN 2"<<endl;
    cout<<"--------------------------------------------"<<endl;
    }
	rec.s=sen.s;
	rec.receiveddata();
	cout<<endl;
	/*long int mac1=123;
	long int mac2=321;
	if(mac==mac2)
	{
		dev2.s=dev1.s;
		dev2.receiveddata();
	}
	else if(mac==mac1)
	{
		dev1.s=dev2.s;
		dev1.receiveddata();
	}*/
}

void switchnetwork(devices device[],devices sen,pair<int,string>headerAndData,int devno){
	int ct=0;// to tell that cam is empty
	int devicemac;
	for(int i=0;i<table.size();i++)
	{
		if(sen.mac==table[i].first && headerAndData.first==table[i].second)
		{
			ct=1;
			devicemac=headerAndData.first;
			cout<<"Address of destination is found in the CAM table and port is successfully recognized."<<endl;
			cout<<"Sending data directly to destination------->"<<endl;
			break;
		}
	}
	if(ct==0)
	{
	    table.clear();
	for(int i=0;i<devno;i++)
	{
		if(device[i].mac==headerAndData.first)
		{
			cout<<"Header accepted for device "<<i+1<<" (DATA ACCEPTED).\n";
			device[i].s=headerAndData.second;
			device[i].receiveddata();
			table.push_back({sen.mac,headerAndData.first});
		}
		else
		{
			cout<<"Header did not match for device "<<i+1<<" (DATA REJECTED)\n";
		}
	}
    }
    else{
    	cout<<"Header accepted for device "<<devdetails[devicemac]<<" (DATA ACCEPTED).\n";
			device[devdetails[devicemac]-1].s=headerAndData.second;
			device[devdetails[devicemac]-1].receiveddata();

    }
	cout<<"bridge network function \n";
}
/*
class HTTP{
        String message;
        int Port = 80;
        endDevice[] arr = new endDevice[10];
    }

    class Telnet{
        String data;
        int Port = 23;
        endDevice[] arr = new endDevice[10];
    }

    class Ephimeral{
        String data;
        Random r = new Random();
        int n = 49152-66535 + 1;
        int i = r.nextInt() % n;
        int port =  49152 + i;
    }
*/

void hubnetwork(devices device[],devices &sen,int devno)
{
	for(int i=0;i<devno;i++)
	{
		if(ssk.find(i+1)!=ssk.end())
		{
		device[i].s=sen.s;
		device[i].receiveddata();
	    }
	}
	sen.s="NULL";
	/*dev2.s=dev1.s;
	dev3.s=dev1.s;
	dev2.receiveddata();
	dev3.receiveddata(); */
}

void tokenpassing(devices device[],queue<int> tokenqueue,int station)
{
    queue<int>g = tokenqueue;
    int rep;
    while (!g.empty()) {
        cout << g.front()<<" station has the token and full access to send data now."<<endl;
        device[g.front()-1].senddata();
        rep=g.front();
        if(device[g.front()-1].s=="0")
        break;
        else
        {
        cout<<"DATA SENT SUCCESSFULLY"<<endl;
        g.pop();
        g.push(rep);
        }
        
    }
}

int n,k;

string XOR(string data,string div,int i){
for(int k=i;k<i+div.length();k++)
{if(data[k]==div[k-i])
  data[k]='0';
 else
  data[k]='1';}
  //cout<<data<<endl;
  return data;
}
string encode(string data,string div){
  n= data.length(),k=div.length();
 for(int i=1;i<k;i++)
   data+='0';
 //cout << "Augmented Data is  "<<data<<endl<<endl;
 string rem=data;
 for(int i=0;i<n;i++)
  {if(rem[i]=='0')
    continue;
   else
    rem= XOR(rem,div,i);}
 cout<<endl;
  
 string code=XOR(data,rem.substr(n,k-1),n);
 

 return code;
 }


//decoding
int decode(string code,string div){
 n= code.length();
 k= div.length();
 for(int i=0;i<n-k+1;i++)
 {if(code[i]=='0')
    continue;
  else
   code= XOR(code,div,i) ;
 }
//cout<<"So,Final remainder is "<<code<<endl;
int zeroes=0,err=0;
for(int i=n-k;i<n;i++)
{if(code[i]=='0')
 zeroes++;}
 if(zeroes==k)
  cout<<"NO ERROR detected using CRC"<<endl;
 else
  {cout<<"ERROR detected using CRC"<<endl<<"DISCARD"<<endl;
   err=1;}
return err;

}

string error(string data,float p){

for(int i=0;i<data.length();i++)
{float r = ((float) rand() / (RAND_MAX));
if(r<p)
{if(data[i]=='0')
 data[i]='1';
 else
 data[i]='0';}
}
return data;
}

//SUBMISSION TWO STARTS HERE
class Switch: public devices{
    public:
    string sw_gateway;
    vector<devices>sdevice;
};
void router(Switch sw[],int nswitch)
    {
        int x=1;
        while(1)
        {
            if(x==0)
            break;
        cout<<"Enter the switch number whose connected device want to send message: "<<endl;
        int stmp; cin>>stmp;
        cout<<"Enter the device number which will send data: "<<endl;
        int setmp;cin>>setmp;
        cout<<"Enter the switch number whose connected device want to receive message: "<<endl;
        int rtmp; cin>>rtmp;
        cout<<"Enter the device number which will receive data: "<<endl;
        int retmp;cin>>retmp;
        sw[stmp-1].sdevice[setmp-1].senddata();
        sw[rtmp-1].sdevice[retmp-1].s=sw[stmp-1].sdevice[setmp-1].s;
        if(stmp==rtmp)
        cout<<"Data was transffered within the LAN and not accross the LAN through router. "<<endl;
        else
        cout<<endl<<"ROUTER WAS USED."<<endl;
        cout<<"Recieved data in device "<<retmp<<" of switch "<<rtmp<<": "<<sw[rtmp-1].sdevice[retmp-1].s<<endl;
        cout<<endl<<"Enter 0 to exit or any other key to continue";
        cin>>x;
        }
        
    }
void assignclassless(Switch &sw,string ipv,int inc)
{
    //for(int i=0;i<2;i++)
    //{
        //sw.sw_gateway=ipv+to_string(inc-1)+"/24";
        for(int j=0;j<sw.sdevice.size();j++)
        {
        string x=to_string(inc);
        string ipx=ipv+x;
        sw.sdevice[j].ip=ipx;
        inc++;
        }
        sw.sw_gateway=ipv+to_string(inc)+"/24";
        //inc=129;
}
int incl=1;
void assignclassfull(Switch &sw, string ipv)
{
	if(ipv=="D" || ipv=="E")
	cout<<"Cannot assign reserved or multicast ip to these devices."<<endl;
	else{
		string ipfront,sub;
	if(ipv=="A")
	{
	ipfront="1.0.0.";
    sub="255.0.0.0";
}
	if(ipv=="B"){
	ipfront="128.0.0.";
	sub="255.255.0.0";
}
	if(ipv=="C")
	{
	ipfront="192.0.0.";
	sub="255.255.255.0";
	}
	for(int j=0;j<sw.sdevice.size();j++)
        {
        string x=to_string(incl);
        string ipx=ipfront+x;
        sw.sdevice[j].ip=ipx;
        sw.sdevice[j].subnet=sub;
        incl++;
        }
}
}
void printip(Switch &sw)
{
    //string k;
    //for(int i=0;i<2;i++)
    //{
    for(int j=0;j<sw.sdevice.size();j++)
    cout<<"I.P of device "<<j+1<<" of Switch is "<<sw.sdevice[j].ip<<endl;
    cout<<"Gateway of this Switch for Router is : "<<sw.sw_gateway<<endl;//<<k+"/25"<<endl;
    cout<<endl;
    //}
}
string arp(string ipfind,Switch sw[],int nos)
{
    for(int i=0;i<nos;i++)
    {
        for(int j=0;j<sw[i].sdevice.size();j++)
        {
            //cout<<sw[i].sdevice[j].ip<<endl;
            if(sw[i].sdevice[j].ip==ipfind)
            return to_string(sw[i].sdevice[j].mac);
        }
    }
    return "NULL";
}
void printarp(Switch sw[],int nos)
{
    cout<<"ARP TABLE"<<endl;
    cout<<"-------------------------------------------"<<endl;
        cout<<"IP ADDRESS    ||  MAC ADDRESS"<<endl;
    cout<<"-------------------------------------------"<<endl;
    for(int i=0;i<nos;i++)
    {
        for(int j=0;j<sw[i].sdevice.size();j++)
        {
            cout<<sw[i].sdevice[j].ip <<" || "<< sw[i].sdevice[j].mac<<endl;
        }
    }
}
int kno=1;
class Router:public Switch{
    public:
    vector<Switch>rdev;
    string port1;
    string port2;
    Router()
    {
        port1="168.0.0.";
        port2="168.0.0.";
    }
    void initit()
    {
        port1=port1+to_string(kno);
        port2=port2+to_string(kno+1);
        kno=kno+2;
    }
};

bool BFS(vector<int> adj[], int src, int dest, int v,int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose adjacency list is to be scanned as per normal DFS algorithm
    list<int> queue;
    // boolean array visited[] which stores the information whether ith vertex is reached at least once in the Breadth first search
    bool visited[v];
    // initially all vertices are unvisited so v[i] for all i is false and as no path is yet constructed dist[i] for all i set to infinity
    for (int i = 0; i < v; i++) {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);
 
    //BFS algo
    while (!queue.empty()) {
        int u = queue.front();
        queue.pop_front();
        for (int i = 0; i < adj[u].size(); i++) {
            if (visited[adj[u][i]] == false) {
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1;
                pred[adj[u][i]] = u;
                queue.push_back(adj[u][i]);
 
                // We stop BFS when we find
                // destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }
 
    return false;
}
void printShortestDistance(vector<int> adj[], int s,
                           int dest, int v)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[v], dist[v];
 
    if (BFS(adj, s, dest, v, pred, dist) == false) {
        cout << "Given source and destination are not connected"<<endl;
        return;
    }
    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }
    // distance from source is in distance array
    cout << "Minimum hop possible will be : "
         << dist[dest];
    // printing path from source to destination
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << "Router "<<path[i] << "-->";
        cout<<"Reached"<<endl;
}
void assignephemeral(devices d1[],int n)
{
    for(int i=0;i<n;i++)
    d1[i].epport=(rand()%17383) + 49152;
}
void assignport(devices d1,int n)
{
    if(n==1)
    d1.wkport=80;
    else if(n==1)
    d1.wkport=80;
    else if(n==1)
    d1.wkport=80;
}
class server{
    public:
  string s="";
  int port;
  int sport;
  server(int p)
  {
      port=p;
  }
};

string findip(string url)
{
    set<pair<string,string>>ipurl;
ipurl.insert({"google.com","142.250.190.142"});
ipurl.insert({"gmail.com","142.251.16.17"});
ipurl.insert({"facebook.com","157.240.229.35"});
ipurl.insert({"piazza.com","54.210.161.152"});
ipurl.insert({"youtube.com","142.251.16.190"});
ipurl.insert({"gradescope.com","35.165.34.237"});
    for(auto i:ipurl)
    {
        if(i.first==url)
        return i.second;
    }
    return "NOT FOUND";
}

void assignipv6(Switch &sw)
{
	map<int,char>mpip;
	mpip[0]='0'; mpip[1]='1'; mpip[2]='2'; mpip[3]='3'; mpip[4]='4'; mpip[5]='5';
	mpip[6]='6'; mpip[7]='7'; mpip[8]='8'; mpip[9]='9'; mpip[10]='A'; mpip[11]='B';
	mpip[12]='C'; mpip[13]='D'; mpip[14]='E'; mpip[15]='F';
	
	for(int j=0;j<sw.sdevice.size();j++)
        {
        	string x;
        	for(int i=0;i<32;i++)
        	{
        	int r=(rand()%16);
            x=x+mpip[r];
            if((i+1)%4==0)
            x=x+":";
            }
        sw.sdevice[j].ip=x;
        }
}



int main()
{
	int test1=1;
	while(test1!=0)
	{
    srand(time(0));
	cout<<"Enter the number of devices you want in your network : ";
	int devno;
	cin>>devno;
	devices device[devno];
	set<int>lan1;
	set<int>lan2;
	cout<<"----------------------------------"<<endl;
	for(int i=0;i<devno;i++)
		{cout<<"Device Created with MAC "<<device[i].mac<<endl;
        devdetails[device[i].mac]=i+1;}
	cout<<"----------------------------------"<<endl;
	int choosedev,choice,rec;
    cout<<"Enter 1 to send data through dedicated connection \nEnter 2 to create a star topology\nEnter 3 to send data through switch network \nEnter 4 to send data through bridge network \nEnter 5 to implement TOKEN PASSING (Access control Protocol)\n";
    cout<<"Enter 6 for CRC:"<<endl;
    cout<<"Enter 7 to implement Flow Control Protocol: (STOP AND WAIT & GO BACK N) "<<endl;
    cout<<"Enter 8 for HUB-->SWITCH-->HUB configuration"<<endl;
    cout<<"----------------------------------------------------------------------------------------"<<endl;
    cout<<"Enter 9 for Router configuration and implementation:"<<endl;
    cout<<"Enter 10 for assigning classless IPV4 address to devices in a configuration and use ARP "<<endl;
    cout<<"Enter 11 to perform static routing: "<<endl;
    cout<<"Enter 12 to perform dynamic routing and find shortest hop distance path between routers: "<<endl;
    cout<<"Enter 13 for transport layer services: "<<endl;
    cout<<"Enter 14 for Application Layer services: "<<endl;
    cout<<"Enter 15 for Add-ONs and others"<<endl;
    cout<<"ENTER YOUR CHOICE:"<<endl;
    cin>>choice;
    int counting=1;// used to create star topology diagram
    choosedev=-1;
    switch(choice)
    {
    case 1: cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
             cin>>choosedev;
             device[choosedev-1].senddata();
             cout<<"Devices Data before Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data before Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
             cin>>rec;
             device[rec-1].s=device[choosedev-1].s;
             device[choosedev-1].s="NULL";
             cout<<"Devices Data after Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data after Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;break;
    
    case 2:
            cout<<"Enter the devices number which you want in Star Topology:(press 0 to end entering): ";
            int temp;
            while(cin>>temp)
            {
                if(temp==0)
                break;
                ssk.insert(temp);
            }
            cout<<"The following device are in Star Topology:\n";
            for(auto j:ssk)
            cout<<j<<" ";
            cout<<endl;
            for(auto j:ssk)
	        {
		    if(counting%2!=0)
		    {cout<<"D"<<j<<"-----  HUB(id-*32)"; counting++;}
	        else
	        {cout<<" -----"<<"D"<<(j)<<endl; counting++;}
	        }
            cout<<endl<<"Choose the device from which you want to send data :\n";
            cin>>choosedev;
            device[choosedev-1].senddata();
            cout<<"Devices Data before Transmission: "<<endl;
            cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data before Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
            hubnetwork(device, device[choosedev-1],devno);
            cout<<"Devices Data after Transmission: "<<endl;
            cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data after Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             break;
    case 3:  
             while(choosedev!=0 || rec!=0)
             {
             cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
             cin>>choosedev;
             if(choosedev==0)
             break;
             device[choosedev-1].senddata();
             pair<int,string>headerAndData;
             cout<<"Data Transferred to Switch\n";
             cout<<"Devices Data before Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data before Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
             cin>>rec;
             headerAndData.first=device[rec-1].mac;
             headerAndData.second=device[choosedev-1].s;
             //long int g=device[rec-1].mac;
             switchnetwork(device, device[choosedev-1],headerAndData,devno);
             device[choosedev-1].s="NULL";
             cout<<"Devices Data after Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(int j=1;j<=devno;j++)
             cout<<"Device "<<j<<" data after Transmission:    "<<device[j-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             cout<<"Switch has per port collision domain so number of COLLISION DOMAIN is "<<devno<<endl;
             cout<<"number of broadcast domain is 1\n"<<endl;
             } break;
    case 4: cout<<"Enter the number of devices on LAN 1 : "<<endl;
            int l1;
            cin>>l1;
            cout<<"Enter device numbers:"<<endl;;
            int temp2;
            while(l1--)
            {
                cin>>temp2;
                lan1.insert(device[temp2-1].mac);
            }
            cout<<"Enter the number of devices on LAN 2 :"<<endl;
            int l2;
            cin>>l2;
            cout<<"Enter device numbers:"<<endl;
            while(l2--)
            {
                cin>>temp2;
                lan2.insert(device[temp2-1].mac);
            }
            cout<<"BRIDGE IS ESTABLISHED"<<endl;
            cout<<"Choose the device from throuh which you want to send data :\n";
            cin>>choosedev;
            device[choosedev-1].senddata();
            cout<<"Enter the device number to which you want to send data : ";
            cin>>rec;
            bridgenetwork(device[choosedev-1],device[rec-1],lan1,lan2);
            cout<<"Bridge has per port collision domain so number of COLLISION DOMAIN is 2"<<endl;
            cout<<"number of broadcast domain is 1"<<endl;
            break;
    case 5: 
            cout<<"Enter the number of stations in the Area: \n";
            int station,sendingstation;
            cin>>station;
            cout<<"Enter the number stations which want to send data:"<<endl;
            cin>>sendingstation;
            cout<<"Enter station queue which are likely to send data:"<<endl;
            int temp3;
            for(int l=0;l<sendingstation;l++)
            {
                cin>>temp3;
                tokenqueue.push(temp3);
            }
            tokenpassing(device, tokenqueue,station);break;
    case 6:
    {
     string data,div="100000111",code;
     cout<<"Enter Data Stream"<<endl;
     cin >> data;
     cout<<"CRC-8 Divisor is "<<div<<endl;
     n= data.length(),k=div.length();
     float token=16.0,block=n/token;
     int a=n%(int)token;
     if(n%(int)token==0)
     {block-=0.5;
     a=token;}
     string arr[(int)ceil(block)];
     for(int i=1;i<=floor(block);i++)
     arr[i]=data.substr(a+token*(i-1),token);
 
    arr[0]=data.substr(0,a);
    int t=arr[0].length();
    for(int i=0;i<token-t;i++)
    arr[0]='0'+arr[0];
 
    string codearr[(int)ceil(block)];

    for(int i=0;i<=floor(block);i++)
    {codearr[i]=encode(arr[i],div);
    cout<<token<<" bit Tokenized data "<<i+1 << " is   : "<<arr[i]<<endl;
    cout<<"CodeWord "<<i+1<<" at sender site is : "<< codearr[i]<< endl;
    cout<<endl;}

    int hops;
    float p;
    cout<<"Enter no of hops in binary symmetric channel : (1 0r 2) ";
    cin>>hops;
    cout<<endl<<"Enter crossover probability for binary symmetric channel :";
    cin>>p;
    cout<<endl;
    string errarr[(int)ceil(block)];
    for(int i=0;i<=floor(block);i++)
    errarr[i]=codearr[i];
    for(int i=0;i<hops;i++)
    {for(int i=0;i<=floor(block);i++)
    errarr[i]=error(errarr[i],p);
 }
    errno=0;
    for(int i=0;i<=floor(block);i++)
    {cout<<"Code Word send     "<<i <<" is " <<codearr[i]<<endl;
    cout<<"Code Word recieved "<<i <<" is "<<errarr[i]<<endl;
    errno+=decode(errarr[i],div);
    cout<<endl;}

    if(errno>0)
    cout<<"Message is Discarded"<<endl;
    else
    {cout<<"NO Error in recieved data & Extracted Data from Code Word is "<<endl;
    for(int i=0;i<=floor(block);i++)
    cout<<errarr[i].substr(0,token);
    cout<<endl;}

    cout<<data;
    cout<<" was our original data     ";
}
// code=encode(data,div);
 break;
case 7:
{
    int chhoice;
    cout<<"Enter 1 for STOP AND WAIT PROTOCOL and Enter 2 for GO BACK N"<<endl;
    cin>>chhoice;
    if(chhoice==1)
    {
    cout<<"STOP AND WAIT PROTOCOL"<<endl;
    cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
    cin>>choosedev;
    cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
    cin>>rec;
    device[choosedev-1].senddata();
    int mtch=0,indx;
    string dta=device[choosedev-1].s;
    cout<<"Enter Y if you want to introduce error, or enter N to continue"<<endl;
    char erchoice,er;
    cin>>erchoice;
    if(erchoice=='y'||erchoice=='Y')
    {
        indx=(rand()%dta.length()) + 1;
        er=dta[indx];
        dta[indx]='2';
    }
    for(int j=0;j<dta.length();j++)
    {
    for(int i=1;i<=devno;i++)
    {
        if(i==choosedev)
        {
        mtch++;
        continue;
        }
        if(dta[j]=='1'||dta[j]=='0')
        {
        if(i!=rec  && mtch<devno-1)
        {  
            mtch++;
            cout<<"FRAME with bit "<<dta[j]<<" SENT TO DEVICE "<<i<<" WITH MAC "<<device[i-1].mac<<" and no ACK recieved"<<endl;
        }
        else if(i==rec){
            cout<<"FRAME with bit "<<dta[j]<<" SENT TO DEVICE "<<i<<" WITH MAC "<<device[i-1].mac<<" (ACKNOWLEDEMENT RECEIVED)"<<endl;
        }
        }
        else
        {
            cout<<"UNABLE TO READ FRAME--------- SEND FRAME AGAIN (NO ACNOWLEDGEMENT)->"<<endl;
            dta[j]=er;//turning back error
            j--;
            break;
        }
        }
    }
    }
    else
    {
        cout<<"GO BACK N"<<endl;
    cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
    cin>>choosedev;
    cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
    cin>>rec;
    device[choosedev-1].senddata();
    cout<<"Enter the sliding window size: "<<endl;
    int slwin;
    cin>>slwin;
    string slstring=device[choosedev-1].s;
    int r=(rand()%slwin) + 3;
    int z=0;
    int pre=0;
    for(int i=0;i<slstring.length();i++)
    {
    	if(z!=r && z<slwin)
    	cout<<"FRAME with bit "<<slstring[i]<<" SENT TO DEVICE WITH MAC "<<device[rec-1].mac<<" (NO ACKNOWLEDEMENT RECEIVED)"<<endl;
        else if(z==r && z<slwin)
        {
        cout<<"FRAME with bit "<<slstring[i]<<" SENT TO DEVICE WITH MAC "<<device[rec-1].mac<<" (ACKNOWLEDEMENT RECEIVED)"<<endl;
        r=(rand()%slwin) + 3;
        z=0;
        pre=i;
        continue;
        }
        else
        {
        cout<<"WAITING--"<<endl;
        r=(rand()%slwin) + 3;
        i=pre-1;
        cout<<"SENDING FRAME AGAIN FROM LAST ACKNOWLEDGED WINDOW SIZE--"<<endl;
        z=0;
        }
        z++;
    }
    }
    }
break;
case 8:
{
    cout<<"Enter the number of devices connected to HUB 1 : "<<endl;
            int l1;
            cin>>l1;
            int temp2;
            while(l1--)
            {
                cin>>temp2;
                lan1.insert(device[temp2-1].mac);
            }
            cout<<"Enter the number of devices on HUB 2 :"<<endl;
            int l2;
            cin>>l2;
            while(l2--)
            {
                cin>>temp2;
                lan2.insert(device[temp2-1].mac);
            }
            choosedev=-1;
        cout<<"SWITCH IS CREATED"<<endl;
        while(choosedev!=0 || rec!=0)
             {
             cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
             cin>>choosedev;
             device[choosedev-1].senddata();
             pair<int,string>headerAndData;
             cout<<"Data Transferred to Switch\n";
             cout<<"Devices Data before Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(auto j:lan1)
             cout<<"Device "<<devdetails[j]<<" data before Transmission:    "<<device[devdetails[j]-1].s<<endl;
             for(auto j:lan2)
             cout<<"Device "<<devdetails[j]<<" data before Transmission:    "<<device[devdetails[j]-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
             cin>>rec;
             headerAndData.first=device[rec-1].mac;
             headerAndData.second=device[choosedev-1].s;
             //long int g=device[rec-1].mac;
             switchnetwork(device, device[choosedev-1],headerAndData,devno);
             cout<<"Devices Data after Transmission: "<<endl;
             cout<<"--------------------------------------------"<<endl;
             for(auto j:lan1)
             cout<<"Device "<<devdetails[j]<<" data before Transmission:    "<<device[devdetails[j]-1].s<<endl;
             for(auto j:lan2)
             cout<<"Device "<<devdetails[j]<<" data before Transmission:    "<<device[devdetails[j]-1].s<<endl;
             cout<<"--------------------------------------------"<<endl;
             }
             break;
}
case 9:
{
cout<<"Enter the number of Switches which will be connected to Router:";
    int nswitch;
    cin>>nswitch;
    Switch sw[nswitch];
    for(int i=0;i<nswitch;i++)
    {
        cout<<"Enter number of devices connected to switch "<<i+1<<" :";
        int nde;
        cin>>nde;
        devices devicesw[nde];
        for(int j=0;j<nde;j++)
        sw[i].sdevice.push_back(devicesw[j]);
    }
    cout<<"Router Connected Successfully"<<endl;
    router(sw,nswitch);
    break;
}
case 10:
{
    cout<<"Enter number of Switches in the network: ";
    int nos; cin>>nos;
   // cout<<"Enter number of devices in Switch 1:"<<endl;
//    int n1; cin>>n1;
  //  cout<<"Enter number of devices in Switch 2:"<<endl;
//    int n2; cin>>n2;
    Switch sw[nos];
    for(int i=0;i<nos;i++)
    {
        cout<<"Enter number of devices in Switch "<<i+1<<" :"<<endl;
    int n1; cin>>n1;
    devices devicesw1[n1];
    for(int j=0;j<n1;j++)
        sw[i].sdevice.push_back(devicesw1[j]);
    }
    //devices devicesw1[n1];
    //devices devicesw2[n2];
    //for(int j=0;j<n1;j++)
      //  sw[0].sdevice.push_back(devicesw1[j]);
    //for(int j=0;j<n2;j++)
      //  sw[1].sdevice.push_back(devicesw2[j]);
    cout<<"Assigning classless IPV4 address to the devices:"<<endl;
    vector<string>ipset;
    ipset.push_back("192.168.100.");
    ipset.push_back("192.168.110.");
    ipset.push_back("192.168.120.");
    ipset.push_back("192.168.130.");
    ipset.push_back("192.168.140.");
    ipset.push_back("192.168.150.");
    ipset.push_back("192.168.160.");
    ipset.push_back("192.168.170.");
    for(int i=0;i<nos;i++)
    {
    assignclassless(sw[i],ipset[i],1);
    }
    //assignclassless(devicesw2,n2,"192.168.100.",129);
    for(int i=0;i<nos;i++)
    printip(sw[i]);
    //printip(devicesw2,n2);
    cout<<"Do you want to see the configuration diagram:(y/n)"<<endl;
    char x;cin>>x;
    if(x=='y')
    {
        for(int i=0;i<20;i++) cout<<" ";
        cout<<"ROUTER"<<endl;
        for(int i=0;i<4;i++)
        cout<<" ";cout<<"192.168.100.3/25"; cout<<"/";cout<<"    \\";cout<<"192.168.110.3/25"<<endl;
        for(int i=0;i<19;i++)
        cout<<" "; cout<<"/";cout<<"      \\"<<endl;
        for(int i=0;i<18;i++)
        cout<<" "; cout<<"/";cout<<"        \\"<<endl;
        for(int i=0;i<15;i++)
        cout<<" ";cout<<"SWITCH 1";cout<<"    SWITCH 2"<<endl;
        cout<<endl;
        for(int i=0;i<15;i++)
        cout<<" "; cout<<"D1 D2           D3 D4"<<endl;
        cout<<endl<<endl<<endl;
    }
    cout<<"Do you want to use arp within the network:(y/n)"<<endl;
    cin>>x;
    if(x=='y')
    {
        cout<<"Enter the I.P address corresponding to which M.A.C id you want to know: "<<endl;
        string ipfind; cin>>ipfind;
        string macfind=arp(ipfind,sw,nos);
        if(macfind!="NULL")
        cout<<"M.A.C of the device is "<<macfind<<endl;
        else
        cout<<"The device is not in the network"<<endl;
    }
    
    cout<<"Do you want to view the arp table: (y/n)"<<endl;
    cin>>x;
    if(x=='y')
    {
        printarp(sw,nos); // function to print arp table
    }
    char bb;
    cin>>bb;
    
    break;
}
case 11:
{
    cout<<"Creating the topology of your network now: "<<endl;
    cout<<"Enter the number of Router: "<<endl;
    int rdevice; cin>>rdevice;
    Router rt[rdevice];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter number of Switches connected to Router "<<i+1<<" :"<<endl;
        int nx; cin>>nx;
        Switch switchnx[nx];
        for(int j=0;j<nx;j++)
        {
        cout<<"Enter number of devices connected to Switch "<<j+1<<" :"<<endl;
        int nj;cin>>nj;
        devices dd[nj];
        for(int z=0;z<nj;z++)
        {
            switchnx[j].sdevice.push_back(dd[z]);
        }
        rt[i].rdev.push_back(switchnx[j]);
        }
    }
    for(int i=0;i<rdevice;i++)
    rt[i].initit();
    /*for(int i=0;i<rdevice;i++)
    {
        cout<<rt[i].port1<<" "<<rt[i].port2<<endl;
    }*/
    cout<<"NOW LETS CONNECTED ROUTERS WITH EACH OTHER"<<endl;
    cout<<"Enter Routers while are connected to each:"<<endl;
    vector<int>topo[rdevice];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter the router numbers which are connected to Router "<<i+1<<endl;
        //int x1,x2; cin>>x1>>x2;
        //if(x1!=0) topo[i].push_back(x1);
        //if(x2!=0) topo[i].push_back(x2);
        int x1=1;
        while(x1!=0)
        {
            cin>>x1;
        if(x1!=0) topo[i].push_back(x1);
        }
    }
    vector<string>ipset;
    ipset.push_back("192.168.100.");
    ipset.push_back("192.168.110.");
    ipset.push_back("192.168.120.");
    ipset.push_back("192.168.130.");
    ipset.push_back("192.168.140.");
    ipset.push_back("192.168.150.");
    ipset.push_back("192.168.160.");
    ipset.push_back("192.168.170.");
    ipset.push_back("192.168.180.");
    ipset.push_back("192.168.190.");
    int counter=0;
    for(int i=0;i<rdevice;i++)
    {
        for(int j=0;j<rt[i].rdev.size();j++)
        assignclassless(rt[i].rdev[j],ipset[counter++],1);
    }
    vector<string>interface_id;
    vector<int>hop;
    cout<<"ROUTER     INTERFACE ID     DESTINATION ROUTER    INTERFACE ID   HOP"<<endl;
    for(int i=0;i<rdevice;i++)
    {
        for(int j=0;j<rt[i].rdev.size();j++)
        cout<<"Router "<<i+1<<"  ||"<<rt[i].rdev[j].sw_gateway<<"  ||      Switch"<<j+1<<" ||   0"<<endl;
        for(int j=0;j<topo[i].size();j++)
        {
            if(j%2==0)
            cout<<"Router "<<i+1<<"  ||"<<rt[i].port1<<"  ||      Router"<<topo[i][j]<<"        ||   "<<rt[topo[i][j]-1].port1<<"   || 1"<<endl;
        else
        cout<<"Router "<<i+1<<"  ||"<<rt[i].port2<<"  ||      Router"<<topo[i][j]<<"        ||   "<<rt[topo[i][j]-1].port1<<"   || 1"<<endl;
        }cout<<"----------------------------------------------------------------------"<<endl;
        
    }
    
    
    
    break;
}
case 12:
{
    cout<<"Creating the topology of your network now: "<<endl;
    cout<<"Enter the number of Router: "<<endl;
    int rdevice; cin>>rdevice;
    Router rt[rdevice];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter number of Switches connected to Router "<<i+1<<" :"<<endl;
        int nx; cin>>nx;
        Switch switchnx[nx];
        for(int j=0;j<nx;j++)
        {
        cout<<"Enter number of devices connected to Switch "<<j+1<<" :"<<endl;
        int nj;cin>>nj;
        devices dd[nj];
        for(int z=0;z<nj;z++)
        {
            switchnx[j].sdevice.push_back(dd[z]);
        }
        rt[i].rdev.push_back(switchnx[j]);
        }
    }
    for(int i=0;i<rdevice;i++)
    rt[i].initit();
    /*for(int i=0;i<rdevice;i++)
    {
        cout<<rt[i].port1<<" "<<rt[i].port2<<endl;
    }*/
    cout<<"NOW LETS CONNECTED ROUTERS WITH EACH OTHER"<<endl;
    cout<<"Enter Routers while are connected to each:"<<endl;
    vector<int>topo[rdevice+1];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter the router numbers which are connected to Router "<<i+1<<endl;
        //int x1,x2; cin>>x1>>x2;
        //if(x1!=0) topo[i].push_back(x1);
        //if(x2!=0) topo[i].push_back(x2);
        int x1=1;
        while(x1!=0)
        {
            cin>>x1;
        if(x1!=0) {topo[i+1].push_back(x1);
        topo[x1].push_back(i+1);}
        }
    }
    vector<string>ipset;
    ipset.push_back("192.168.100.");
    ipset.push_back("192.168.110.");
    ipset.push_back("192.168.120.");
    ipset.push_back("192.168.130.");
    ipset.push_back("192.168.140.");
    ipset.push_back("192.168.150.");
    ipset.push_back("192.168.160.");
    ipset.push_back("192.168.170.");
    ipset.push_back("192.168.180.");
    ipset.push_back("192.168.190.");
    int counter=0;
    for(int i=0;i<rdevice;i++)
    {
        for(int j=0;j<rt[i].rdev.size();j++)
        assignclassless(rt[i].rdev[j],ipset[counter++],1);
    }
    int source, dest;
    cout<<"Enter the source router: "<<endl;
    cin>>source;
    cout<<"Enter the destination router: "<<endl;
    cin>>dest;
    printShortestDistance(topo, source, dest, rdevice+1);
    break;
}
case 13:
{
    int x1;
    cout<<"Enter 1 to establish connection between client and server for communication: (EPHEMERAL PORTS USED)"<<endl;
    cout<<"Enter 2 to use WELL-KNOWN PORT for their specified purpose:"<<endl;
    cout<<"Enter 3 to use sliding window protocol (GO-BACK-N)"<<endl;
    cin>>x1;
    if(x1==1)
    {
        cout<<"Enter the number of client :"<<endl;
        int numcli; cin>>numcli;
        devices d1[numcli];
        int renew=1;
        unordered_set<int>chk;
        while(renew!=0){
        assignephemeral(d1,numcli);
        cout<<"Connecting all clients to PORT 80 of WEB SERVER IPX ------>(EPHEMERAL PORT USED)"<<endl;
        for(int i=0;i<numcli;i++)
        {
            if(chk.find(i+1)==chk.end())
            cout<<"Client "<<i+1<<" connected via PORT "<<d1[i].epport<<"(CONNECTION ESTABLISHED)"<<endl; 
        }
        server servr(80);
        cout<<"-------------------------------------------------------------------------------------"<<endl;
        cout<<"Communication can flow between client and Server now"<<endl;
        cout<<"Enter the device number which want to perform communication:"<<endl;
        int comdev; cin>>comdev;
        d1[comdev-1].senddata();
        servr.s=d1[comdev-1].s;
        udpdata udp;
        udp.data=d1[comdev-1].s;
        udp.sourceport=d1[comdev-1].epport;
        udp.destport=80;
        udp.checksum=abs(~(udp.sourceport+udp.destport+udp.tlength+udp.data.length()));
        
        udp.tlength=sizeof(udp);
        cout<<"Data was sent in a UDP segment format= SOURCE PORT -> DESTINATION PORT -> TOTAL LENGTH -> CHECKSUM -> DATA "<<endl;
        cout<<udp.sourceport<<" "<<udp.destport<<" "<<udp.tlength<<" "<<udp.checksum<<" "<<udp.data<<endl;
        servr.sport=d1[comdev-1].epport;
        cout<<"MESSAGE recieved in SERVER side : "<<servr.s<<endl;
        cout<<"IF MESSAGE RECEIEVED SUCCESSFULLY SERVER WILL REPLY WITH OK TO I.P and CORRESPONDING PORT NUMBER ASSOSIATED DEVICE--"<<endl;
        for(int i=0;i<numcli;i++)
        {
            if(chk.find(i+1)==chk.end()){
            if(d1[i].epport==servr.sport)
            cout<<"OK RECEIEVED -----> Device "<<i+1<<" IP MATCHED AND MESSAGE FORWARDED TO CORRESPONDING PORT"<<endl;
            else
            cout<<"DISCARDED DEVICE "<<i+1<<endl;
            }
        }
        
        cout<<"Continue? enter 1 to continue, 0 to end all: "<<endl;
        cin>>renew;
        if(renew==1)
        {
        cout<<"ENTER the client number which you want to end connection with server: "<<endl;
        int endcon=1;
        while(endcon!=0)
        {
            cin>>endcon;
            if(endcon!=0) chk.insert(endcon);
        }
            
        }}
        
    }
    if(x1==2)
    {
        devices d1;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
        cout<<"Press 1 for File Transfer Protocol (FTP) Data Transfer\nPress 2 for File Transfer Protocol (FTP) Command Control\n";
cout<<"Press 3 for Secure Shell (SSH)\nPress 4 for Telnet - Remote login service, unencrypted text messages\n";
cout<<"Press 5 for Simple Mail Transfer Protocol (SMTP) E-mail Routing\nPress 6 for Domain Name System (DNS) service\n";
cout<<"Press 7 for Hypertext Transfer Protocol (HTTP) used in World Wide Web\nPress 8 for Post Office Protocol (POP3) used by e-mail clients to retrieve e-mail from a server\n";
cout<<"Press 9 for Network News Transfer Protocol (NNTP)\nPress 10 for Network Time Protocol (NTP)\n";
cout<<"Press 11 for Internet Message Access Protocol (IMAP) Management of Digital Mail\nPress 12 for Simple Network Management Protocol (SNMP)\n";
cout<<"Press 13 for Internet Relay Chat (IRC)\nPress 14 for HTTP Secure (HTTPS) HTTP over TLS/SSL\n";
cout<<"-------------------------------------------------------------------------------------"<<endl;
int inp; cin>>inp;
if(inp==1)
{
    d1.wkport=20;
}
if(inp==2)
{
    d1.wkport=21;
}
if(inp==3)
{
    d1.wkport=22;
}
if(inp==4)
{
    d1.wkport=23;
}
if(inp==5)
{
    d1.wkport=25;
}
if(inp==6)
{
    d1.wkport=53;
}
if(inp==7)
{
    d1.wkport=80;
}
if(inp==8)
{
    d1.wkport=110;
}
if(inp==9)
{
    d1.wkport=119;
}
if(inp==10)
{
    d1.wkport=123;
}
if(inp==11)
{
    d1.wkport=143;
}
if(inp==12)
{
    d1.wkport=161;
}
if(inp==13)
{
    d1.wkport=194;
}
if(inp==14)
{
    d1.wkport=443;
}
        cout<<"-------------------------------------------------------------------------------------"<<endl;
cout<<"Assigned port number to the process is "<<d1.wkport<<endl;
        cout<<"-------------------------------------------------------------------------------------"<<endl;
    }
if(x1==3)
{
    cout<<"Enter the number of Router: "<<endl;
    int rdevice; cin>>rdevice;
    Router rt[rdevice];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter number of Switches connected to Router "<<i+1<<" :"<<endl;
        int nx; cin>>nx;
        Switch switchnx[nx];
        for(int j=0;j<nx;j++)
        {
        cout<<"Enter number of devices connected to Switch "<<j+1<<" :"<<endl;
        int nj;cin>>nj;
        devices dd[nj];
        for(int z=0;z<nj;z++)
        {
            switchnx[j].sdevice.push_back(dd[z]);
        }
        rt[i].rdev.push_back(switchnx[j]);
        }
    }
    for(int i=0;i<rdevice;i++)
    rt[i].initit();
    cout<<"NOW LETS CONNECTED ROUTERS WITH EACH OTHER"<<endl;
    cout<<"Enter Routers while are connected to each:"<<endl;
    vector<int>topo[rdevice];
    for(int i=0;i<rdevice;i++)
    {
        cout<<"Enter the router numbers which are connected to Router "<<i+1<<endl;
        //int x1,x2; cin>>x1>>x2;
        //if(x1!=0) topo[i].push_back(x1);
        //if(x2!=0) topo[i].push_back(x2);
        int x1=1;
        while(x1!=0)
        {
            cin>>x1;
        if(x1!=0) topo[i].push_back(x1);
        }
    }
    vector<string>ipset;
    ipset.push_back("192.168.100.");
    ipset.push_back("192.168.110.");
    ipset.push_back("192.168.120.");
    ipset.push_back("192.168.130.");
    ipset.push_back("192.168.140.");
    ipset.push_back("192.168.150.");
    ipset.push_back("192.168.160.");
    ipset.push_back("192.168.170.");
    ipset.push_back("192.168.180.");
    ipset.push_back("192.168.190.");
    int counter=0;
    for(int i=0;i<rdevice;i++)
    {
        for(int j=0;j<rt[i].rdev.size();j++)
        assignclassless(rt[i].rdev[j],ipset[counter++],1);
    }
    cout<<"GO BACK N"<<endl;
    int chrt,chsw,chdv,recrou,recsw,recdv;
    cout<<"Enter the router number from which the device connected want to use GBN"<<endl;
    cin>>chrt;
    cout<<"Enter the switch number:" <<endl;
    cin>>chsw;
    cout<<"Enter the device number from which you want to send data or enter 0 to stop: ";
    cin>>chdv;
    cout<<"Enter the router number from which the device connected will receive data"<<endl;
    cin>>recrou;
    cout<<"Enter the switch number:" <<endl;
    cin>>recsw;
    cout<<"Enter the device number to which you want to send data or enter 0 to stop:: ";
    cin>>recdv;
    rt[chrt-1].rdev[chsw-1].sdevice[chdv-1].senddata();
    //device[choosedev-1].senddata();
    cout<<"Enter the sliding window size: "<<endl;
    int slwin;
    cin>>slwin;
    string slstring=rt[chrt-1].rdev[chsw-1].sdevice[chdv-1].s;
    int r=(rand()%slwin) + 3;
    int z=0;
    int pre=0;
    for(int i=0;i<slstring.length();i++)
    {
    	if(z!=r && z<slwin)
    	cout<<"FRAME with bit "<<slstring[i]<<" SENT TO DEVICE WITH MAC "<<rt[recrou-1].rdev[recsw-1].sdevice[recdv].mac<<" (NO ACKNOWLEDEMENT RECEIVED)"<<endl;
        else if(z==r && z<slwin)
        {
        cout<<"FRAME with bit "<<slstring[i]<<" SENT TO DEVICE WITH MAC "<<rt[recrou-1].rdev[recsw-1].sdevice[recdv].mac<<" (ACKNOWLEDEMENT RECEIVED)"<<endl;
        r=(rand()%slwin) + 3;
        z=0;
        pre=i;
        continue;
        }
        else
        {
        cout<<"WAITING--"<<endl;
        r=(rand()%slwin) + 3;
        i=pre-1;
        cout<<"SENDING FRAME AGAIN FROM LAST ACKNOWLEDGED WINDOW SIZE--"<<endl;
        z=0;
        }
        z++;
    }
}
    break;
}
case 14:
{
    cout<<"Enter 1 for using DNS (Domain Name System): "<<endl;
    cout<<"Enter 2 for using FTP (File Transfer Protocol): "<<endl;
    cout<<"Enter 3 for using HTTP :"<<endl;
    cout<<"Enter 4 to use SSH : "<<endl;
    devices d1;
    d1.ip="14.139.61.130";
    int x1; cin>>x1;
    if(x1==1)
    {
        cout<<"Device IP : "<<d1.ip<<endl;
        d1.wkport=53;
        cout<<"Enter the URL :"<<endl;
        string url; cin>>url;
        cout<<"Corresponding I.P for "<<url<<" is : "<<findip(url)<<endl<<endl;
        cout<< "DNS used UDP port "<<d1.wkport<< " and responded back to IP "<<d1.ip<<endl;
    }
    if(x1==2)
    {
    	devices d1;
        d1.ip="14.139.61.130";
    	cout<<"Device IP : "<<d1.ip<<endl;
        d1.wkport=21;
    	const char* url = "https://yt3.ggpht.com/ytc/AKedOLTIYTlKhaK5CguFSItHWr8ctnAllBL_qjjget1H=s88-c-k-c0x00ffffff-no-rj";
	const char* dst = "C:\\Users\\Cartoon\\Desktop\\Projects\\CN\\\\myfilename.jpg";
	
	/*if (S_OK == URLDownloadToFile(NULL, url, dst, 0, NULL))
	{
		cout<<"You downloaded an image using FTP protocol."<<endl<<"Saved to Desktop."<<endl;
		return 0;
	}
	else
	{
		cout<<"Failed."<<endl;
		return -1;
	}*/
	cout<< "FTP used TCP port "<<d1.wkport<< " and responded back to IP "<<d1.ip<<endl;
	}
	if(x1==3)
	{
    	devices d1;
        d1.ip="14.139.61.130";
    	cout<<"Device IP : "<<d1.ip<<endl;
        d1.wkport=80;
        string webp;
        cout<<"Enter the webpage you want to open using HTTP protocol: "<<endl;
        cin>>webp;
        cout<< "HTTP used TCP port connection "<<d1.wkport<< " and responded back to IP "<<d1.ip<<endl;
        ShellExecute(NULL, "open", "http://google.net",
			NULL, NULL, SW_SHOWNORMAL);
	}
	if(x1==4)
	{
		devices d1;
        d1.ip="14.139.61.130";
    	cout<<"Device IP : "<<d1.ip<<endl;
        d1.wkport=80;
    ShellExecute(NULL, "open", "C:\\Users\\Cartoon\\Desktop\\Projects\\CN\\Database.exe" , NULL, NULL, SW_SHOWDEFAULT);
}
}
break;
case 15:
	{
		cout<<"Enter 1 for classfull addressing: "<<endl;
		cout<<"Enter 2 for IPV6 addressing: "<<endl;
		cout<<"Enter 3 for data transfer simulation between two different PC: "<<endl;
		int x1; cin>>x1;
		if(x1==1)
		{
			cout<<"Enter number of Switches in the network: ";
    int nos; cin>>nos;
    Switch sw[nos];
    for(int i=0;i<nos;i++)
    {
        cout<<"Enter number of devices in Switch "<<i+1<<" :"<<endl;
    int n1; cin>>n1;
    devices devicesw1[n1];
    for(int j=0;j<n1;j++)
        sw[i].sdevice.push_back(devicesw1[j]);
    cout<<"Enter the class of IP you want to assign: (A/B/C/D/E): "<<endl;
    string ipclass; cin>>ipclass;
    cout<<"Assigning classful IPV4 address to the devices:"<<endl;
    assignclassfull(sw[i],ipclass);
    }
    //cout<<"Enter the class of IP you want to assign: (A/B/C/D/E): "<<endl;
    //string ipclass; cin>>ipclass;
    //cout<<"Assigning classful IPV4 address to the devices:"<<endl;
    //for(int i=0;i<nos;i++)
    //assignclassfull(sw[i],ipclass);
    for(int i=0;i<nos;i++)
    {
    	for(int j=0;j<sw[i].sdevice.size();j++)
    	cout<<"Device "<<j+1<<" of Switch "<<i+1<<" has I.P ----> "<<sw[i].sdevice[j].ip<<" & DEFAULT SUBNET -> "<<sw[i].sdevice[j].subnet<<endl;
	}
		}
	if(x1==2)
	{
	cout<<"Enter number of Switches in the network: ";
    int nos; cin>>nos;
    Switch sw[nos];
    for(int i=0;i<nos;i++)
    {
        cout<<"Enter number of devices in Switch "<<i+1<<" :"<<endl;
    int n1; cin>>n1;
    devices devicesw1[n1];
    for(int j=0;j<n1;j++)
        sw[i].sdevice.push_back(devicesw1[j]);
    cout<<"Assigning IPV6 address to the devices:"<<endl;
    assignipv6(sw[i]);
    }
    for(int i=0;i<nos;i++)
    {
    	for(int j=0;j<sw[i].sdevice.size();j++)
    	cout<<"Device "<<j+1<<" of Switch "<<i+1<<" has I.P ----> "<<sw[i].sdevice[j].ip<<endl;
	}
	}
	break;
	if(x1==3)
	{
		ShellExecute(NULL, "open", "C:\\Users\\Cartoon\\Desktop\\Projects\\CN\\dataTransfer.bat" , NULL, NULL, SW_SHOWDEFAULT);
	}
	break;
    default: cout<<"Wrong Input"<<endl; break; 
}
}
cout<<"continue (0->no)"<<endl;
cin>>test1;
cout<<endl<<endl<<endl;
}
    return 0;
}
