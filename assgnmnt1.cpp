#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>

using namespace std;

void printpoints(const vector<double> printings);
void amove(vector<double>& ip);
void wmove(vector<double>& ip);
void smove(vector<double>& ip);
void dmove(vector<double>& ip);
void ashift(vector<double>& ips);
void wshift(vector<double>& ips);
void sshift(vector<double>& ips);
void dshift(vector<double>& ips);
void random2(vector<double>& ip);
bool gameover(vector<double>& ip);
bool isitthesame(vector<double>& ip, vector<double>& checker);

int main(){
    ifstream ipfile;
    cout << "enter inital configuration file name:" << endl;
    string ipfilename;
    cin >> ipfilename;

    ipfile.open(ipfilename.c_str());

    vector<double> points;
    int tmp;

    if(!ipfile.is_open()){
        cout << "error the input configuration could not be opened. A default configuration will be used instead" << endl;
        for(int i = 0; i< 15; i++){
            points.push_back(0);
        }
        points.push_back(2);
    }
    else{
        while( ipfile >> tmp){
            points.push_back(tmp);
        }
    }

    printpoints(points);

    bool ended = gameover(points);
    while(!ended){
        cout << "enter your move: w for up; a for left; s for down or d for right" << endl;
        string nextmove;
        cin >> nextmove;

        if(nextmove == "a"){
            vector<double> copypoints;
            for(int i =0; i< points.size(); i++){
                copypoints.push_back(points[i]);
            }
            amove(points);
            bool diditchange = isitthesame(points, copypoints);
            if (!(diditchange)){
                random2(points);
            }
            printpoints(points);
        }
        else if(nextmove == "w"){
            vector<double> copypoints;
            for(int i =0; i< points.size(); i++){
                copypoints.push_back(points[i]);
            }
            wmove(points);
            bool diditchange = isitthesame(points, copypoints);
            if (!(diditchange)){
                random2(points);
            }
            printpoints(points);
        }
        else if(nextmove == "s"){
            vector<double> copypoints;
            for(int i =0; i< points.size(); i++){
                copypoints.push_back(points[i]);
            }
            smove(points);
            bool diditchange = isitthesame(points, copypoints);
            if (!(diditchange)){
                random2(points);
            }
            printpoints(points);
        }
        else if(nextmove == "d"){
            vector<double> copypoints;
            for(int i =0; i< points.size(); i++){
                copypoints.push_back(points[i]);
            }
            dmove(points);
            bool diditchange = isitthesame(points, copypoints);
            if (!(diditchange)){
                random2(points);
            }
            printpoints(points);
        }
    ended = gameover(points);
    }
    cout << "game over" << endl;
    return 0;
}

//printing function
void printpoints(const vector<double> printings){
    for(int i = 0; i<4; i++){
    cout << printings[4*i] << "\t" << printings[4*i+1] << "\t" << printings[4*i+2] << "\t" << printings[4*i+3] << endl;
    }
}

void amove( vector<double>& ip){    //move left
    ashift(ip);
    for(int g=0; g<4; g++){
        if((ip[4*g+0])==(ip[4*g+1])){
                double temp = ip[4*g+0] + ip[4*g+1];
                ip[4*g+1] = 0;
                ip[4*g+0] = temp;
        }
        if((ip[4*g+2])==(ip[4*g+1])){
                double temp = ip[4*g+1] + ip[4*g+2];
                ip[4*g+2] = 0;
                ip[4*g+1] = temp;
        }
        if((ip[4*g+2])==(ip[4*g+3])){
                double temp = ip[4*g+3] + ip[4*g+2];
                ip[4*g+3] = 0;
                ip[4*g+2] = temp;
        }
    }
    ashift(ip);
}

void wmove( vector<double>& ip){     //move up
    wshift(ip);
  for(int g=0; g<4; g++){
        if((ip[g+0])==(ip[g+4])){
                double temp = ip[g+0] + ip[g+4];
                ip[g+4] = 0;
                ip[g+0] = temp;
        }
        if((ip[g+8])==(ip[g+4])){
                double temp = ip[g+4] + ip[g+8];
                ip[g+8] = 0;
                ip[g+4] = temp;
        }
        if((ip[g+8])==(ip[g+12])){
                double temp = ip[g+8] + ip[g+12];
                ip[g+12] = 0;
                ip[g+8] = temp;
        }
    }
    wshift(ip);
}

void smove( vector<double>& ip){   //move down
    sshift(ip);
    for(int g = 0; g<4; g++){
        if((ip[g+8])==(ip[g+12])){
                double temp = ip[g+8] + ip[g+12];
                ip[g+8] = 0;
                ip[g+12] = temp;
        }
        if((ip[g+8])==(ip[g+4])){
                double temp = ip[g+4] + ip[g+8];
                ip[g+4] = 0;
                ip[g+8] = temp;
        }
        if((ip[g+0])==(ip[g+4])){
                double temp = ip[g+0] + ip[g+4];
                ip[g+0] = 0;
                ip[g+4] = temp;
        }
    }
    sshift(ip);
}

