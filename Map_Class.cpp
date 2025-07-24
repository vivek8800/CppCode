#include<iostream>
#include<vector>
#include<list>
using namespace std;

template<typename K, typename V>
class HashMap
{
    int bucketSize;
    int ElementCount;
    double loadFactor;
    vector<list<pair<K, V>>> Table;

    /*
        std::hash<K> is a function object (functor) provided by C++ Standard Library that
        computes a hash code for objects of type K.

        {} creates a temporary object of type std::hash<K>.

        () calls the function operator of the object with the argument key.
    */
    
    int getIndex(K key)
    {
        // this hash() is in standatd c++, required to convert string or char to any random value as 
        // we can't do mod string with int
        size_t hashVal = std::hash<K>{}(key);
        return hashVal % bucketSize;
    }

    void rehash()
    {
        int oldBucketSize = bucketSize;
        bucketSize = 2*bucketSize;

        vector<list<pair<K, V>>> NewTable(bucketSize);

        for(int i=0; i<oldBucketSize; ++i)
        {
            for(auto &it: NewTable[i])
            {
                int index=getIndex(it.first);
                NewTable[i].push_back(it);
            }
        }

        Table=NewTable; // deep copy 
    } 

    public:
    
    HashMap(int x = 2):bucketSize(x), ElementCount(0), loadFactor(0.75)
    {
        Table.resize(bucketSize);   // resize the vector to have 'bucketSize' number of lists
        cout<<"HashMap created with bucket size: "<<bucketSize<<endl;
    }
    
    void push(const K key, const V value)
    {
        int index=getIndex(key);
        for(auto &i: Table[index])
        {
            if(i.first==key)
            {
                i.second=value;
                return;
            }
        }
        
        cout<<"Key: "<<key<<"--> Value: "<<value<<" inserted in table at index: "<<index<<endl;
        
        Table[index].push_back({key, value});
        ElementCount++;
        
        // check for resize of hash
        if(ElementCount/bucketSize > loadFactor)
        {
            rehash();
        }
    }
    
    void printMap()
    {
        cout<<"Printing HashMap key value:-"<<endl;
        for(int i=0;i<bucketSize;i++)
        {
            if(!Table[i].empty())
            {
                for(auto i: Table[i])
                {
                    cout<<i.first<<" -> "<<i.second<<endl;
                }
            }
        }
    }
    
    int getSize()
    {
        return bucketSize;
    }
    
    int FindValue(K key)
    {
        int index=getIndex(key);
        for(auto it: Table[index])
        {
            if(it.first==key)
            {
                cout<<"value found: "<<it.second<<" For key: "<<key<<endl;
                return it.second;
            }
        }
        cout<<"Key not found!!!"<<endl;
        return -1;
    }
    
    void removeElement(K key)
    {
        int index=getIndex(key);
        for(auto it=Table[index].begin();it!=Table[index].end();it++)
        {
            if(it->first==key)
            {
                Table[index].erase(it);
                return;
            }
        }
        
        cout<<"key not found"<<endl;
    }
};

int main()
{
    HashMap<string, int> h;
    h.push("aaa",60);
    h.push("bbb", 90);
    h.push("ccc", 80);
    h.printMap();
    h.FindValue("ccc");

    h.removeElement("bbb");

    h.printMap();
    
    h.removeElement("bbb");
    
    return 0;
}