//
// Created by hdani on 11/06/2023.
//

#ifndef SEMESTERB_TASK5_BIMAP_H
#define SEMESTERB_TASK5_BIMAP_H
#include <map>

using namespace std;

template <class Key, class Value>
class BiMap
{
    public:
        // Default constructor
        BiMap(){;}
        // Destructor
        ~BiMap(){;}

        // Insert a pair (first, second) into the BiMap
        bool insert(const Key& first, const Value& second);
        // Insert a pair (second, first) into the BiMap
        bool insert(const Value& second, const Key& first);
        // Erase the pair with the specified first key
        bool erase(const Key& first);
        // Erase the pair with the specified second value
        bool erase(const Value& second);

        // Access the value associated with the given first key
        Value operator[](const Key& first);
        // Access the key associated with the given second value
        Key operator[](const Value& second);

        // Check if a pair with the specified first key exists in the BiMap
        bool find(const Key& first){return m_Straight_Map.count(first) != 0;}
        // Check if a pair with the specified second value exists in the BiMap
        bool find(const Value& second){return m_Reverse_Map.count(second) != 0;}
        // Get the size of the BiMap
        int size()const;
        // Sort the BiMap by city and print it to the outputFile
        void sortByCityAndPrint(fstream& outputFile);
        // Sort the BiMap by representation and print it to the outputFile
        void sortByRepAndPrint(fstream& outputFile);
        // Clear the BiMap
        void clearMap(){m_Straight_Map.clear(), m_Reverse_Map.clear();}

    // Iterator for the BiMap (iterates over the first keys)
    class iteratorF
        {
            public:
                // Constructor for iteratorF class
                explicit iteratorF(const typename map<Key, Value>::iterator& other): m_it(other){};
                // Prefix increment operator
                iteratorF operator++()
                {
                    ++m_it;
                    return *this;
                }
                // Postfix increment operator
                iteratorF operator++(int)
                {
                    iteratorF oldIteratorF = *this;
                    ++m_it;
                    return oldIteratorF;
                }
                // Multiplication operator
                iteratorF operator*(const iteratorF& other)
                {
                    m_it *= other.m_it;
                    return *this;
                }
                // Arrow operator
                Key& operator->(){return *m_it;}
                // Get the second value associated with the current iterator position
                Value& getSecond(){return m_it->first;}
                // Equality operator
                bool operator==(const iteratorF& other){return m_it  == other.m_it;}
                // Inequality operator
                bool operator!=(const iteratorF& other){return m_it  != other.m_it;}
            private:
                typename map<Key, Value>::iterator m_it;
        };
        // Get the iterator pointing to the beginning of the BiMap (first keys)
        iteratorF beginF(){return iteratorF(m_Straight_Map.begin());}
        // Get the iterator pointing to the end of the BiMap (first keys)
        iteratorF endF(){return iteratorF(m_Straight_Map.end());}

        // Iterator for the BiMap (iterates over the second values)
        class iteratorS
        {
        public:
            // Constructor for iteratorS class
            explicit iteratorS(const typename map<Value, Key>::iterator& other): m_it(other){};

            // Prefix increment operator
            iteratorS operator++()
            {
                ++m_it;
                return *this;
            }
            // Postfix increment operator
            iteratorS operator++(int)
            {
                iteratorS oldIteratorS = *this;
                ++m_it;
                return oldIteratorS;
            }
            // Multiplication operator
            iteratorS operator*(const iteratorS& other)
            {
                m_it *= other.m_it;
                return *this;
            }
            // Arrow operator
            Value& operator->(){return *m_it;}
            // Get the first key associated with the current iterator position
            Key& getFirst(){return m_it->second;}
            // Equality operator
            bool operator==(const iteratorS& other){return m_it  == other.m_it;}
            // Inequality operator
            bool operator!=(const iteratorS& other){return m_it  != other.m_it;}
        private:
            typename map<Value, Key>::iterator m_it;
        };
        // Get the iterator pointing to the beginning of the BiMap (second values)
        iteratorS beginS(){return iteratorS(m_Reverse_Map.begin());}
        // Get the iterator pointing to the end of the BiMap (second values)
        iteratorS endS(){return iteratorS(m_Reverse_Map.end());}
private:
        map<Key, Value>m_Straight_Map;// Map to store the pairs (first, second)
        map<Value, Key>m_Reverse_Map;// Map to store the pairs (second, first)
};