void dmove( vector<double>& ip){     //move right
    dshift(ip);
    for(int g = 0; g<4; g++){
        if((ip[4*g+2])==(ip[4*g+3])){
                double temp = ip[4*g+2] + ip[4*g+3];
                ip[4*g+2] = 0;
                ip[4*g+3] = temp;
        }
        if((ip[4*g+2])==(ip[4*g+1])){
                double temp = ip[4*g+1] + ip[4*g+2];
                ip[4*g+1] = 0;
                ip[4*g+2] = temp;
        }
        if((ip[4*g+0])==(ip[4*g+1])){
                double temp = ip[4*g+0] + ip[4*g+1];
                ip[4*g+0] = 0;
                ip[4*g+1] = temp;
        }
    }
    dshift(ip);
}

void random2(vector<double>& ip){
    vector<double> zeroes;
    for(int i=0; i < ip.size(); i++){
        if((ip[i]==0)){zeroes.push_back(i);}
    }
    int x = rand();
    int y = x % zeroes.size();
    ip[(zeroes[y])] = 2;
}

bool gameover(vector<double>& ip){
    bool zero_found = false;
    bool combo_found = false;
    for(int i=0; i < ip.size(); i++){
            if(ip[i]==0){zero_found = true;return false;}
    if(!zero_found){
        for(int x = 0; x < 4; x++){ //check for vertical combos
                            for(int y=0; y < 3; y++){
                                if ((ip[x+4*y])==(ip[x+4*y+4])){
                                    combo_found = true;
                                }
                            }
                        }
                        for(int y = 0; y < 4; y++){//check horizontal combos
                            for(int x=0; x < 3; x++){
                                if ((ip[x+4*y])==(ip[x+1+4*y])){
                                    combo_found = true;
                                }
                            }
                        }
    }}
    if(!combo_found){
            return true;
    }
    else{
            return false;
    }
}

bool isitthesame(vector<double>& ip, vector<double>& checker){
    bool aretheythesame = true;
    for(int j = 0; j<ip.size(); j++){
        if(!((checker[j]) == (ip[j]))){
            aretheythesame = false;
           }
    }
    if(!aretheythesame){return false;}
    else{return true;}
}
void ashift(vector<double>& ips){
    for(int h = 0; h<4; h++){
        if((ips[4*h+2])==0){
            ips[4*h+2] = ips[4*h+3];
            ips[4*h+3] = 0;
        }
        if((ips[4*h+1])==0){
            ips[4*h+1] = ips[4*h+2];
            ips[4*h+2] = ips[4*h+3];
            ips[4*h+3] = 0;
        }
        if((ips[4*h])==0){
            ips[4*h] = ips[4*h+1];
            ips[4*h+1] = ips[4*h+2];
            ips[4*h+2] = ips[4*h+3];
            ips[4*h+3] = 0;
        }
    }
}
void wshift(vector<double>& ips){
for(int h = 0; h<4; h++){
    if((ips[h+8])==0){
       ips[h+8] = ips[h+12];
       ips[h+12] = 0;
    }
    if((ips[h+4])==0){
        ips[h+4] = ips[h+8];
        ips[h+8] = ips[h+12];
        ips[h+12] = 0;
            }
    if((ips[h])==0){
       ips[h] = ips[h+4];
       ips[h+4] = ips[h+8];
       ips[h+8] = ips[h+12];
       ips[h+12] = 0;
    }
}}
void sshift(vector<double>& ips){
for(int h = 0; h<4; h++){
    if((ips[h+4])==0){
       ips[h+4] = ips[h];
       ips[h] = 0;
    }
    if((ips[h+8])==0){
        ips[h+8] = ips[h+4];
        ips[h+4] = ips[h];
        ips[h] = 0;
            }
    if((ips[h+12])==0){
        ips[h+12] = ips[h+8];
        ips[h+8] = ips[h+4];
        ips[h+4] = ips[h];
        ips[h] = 0;
            }
    }}
void dshift(vector<double>& ips){
for(int h = 0; h<4; h++){
    if((ips[4*h+1])==0){
       ips[4*h+1] = ips[4*h];
       ips[4*h] = 0;
    }
    if((ips[4*h+2])==0){
       ips[4*h+2] = ips[4*h+1];
       ips[4*h+1] = ips[4*h];
       ips[4*h] = 0;
    }
    if((ips[4*h+3])==0){
       ips[4*h+3] = ips[4*h+2];
       ips[4*h+2] = ips[4*h+1];
       ips[4*h+1] = ips[4*h];
       ips[4*h] = 0;
    }
    }}
