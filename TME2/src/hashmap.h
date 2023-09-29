#include <forward_list>

namespace pr {
    
    template <typename K, typename V>
    class HashMap{

        class Entry {
            K key;
            V value;
        };
    
        std::vector<std::forward_list<Entry>> vec;

    public:
        HashMap();

        // Ctor
        HashMap(size_t size);

        // Dtor
        ~HashMap();

        // get Value
        V* get(const K& key);

    };

    
}