 #ifndef INC_21F_FINAL_PROJ_TEMPLATE_DSHASHTABLE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_DSHASHTABLE_H

#include <list>
#include <iostream>
#include "DSList.h"
#include "DSString.h"
#include "string"
//#include "cityhash-master/src/city.h"


template<typename T, typename U>
class DSHashTable {
private:
    struct DataEntry{
        T key;
        U value;
        DataEntry() = default;
        DataEntry(T k, U v) {
            key = k;
            value = v;
        }
    };
    //std::vector<DataEntry>* hashTable;
    std::list<DataEntry>* table;
    int hashSize;
    int numElements;

public:
    DSHashTable() {
        hashSize = 100003;
        //hashTable = new std::vector<DataEntry>[hashSize];
        table = new std::list<DataEntry>[hashSize];
        numElements = 0;
    }

    ~DSHashTable() {
        delete[] table;
        numElements = 0;
        hashSize = 0;
    }

    bool isEmpty() const {
        int sum;
        for(int i = 0; i < hashSize; i++) {
            sum += table[i].size();
        }
        if(sum == 0)
            return true;
        return false;
    }

    int hashFunction(const T& key) {
        auto h = std::hash<T>{}(key);
        return h % hashSize;
    }

    U& get(const T& key) {
        int loc = hashFunction(key);
        for(auto &c : table[loc]) {
            if (c.key == key)
                return c.value;
        }
        throw std::runtime_error("Key not found");
    }

//    struct DataEntry* search(T key) {
//        int index = hashFunction(key);
//        while(table[index] != nullptr) {
//            if(table[index].key == key)
//                return table[index];
//            ++index;
//            index %= hashSize;
//        }
//        return nullptr;
//    }

    U& insert(T key) {
        int ind = hashFunction(key);
        auto iter = table[ind].begin();
        while(iter != table[ind].end()) {
            if(iter->key == key)
                return iter->value;
            iter++;
        }

        DataEntry e{};
        e.key = key;
        table[ind].push_back(e);
        numElements++;
        return get(e.key);
    }

    void insert(T key, U val) {
        int ind = hashFunction(key);
        //std::list<DataEntry>* cell = table[ind];

        //auto& cell = table[ind];
        auto iter = table[ind].begin();
        //auto it = cell.begin();
        bool keyExists = false;
        while(iter != table[ind].end()) {
//            DataEntry* temp = iter;
            if(iter->key == key) {
                keyExists = true;
                iter->value = val;
                //warn user of replacement
                break;
            }
            iter++;
        }

        if(!keyExists){
            DataEntry e(key, val);
            table[ind].push_back(e);
            numElements++;
        }
//        DataEntry d(key, val);
//        auto value = std::hash<T>{}(key);
//        int loc = value % hashSize;
//        table[loc].push_back(d);
    }

    bool remove(T key) {
        int ind = hashFunction(key);
        auto& cell = table[ind];
        auto iter = cell.begin();
        while(iter != cell.end()) {
            //DataEntry* temp = iter;
            if(iter->key == key) {
                iter = cell.erase(iter);
                //item removed
                return true;
            }
            iter++;
        }
        return false;
    }

    void printTable() {
        for(int i = 0; i < hashSize; i++) {
            if(table[i].size() == 0)
                continue;
            auto iter = table[i].begin();
            while(iter != table[i].end()) {
                //DataEntry* temp = iter;
                std::cout << "Key: " << iter->key << " Value: " << iter->value << std::endl;
                iter++;
            }
        }
    }

    void copyToVector(std::vector<std::pair<T, U>>& vec) {
        for(int i = 0; i < hashSize; i++) {
            if(table[i].size() == 0)
                continue;
            auto iter = table[i].begin();
            while(iter != table[i].end()) {
                //DataEntry* temp = iter;
                vec.push_back(std::pair<T, U>(iter->key, iter->value));
                iter++;
            }
        }
    }

    void clear() {
        delete[] table;
        table = new std::list<DataEntry>[hashSize];
        numElements = 0;

    }


    int size() {
        return numElements;
    }


};

#endif //INC_21F_FINAL_PROJ_TEMPLATE_DSHASHTABLE_H
