#ifndef LRU_H
#define LRU_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <string>
#include <utility>

using dlist = std::list<std::pair<std::string, int>>;

class LRU
{
    public:
        LRU();
        int getData(const std::string &key);
        void addData(const std::string &key, const int &data);
        
    private:
        std::unordered_map<std::string, dlist::iterator> keyMap;
        dlist dataList;
        size_t max_size;
        
        void UpdateList(dlist::iterator &it);
        void ClearLastEle();
};

#endif // LRU_H