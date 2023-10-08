#include <forward_list>

namespace pr {
    
    template <typename K, typename V>
    class HashMap{

        class Entry {
            public:
                const K key;
                V value;

                // Ctor
                Entry(const K key, V value): key(key), value(value) {};
        };

        std::vector<std::forward_list<Entry>> buckets;

    public:
        // Sous-classe iterator
        class iterator {
            public:
                std::vector<std::forward_list<Entry>>& buckets; // ref vers table buckets
                typename std::vector<std::forward_list<Entry>>::iterator vit; // itérateur dans la table désignant le bucket en cours d'exploration
                typename std::forward_list<Entry>::iterator lit; // point l'élément courant dans la liste

                // Ctor
                iterator(std::vector<std::forward_list<Entry>>& buckets, typename std::vector<std::forward_list<Entry>>::iterator vit, typename std::forward_list<Entry>::iterator lit): buckets(buckets), vit(vit), lit(lit) {}

                iterator& operator++() {
                    std::cout << "operator++ : " << lit->key << std::endl;
                    // on incrémente d'abord lit
                    ++lit;
                    // si on est au bout de la liste (lit == vit->end())
                    if(lit == vit->end()){
                        // on recherche la prochaine case non vide de vit
                        while(vit->empty() && vit != buckets.end()) {
                            vit++;
                        }
                        // attention au débordement (if)
                        if(vit != buckets.end())
                            // on met lit en tête de liste
                            lit = vit->begin();
                    }

                    return *this;
                }

                bool operator!=(const iterator &other) {
                    return (lit != other.lit) || (vit != other.vit);
                }

                Entry & operator*() {
                    return *lit;
                }
        };

        // CONSTRUCTEURS

        // Ctor
        HashMap(){}

        // Ctor
        HashMap(size_t size) {
            for(size_t i=0; i<size; ++i){
                buckets.push_back(std::forward_list<Entry>());
            }
        }

        // METHODES

        // get Value
        V* get(const K& key){
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            for(Entry &ent : buckets[target]) {
                if(ent.key == key)
                    return &ent.value;
            }
            return nullptr;
        }

        // put Value
        // retourne true si la valeur associée à jey a été mise à jour dans la table
        // retourne false si on a réalisé une insertion (clef pas encore dans la table)
        bool put(const K& key, const V& value){
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            // parcours des buckets (recherche si un bucket a pour clef : key)
            for(Entry &ent : buckets[target]) {
                if(ent.key == key){ // s'il existe déjà une entrée avec key pour clef
                    ent.value = value;
                    return true;
                }
            }
            // ajout de la nouvelle entrée pour key non présente dans la table dans le bucket adéquat (bon hash) ajout ds forward list
            buckets[target].push_front(Entry(key, value));
            return false;
        }

        // get Size
        size_t size() const {
            return buckets.size();
        }

        // get Begin
        // iterator begin() const {
        //     return buckets.begin();
        // }
        iterator begin() {
            // on recherche le premier bucket non vide
            for(auto vit = buckets.begin(); vit != buckets.end(); ++vit){
                if(!vit->empty())
                    return iterator(buckets, vit, vit->begin());
            }
            // si tous les buckets sont vides, on retourne end()
            return end();
        }

        // get End
        // iterator end() const {
        //     return buckets.end();
        // }
        iterator end() {
            // on retourne un itérateur sur le dernier bucket
            return iterator(buckets, buckets.end(), buckets.back().end());
        }
    };

    
} // namespace pr