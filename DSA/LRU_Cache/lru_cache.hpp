#ifndef LRU_CACHE_HPP
#define LRU_CACHE_HPP

#include <cstddef>
#include <list>
#include <unordered_map>

namespace rp
{
    template<typename t_key, typename t_value>
    class LRU_Cache
    {
        using DataList = std::list<std::pair<t_key, t_value>>;
        using DataMap = std::unordered_map<t_key, typename DataList::iterator>;

        public:
            LRU_Cache() = delete;
            LRU_Cache(std::size_t sz) : max_size(sz) {}

            void addData(const t_key& key, const t_value& value)
            {
                auto SearchIt = dmap.find(key);

                if( SearchIt == dmap.end() )
                {
                    if( dlist.size() == max_size )
                    {
                        clearLastEle();
                    }
                    dlist.emplace_front(std::make_pair(key,value));
                    dmap.emplace(std::make_pair(key, dlist.begin()));
                }
                else
                {
                    auto ListIt = SearchIt->second;
                    ListIt->second = value;
                    updateList(ListIt);
                }
            }
            bool getData(const t_key& key, t_value& value)
            {
                auto SearchIt = dmap.find(key);

                if( SearchIt == dmap.end() )
                {
                    return false;
                }

                auto ListIt = SearchIt->second;
                value = ListIt->second;
                updateList(ListIt);

                return true;
            }
            const std::pair<t_key, t_value>& getMRU()
            {
                return dlist.front();
            }
            const std::pair<t_key, t_value>& getLRU()
            {
                return dlist.back();
            }

        private:
            std::size_t max_size;
            DataList dlist;
            DataMap dmap;

            void clearLastEle()
            {
                auto LastEle = dlist.back();
                dmap.erase(LastEle.first);
                dlist.pop_back();
            }
            void updateList(typename DataList::iterator& it)
            {
                dlist.splice(dlist.begin(), dlist, it);
            }
    };
}

#endif
