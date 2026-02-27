#pragma once
#include <vector>
#include <string>

template<typename T>
class HashTable
{
public:
	HashTable() = default;
	~HashTable() = default;

    static int GetHash(const std::string& key)
    {
        int hash = 0;
        for (int i = 0; i < static_cast<int>(key.size()); i++)
        {
            hash = hash * 31 + key[i];
        }
        return std::abs(hash);
    }

    bool Add(const std::string& key, const T& value)
    {
        int hash = GetHash(key) % bucketCount;
        int chainingSize = static_cast<int>(chainingTable[hash].size());
        for (const std::pair<std::string, T>& data : chainingTable[hash])
        {
            if (data.first == key)
                return false;
        }

        chainingTable[hash].emplace_back(std::make_pair(key, value));
        return true;
    }

    bool Delete(const std::string& key)
    {
        typename std::vector<std::pair<std::string, T>>::iterator iter;
        if (!Find(key, iter))
            return false;

        int hash = GetHash(key) % bucketCount;
        delete iter->second;
        iter->second = nullptr;
        chainingTable[hash].erase(iter);

        return true;
    }

    bool Find(const std::string& key, typename std::vector<std::pair<std::string, T>>::iterator& out)
    {
        int hash = GetHash(key) % bucketCount;
        int chainingSize = static_cast<int>(chainingTable[hash].size());
        if (chainingSize == 0)
            return false;

        for (auto iter = chainingTable[hash].begin(); iter != chainingTable[hash].end(); iter++)
        {
            if ((*iter).first == key)
            {
                out = iter;
                return true;
            }
        }

        return false;
    }

    bool Empty()
    {
        return Size() == 0;
    }

    int Size()
    {
        int count = 0;
        for (auto& table : chainingTable)
        {
            for (auto& data : table)
            {
                count++;
            }
        }
        return count;
    }

    template<typename Func>
    void ForEach(Func func)
    {
        for (auto& table : chainingTable)
        {
            for (auto& data : table)
            {
                func(data.second);
            }
        }
    }

private:
	static const int bucketCount = 19;
	std::vector<std::pair<std::string, T>> chainingTable[bucketCount];
};

