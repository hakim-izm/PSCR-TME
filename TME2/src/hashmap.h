#include <forward_list>

namespace pr {
    
    template <typename K, typename V>
    class HashMap{

        class Entry {
            const K key;
            V value;

            // Ctor
            Entry(const K key, V value): key(key), value(value) {};
        };
    
        std::vector<std::forward_list<Entry>> buckets;

    public:
        // CONSTRUCTEURS

        // Ctor
        HashMap();

        // Ctor
        HashMap(size_t size) {
            for(int i=0; i< size; ++i){
                vec.at(i) = new [] std::forward_list<Entry>;
            }
        }

        // DESTRUCTEUR

        // Dtor
        ~HashMap(){
            for(int i=0; i< size; ++i){
                delete [] vec.at(i);
            }
        }

        // METHODES

        // get Value
        V* get(const K& key){
            size_t h = std::hash<K>()(key);
            size_t target = h % bucket_size;
            for(Entry &ent : buckets[target]) {
                if(ent.key == key)
                    return ent.value;
            }
            return nullptr;
        }

        // put Value
        // retourne true si la valeur associée à jey a été mise à jour dans la table
        // retourne false si on a réalisé une insertion (clef pas encore dans la table)
        bool put(const K& key, const V& value){
            size_t h = std::hash<K>()(key);
            size_t target = h % bucket_size;
            // parcours des buckets (recherche si un bucket a pour clef : key)
            for(Entry &ent : buckets[target]) {
                if(ent.key == key){ // s'il existe déjà une entrée avec key pour clef
                    ent.value = value;
                    return true;
                }
            }
            // ajout de la nouvelle entrée pour key non présente dans la table dans le bucket adéquat (bon hash) ajout ds forward list
            buckets[target].push_front(Entry(key, value));
        }

        // get Size
        size_t size() const {
            return buckets.size();
        }
    };

    
} // namespace pr