// Insert a pair (first, second) into the BiMap
template<class Key, class Value>
bool BiMap<Key, Value>::insert(const Key &first, const Value &second)
{
    if (m_Reverse_Map.count(second) == 0)
    {
        if (m_Straight_Map.count(first) != 0)
            // Remove the existing pair with the same first key
            m_Reverse_Map.erase(m_Straight_Map[first]);
        // Insert the pair (first, second) into the straight map
        m_Straight_Map[first] = second;
        // Insert the pair (second, first) into the reverse map
        m_Reverse_Map[second] = first;
        return true;
    }
    return false;
}

// Insert a pair (second, first) into the BiMap
template<class Key, class Value>
bool BiMap<Key, Value>::insert(const Value &second, const Key &first)
{
    if (m_Straight_Map.count(first) == 0)
    {
        if (m_Reverse_Map.count(second) != 0)
            // Remove the existing pair with the same second value
            m_Straight_Map.erase(m_Reverse_Map[second]);
        // Insert the pair (second, first) into the reverse map
        m_Reverse_Map[second] = first;
        // Insert the pair (first, second) into the straight map
        m_Straight_Map[first] = second;
        return true;
    }
    return false;
}

// Erase the pair with the specified first key
template<class Key, class Value>
bool BiMap<Key, Value>::erase(const Key &first)
{
    if (m_Straight_Map.count(first) != 0)
    {
        // Erase the pair from the reverse map
        m_Reverse_Map.erase(m_Straight_Map[first]);
        // Erase the pair from the straight map
        m_Straight_Map.erase(first);
        return true;
    }
    return false;
}

// Erase the pair with the specified second value
template<class Key, class Value>
bool BiMap<Key, Value>::erase(const Value &second)
{
    if (m_Reverse_Map.count(second) != 0)
    {
        // Erase the pair from the straight map
        m_Straight_Map.erase(m_Reverse_Map[second]);
        // Erase the pair from the reverse map
        m_Reverse_Map.erase(second);
        return true;
    }
    return false;
}

// Access the value associated with the given first key
template<class Key, class Value>
Value BiMap<Key, Value>::operator[](const Key &first)
{
    // Find the iterator pointing to the pair with the specified first key
    typename map<Key, Value>::iterator it = m_Straight_Map.find(first);
    // If the pair is found
    if (it != m_Straight_Map.end())
        // Return the value associated with the first key
        return it->second;
    // Return a default value if the pair is not found
    return Value();
}

// Access the key associated with the given second value
template<class Key, class Value>
Key BiMap<Key, Value>::operator[](const Value &second)
{
    // Find the iterator pointing to the pair with the specified second value
    typename map<Value, Key>::iterator it = m_Reverse_Map.find(second);
    // If the pair is found
    if (it != m_Reverse_Map.end())
        // Return the key associated with the second value
        return it->second;
    // Return a default key if the pair is not found
    return Key();
}

// Get the size of the BiMap
template<class Key, class Value>
int BiMap<Key, Value>::size() const
{
    // Return the size of the straight map
    return m_Straight_Map.size();
}

// Sort the BiMap by city (first keys) and print it to the outputFile
template<class Key, class Value>
void BiMap<Key, Value>::sortByCityAndPrint(fstream& outputFile)
{
    // Print "empty" if the straight map is empty
    if (m_Straight_Map.empty())
    {
        outputFile << "empty" << std::endl;
        return;
    }

    // Create a new map to store the sorted pairs by city
    map<Key, Value> sortedCities;

    // Insert each pair from the straight map into the sorted map
    for (const auto& pair : m_Straight_Map)
        sortedCities.insert(pair);

    // Print each city (first key) to the outputFile
    for (const auto& pair : sortedCities)
        outputFile << pair.first;
}

// Sort the BiMap by representation (second values) and print it to the outputFile
template<class Key, class Value>
void BiMap<Key, Value>::sortByRepAndPrint(fstream& outputFile)
{
    // Print "empty" if the reverse map is empty
    if (m_Reverse_Map.empty()) {
        outputFile << "empty" << std::endl;
        return;
    }

    // Create a new map to store the sorted pairs by representation
    map<Value, Key> sortedCities;

    // Insert each pair from the reverse map into the sorted map
    for (const auto& pair : m_Reverse_Map)
        sortedCities.insert(pair);

    // Print each representation (second value) to the outputFile
    for (const auto& pair : sortedCities)
        outputFile << pair.first << std::endl;
}
#endif //SEMESTERB_TASK5_BIMAP_H
