#pragma once
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <functional>

using std::function;
using std::list;
using std::ostream;
using std::string;
using std::vector;

template <class T>
class HashTable
{
public:
  class KeyValuePair
  {
    string _key;
    T _value;

  public:
    KeyValuePair(string key, T value) : _key(key), _value(value) {}
    string &key()
    {
      return _key;
    }
    T &value()
    {
      return _value;
    }
  };

  class NodeList
  {
    list<KeyValuePair> items;

  public:
    void push_front(string key, T &value)
    {
      items.push_front(KeyValuePair(key, value));
    }
    void push_back(string key, T &value)
    {
      items.push_back(KeyValuePair(key, value));
    }
    typename list<KeyValuePair>::iterator begin()
    {
      return items.begin();
    }
    typename list<KeyValuePair>::iterator end()
    {
      return items.end();
    }
    size_t size()
    {
      return items.size();
    }
  };
  class ValueProxy
  {
    string key;
    size_t index;
    HashTable<T> *hashtable;

    KeyValuePair &findPair() const
    {
      for (KeyValuePair &pair : hashtable->table[index])
      {
        if (pair.key() == key)
        {
          return pair;
        }
      }
      throw std::invalid_argument("'" + key + "' wasn't found in the HashTable.");
    }

  public:
    ValueProxy(string key, HashTable<T> *hashtable)
    {
      this->key = key;
      this->index = hashtable->hash(key);
      this->hashtable = hashtable;
    }

    ValueProxy &operator=(T &value)
    {
      try
      {
        KeyValuePair pair = findPair();
        pair.value() = value;
      }
      catch (const std::invalid_argument &err)
      {
        hashtable->table[index].push_back(key, value);
      }
      return *this;
    }

    ValueProxy &operator=(T value)
    {
      try
      {
        KeyValuePair pair = findPair();
        pair.value() = value;
      }
      catch (const std::invalid_argument &err)
      {
        hashtable->table[index].push_back(key, value);
      }
      return *this;
    }

    ValueProxy &operator=(ValueProxy &proxy)
    {
      KeyValuePair pair = proxy.findPair();
      return operator=(&pair.value());
    }

    operator T()
    {
      KeyValuePair pair = findPair();
      return pair.value();
    }

    friend ostream &operator<<(ostream &out, const ValueProxy &proxy)
    {
      KeyValuePair pair = proxy.findPair();
      out << pair.value();
      return out;
    }
  };

private:
  vector<NodeList> table;
  friend class ValueProxy;

public:
  HashTable(size_t size)
  {
    table = vector<NodeList>(size);
  }
  void forEach(function<void(KeyValuePair &)> fn)
  {
    for (NodeList &list : table)
    {
      for (KeyValuePair &pair : list)
      {
        fn(pair);
      }
    }
  }
  T &operator[](string key) const
  {
    size_t index = hash(key);
    for (KeyValuePair &pair : table[index])
    {
      if (pair.key() == key)
      {
        return pair.value();
      }
    }
    throw std::invalid_argument("'" + key + "' wasn't found in the HashTable.");
  }
  ValueProxy operator[](string key)
  {
    return ValueProxy(key, this);
  }

private:
  size_t hash(string str)
  {
    size_t hash = (size_t)57;
    for (size_t i = 0; i < str.length(); ++i)
    {
      hash = (size_t)19 * hash * (size_t)str.at(i);
    }
    return hash % table.size();
  }
};
