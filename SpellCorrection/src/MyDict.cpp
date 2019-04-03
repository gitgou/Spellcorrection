 ///
 /// MyDict.cpp
 /// Created by yll(1711019653@qq.com).
 /// 2019-02-20 20:54:17
 /// @Brief: 
 ///

#include "QueryTask.h"
#include "Mylog.h"

#include <fstream>

MyDict* MyDict::_Instance = NULL;

void MyDict::init(){
    initDict();
    initIndex();
    LogInfo("Dict Initializei.");
}

void MyDict::initDict(){

    string words;
    int freq;
{//enDict

    ifstream enDict(_enPath);
	//以空格为划分，故一次输入两个数据为一个键值对
	while(enDict >> words >> freq){
        _dict.push_back(pair<string, int>(words, freq));
    }
}

{//cnDict
    ifstream cnDict(_cnPath);
    while(cnDict >> words >> freq){
        _dict.push_back(pair<string, int>(words, freq));
    }
}
}
//num代表在字典vector中的位置
void MyDict::initIndex(){
    int num = 0;
    for(auto c : _dict){
        string one = c.first;
        if(isUTF8(one)){
            for(string::size_type col = 0; col < one.size(); col+=3){
                string sing = one.substr(col, 3);
                _index[sing].insert(num);
            }
        }
        else{
            for(string::size_type col = 0; col < one.size(); ++col){
                string sing = one.substr(col, 1);
                _index[sing].insert(num);
           } 
        }
        ++num;
    }
}

void MyDict::list(){
    auto map_it = _index.cbegin();
    while(map_it != _index.cend()){
        cout << map_it->first << " :";
        for(auto c : map_it->second){
            cout << " " <<  _dict[c].first; 
        }
        cout << endl;
        ++map_it;
    }
}
