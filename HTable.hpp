//HTable.hpp
//SENG1120
//Written by: Jeremy Anderson c3315176
//Updated: 18/11/20
//Designed for use with files related c3315176.zip for A3
//HTable class: hash function that inserts
//              to an array, based on storing type item
//This is the implementation


using namespace std;

template <typename Item>
HTable<Item>::HTable(){
    capacity = 150;
    hash_table = new Item[capacity];
    for (int i=0; i<capacity; i++)
        hash_table[i] = "NULL";
}

template <typename Item>
HTable<Item>::~HTable(){

}

template <typename Item>
void HTable<Item>::add(const Item& data){
    int pos = hashFun(data);
    hash_table[pos] = data;
}


template <typename Item>
bool HTable<Item>::remove(const Item& data){
    int pos = hashFun(data);
    if (hash_table[pos] == "NULL")
        return false;
    else {
        hash_table[pos] = "NULL";
        return true;
    }
}

template <typename Item>
int HTable<Item>::hashFun(Item value) {
    int addResult = 0;
    for (int i=0; i<value.length(); i++){
        addResult += (int)value.at(i);
    }
    return addResult % 150;
}

template <typename Item>
Item HTable<Item>::inOrder() const {
    Item out = "";
    for (int i=0; i<capacity; i++){
        if (hash_table[i] != "NULL")
            out += hash_table[i] + " ";
    }
    return out;
}


template <typename Item>
void HTable<Item>::operator += (HTable<Item> hashTable2){
    for (int i=0; i<capacity; i++){
        if (hashTable2.hash_table[i] != "NULL") {
            Item insert = hashTable2.hash_table[i];
            add(insert);
        }
    }
}


template <typename Item>
ostream& operator << (ostream& out, HTable<Item> hashTable){
    out << hashTable.inOrder();
    return out;
}






