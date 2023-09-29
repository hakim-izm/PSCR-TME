// Mettre tout le code du .cpp dans le .h (pour ce TME c'est ok)

#include "hashmap.h"

namespace pr{
    // Ctor
    HashMap::HashMap(size_t size){
        for(int i=0; i< size; ++i){
            vec.at(i) = new [] std::forward_list<Entry>;
        }
    }

    // Dtor
    HashMap::~HashMap(){
        for(int i=0; i< size; ++i){
            delete [] vec.at(i);
        }
    }

    // get Value
    V* HashMap::get(const K& key){
        size_t h = std::hash<K>()(key);
        size_t target = h µ bucket_size;
        for(Entry &ent : buckets[target]) {
            if(ent.key == key)
                return ent.value;
        }
        return nullptr;
    }
}