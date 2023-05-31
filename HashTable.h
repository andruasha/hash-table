#ifndef LAB2_1_HASHTABLE_H
#define LAB2_1_HASHTABLE_H

#include <algorithm>
#include <forward_list>
#include <vector>
#include <fstream>


template<class Type, class Hasher = std::hash<Type>>
class HashTable {
    friend class MainWindow;
public:
    HashTable() = default;

    HashTable(const HashTable &other_) = default;

    ~HashTable() = default;

    void clear();

    size_t size() const;

    bool unoccupied() const;

    bool isHere(const Type &key) const;

    bool operator==(const HashTable &otherTable) const;

    HashTable &operator<<(const Type &key);

    size_t operator[](const Type &key) const;

    void erase(const Type &key);

    void writeToFile(const std::string &fileName) const;

    void readFromFile(const std::string &fileName);

    int finding(const int &number) const;

private:
    size_t index(const Type &key) const;

    bool inc(size_t idx, const Type &key);

    Hasher hasher_{Hasher()};
    std::vector<std::forward_list<std::pair<Type, size_t>>> containers_{999};
    size_t size_{0};
};


template<class Type, class Hasher>
size_t HashTable<Type, Hasher>::index(const Type &key) const {
    return hasher_(key) % containers_.size();
}


template<class Type, class Hasher>
bool HashTable<Type, Hasher>::inc(size_t idx, const Type &key) {
    for (auto iter = containers_[idx].begin(); iter != containers_[idx].end(); iter++) {
        auto &[key_, val_] = *iter;
        if (key_ == key) {
            val_++;
            return true;
        }
    }
    return false;
}


template<class Type, class Hasher>
void HashTable<Type, Hasher>::clear() {
    size_t numContainers = containers_.size();
    containers_.clear();
    containers_.resize(numContainers);
    size_ = 0;
}


template<class Type, class Hasher>
size_t HashTable<Type, Hasher>::size() const {
    return size_;
}


template<class Type, class Hasher>
bool HashTable<Type, Hasher>::unoccupied() const {
    return (size_ == 0);
}


template<class Type, class Hasher>
bool HashTable<Type, Hasher>::isHere(const Type &key) const {
    size_t idx = index(key);
    for (auto iter = containers_[idx].begin(); iter != containers_[idx].end(); iter++) {
        if (iter->first == key) {
            return true;
        }
        else {
            return false;
        }
    }
}

template<class Type, class Hasher>
bool HashTable<Type, Hasher>::operator==(const HashTable &otherTable) const {
    if (containers_.size() != otherTable.containers_.size()) {
        return false;
    }
    for (auto iterFirst = containers_.begin(), iterSecond = otherTable.containers_.begin();
         iterFirst != containers_.end() && iterSecond != otherTable.containers_.end();
         iterFirst++, iterSecond++) {

        if (!std::is_permutation(iterFirst->begin(), iterFirst->end(), iterSecond->begin(), iterSecond->end())) {
            return false;
        }
    }
    return true;
}


template<class Type, class Hasher>
HashTable<Type, Hasher> &HashTable<Type, Hasher>::operator<<(const Type &key) {
    size_t idx = index(key);
    if (!inc(idx, key)) {
        containers_[idx].emplace_front(std::make_pair(key, 1));
        size_++;
    }
    return *this;
}


template<class Type, class Hasher>
size_t HashTable<Type, Hasher>::operator[](const Type &key) const {
    size_t idx = index(key);
    for (auto iter = containers_[idx].begin(); iter != containers_[idx].end(); iter++) {
        const auto &[key_, val_] = *iter;
        if (key_ == key) {
            return val_;
        }
    }
    throw std::runtime_error("Key not found.");
}

template<class Type, class Hasher>
void HashTable<Type, Hasher>::erase(const Type &key) {
    if (!isHere(key)) {
        return;
    }
    size_t idx = index(key);
    auto it = containers_[idx].begin();
    if (it->first == key) {
        containers_[idx].pop_front();
        size_--;
        return;
    } else {
        it++;
        for (auto itPrev = containers_[idx].begin(); it != containers_[idx].end(); it++, itPrev++) {
            if (it->first == key) {
                containers_[idx].erase_after(itPrev);
                size_--;
                return;
            }
        }
    }
}


template<class Type, class Hasher>
void HashTable<Type, Hasher>::writeToFile(const std::string &fileName) const {
    std::ofstream file;
    file.open(fileName);
    for (auto cntrs = containers_.begin(); cntrs != containers_.end(); cntrs++) {
        const auto &container = *cntrs;
        for (auto pairs = container.begin(); pairs != container.end(); pairs++) {
            const auto &[key_,val_] = *pairs;
            file << key_ << " -> " << val_ << "\n";
        }
    }
    file.close();
}


template<class Type, class Hasher>
void HashTable<Type, Hasher>::readFromFile(const std::string &fileName) {
    clear();
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("File not found");
    }
    std::pair<Type, size_t> newValue;
    while (file >> newValue.first) {
        file.ignore(3);
        file >> newValue.second;
        for (unsigned i = 0; i < newValue.second; i++) {
            operator<<(newValue.first);
        }
    }
    file.close();
}

template<class Type, class Hasher>
int HashTable<Type, Hasher>::finding(const int &number) const{
    int result = 0;
    for (auto cts = containers_.begin(); cts != containers_.end(); cts++) {
        const auto &container = *cts;
        for (auto prs = container.begin(); prs != container.end(); prs++) {
            const auto &[key_, val_] = *prs;
            if (val_ >= number)
                result++;
        }
    }
    if (result != 0)
        return result;
    else
        throw std::runtime_error("No such keys");
}


#endif //LAB2_1_HASHTABLE_H

