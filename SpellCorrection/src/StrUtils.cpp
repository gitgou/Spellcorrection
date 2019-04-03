
#include "StrUtils.h"

using namespace std;

int min(int a, int b, int c){
    int tmp = a < b ? a : b;
    return tmp < c ? tmp : c;
}

bool isUTF8(const string &one){
    return ( one[0] & 0xe0 && one[1] & 0x80 && one[2] & 0x80);
}
//中文为utf-8编码,中文占三个字节，英文非utf-8编码.
vector<string> Str2Vec(const string& rhs){
    vector<string> ret;
    if(isUTF8(rhs)){
        for(string::size_type col = 0; col < rhs.size(); col+=3){
            string sing = rhs.substr(col, 3);
            ret.push_back(sing);
        }
    }
    else{
        for(string::size_type col = 0; col < rhs.size(); ++col){
            string sing = rhs.substr(col, 1);
        //cout << "str2vec : " << rhs << " :  "<< sing <<endl;
            
            ret.push_back(sing);
        } 
    }
    //cout << "str2vec : " << ret.size() <<endl;
    return ret;
}

