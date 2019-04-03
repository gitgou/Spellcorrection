 ///
 /// CacheManager.cpp
 /// Created by yll(1711019653@qq.com).
 /// 2018-02-13 22:24:32
 /// @Brief: 
 ///

#include "CacheManager.h"

void CacheManager::initCache(){
    Cache<> mainCache;
    mainCache.readFromFile(_cacheDiskPath);
    _cacheList.push_back(mainCache);
    LogInfo("The main Cache was initialize.");
}

Cache<>& CacheManager::getCache(){
    //wd::MutexLockGuard mlg(_mutex);
    auto it = _Thread2Cache.find(pthread_self());
    cout << "judge it" << endl;
    if(it == _Thread2Cache.cend()){
        _Thread2Cache.insert(make_pair(pthread_self(), _cacheList.size()));
        Cache<> newCache;
        newCache.readFromFile(_cacheDiskPath);
        _cacheList.push_back(newCache);
        it = _Thread2Cache.find(pthread_self());
        LogWarn("A new Cache was mapped to a thread.");
    }
    return _cacheList[it->second];
}


void CacheManager::periodcUpdate(){
    int updated = 0;
    for(auto &c : _cacheList){
        c.setUpdateTag();
        c.waitSet();//临界资源互斥访问
        updated += c._newCacheCnt;
        cout << c._newCacheCnt << endl;
    }
    cout << "----------Cache Update Start------" << endl;
    //判断总的更新数与cache内存大小得出需要更新的总数
	int total = updated < _cacheList[0]._size ? updated : _cacheList[0]._size;
    cout << "total = " << total << endl;
    if(total == 0){
        LogWarn("No cache to update in this period.");
        cout << "No need to updated" << endl;
        cout << "------------Cache Updated end -------------" << endl;
        return;
    }
    int ret = total;
    int seq = 0;
    while(total){
        for(auto &c : _cacheList){
            if(c._newCacheCnt == 0)
                continue;
            else{ 
                int in_seq = seq;
                Node<> *nodePending = c._head;
				//seq代表第几轮循环，故取每个cache的第几个节点进行更新
                while(in_seq--){
                    nodePending = nodePending->next;
                    cout << nodePending << endl;
                }
                cout << nodePending->_query << " " << nodePending->_jsonfile << endl;
                string getFromMain = _cacheList[0].get(nodePending->_query);
                cout << getFromMain<< " " << getFromMain.size() <<  endl;
                if(getFromMain.size() == 0){
                   //插入前需要解除UpdateTag
					_cacheList[0].removeUpdateTag();
                    cout << "before set" << _cacheList[0]._cacheMap.size() << endl;
                    _cacheList[0].set(nodePending->_query, nodePending->_jsonfile);
                    cout << "after set" << _cacheList[0]._cacheMap.size() << endl;
                    _cacheList[0].setUpdateTag();
                }
                --c._newCacheCnt;
                --total;
                if(total == 0)
                    break;
            }
        }
        ++seq;
    }
    for(auto &c : _cacheList){
        c._newCacheCnt = 0;
        c.removeUpdateTag();
    } 
    _cacheList[0].writeToFile(_cacheDiskPath);
    string logwarn = to_string(ret) + " cache on disk updated.";
    LogWarn(logwarn);
    cout << ret << "Cache ON Disk Updated" << endl;
    cout << "------------Cache Updated end -------------" << endl;
}
