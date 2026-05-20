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
            LRU_Cache(const LRU_Cache& other) : max_size(other.max_size)
            {
                for(const auto& list_item : other.dlist)
                {
                    auto list_iter = dlist.emplace(dlist.end(), list_item);
                    dmap.emplace(list_item.first, list_iter);
                }
            }
            LRU_Cache(LRU_Cache&& other) : max_size(other.max_size) noexcept
            {
                dlist = std::move(other.dlist);
                dmap = std::move(other.dmap);
                other.max_size = 0;
            }
            ~LRU_Cache() = default;
            LRU_Cache& operator=(const LRU_Cache& other)
            {
                dlist.clear();
                dmap.clear();
                max_size = other.max_size;

                for(const auto& list_item : other.dlist)
                {
                    auto list_iter = emplace(dlist.end(), list_item);
                    dmap.emplace(list_iter.first, list_iter);
                }

                return *this;
            }
            LRU_Cache& operator=(LRU_Cache&& other)
            {
                if(this == &other)
                {
                    return *this;
                }

                dlist.clear();
                dmap.clear();
                max_size = other.max_size;
                dlist = std::move(other.dlist);
                dmap = std::move(other.dmap);
                other.max_size = 0;

                return *this;
            }

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
