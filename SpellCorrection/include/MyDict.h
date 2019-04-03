 ///
 /// MyDict.h
 /// Created by yll(1711019653@qq.com).
 /// 2019-2-28 20:31:43 
 /// @Brief: 
 ///


#ifndef __MYDICT_H__
#define __MYDICT_H__

#include "StrUtils.h"
#include <map>
#include <set>

using namespace std;

//单例类
class MyDict{
public:
    static MyDict* getInstance(const string& p1, const string& p2){
        if(!_Instance){
            _Instance = new MyDict(p1, p2);
        }
        return _Instance;
    }
    void init();
    void initDict();
    void initIndex();
    vector<pair<string, int>> &getDict(){
        return _dict;
    }
    map<string, set<int>> &getIndexTable(){
        return _index;
    }
    void list(); //only for test
    static void Delelte(){
        if(_Instance)
            delete _Instance;
    }
private:
    MyDict(const string& cnPath, const string& enPath)
    : _enPath(enPath)
    , _cnPath(cnPath) {}
    ~MyDict() {}
private:
    string _enPath;
    string _cnPath;
    static MyDict *_Instance;
    vector<pair<string, int>> _dict;
    map<string, set<int>> _index;
};




#endif