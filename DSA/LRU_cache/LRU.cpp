#include "LRU.h"

LRU::LRU()
{
    max_size = 10;
}

void LRU::addData(const std::string &key, const int &data)
{
    if(dataList.size() == max_size)
    {
        ClearLastEle();
    }
    
    dataList.emplace_front(std::make_pair(key, data));

    auto ListFrontIter = dataList.begin();
    keyMap.emplace(std::make_pair(key, ListFrontIter));
}

int LRU::getData(const std::string &key)
{
    int result;
    auto search = keyMap.find(key);
    
    if(search == keyMap.end())
    {
        return 0;
    }
    
    auto ListIter = search->second;
    result = ListIter->second;
    UpdateList(ListIter);
    
    return result;
}

void LRU::UpdateList(dlist::iterator &it)
{
    dataList.splice(dataList.begin(), dataList, it);
}

void LRU::ClearLastEle()
{
    auto ListLastEle = dataList.back();
    keyMap.erase(ListLastEle.first);
    dataList.pop_back();
}