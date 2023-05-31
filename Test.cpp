#include <string>
#include <cassert>
#include <iostream>
#include "Test.h"


std::string Test() {
    HashTable<std::string> collection1;
    assert(collection1.size() == 0);

    // Тестирование метода удаления всех значений коллекции.
    HashTable<std::string> collection2;
    collection2 << "item";
    collection2.clear();
    assert(collection2 == collection1);

    // Тестирование методов записи в файл и чтения из файла.
    HashTable<std::string> collection3;
    collection3 << "item";
    collection3 << "value";
    collection3 << "value";
    collection3.writeToFile("D:/result.txt");
    HashTable<std::string> collection4;
    collection4.readFromFile("D:/result.txt");
    assert(collection4 == collection3);

    // Тестирование функции сравнения двух коллекций.
    HashTable<std::string> collection5;
    collection5 << "value";
    HashTable<std::string> collection6(collection5);
    collection5 << "value";
    assert(!(collection5 == collection6));

    // Тестирование метода добавления ключа в коллекцию.
    HashTable<std::string> collection7;
    collection7 << "value";
    HashTable<std::string> collection8(collection7);
    size_t originalSize, receivedSize;
    originalSize = collection7.size();
    collection8 << "other";
    receivedSize = collection8.size();
    assert(originalSize == receivedSize-1);

    // Тестирование метода добавления имеющегося ключа в коллекцию.
    HashTable<std::string> collection9;
    collection9 << "value";
    HashTable<std::string> collection10(collection9);
    size_t originalNumber, receivedNumber;
    originalSize = collection9.size();
    originalNumber = collection9["value"];
    collection10 << "value";
    receivedSize = collection10.size();
    receivedNumber = collection10["value"];
    assert((originalSize == receivedSize) && (originalNumber == receivedNumber-1));

    // Тестирование метода наличия ключа в коллекции.
    HashTable<std::string> collection11;
    collection11 << "value";
    assert(collection11.isHere("value"));

    // Тестирование метода возвращающего значение ключа.
    HashTable<std::string> collection12;
    collection12 << "value";
    assert(collection12["value"] == 1);

    // Тестирование функции удаления элементов.
    HashTable<std::string> collection13;
    collection13 << "value";
    collection13 << "item";
    originalSize = collection13.size();
    collection13.erase("value");
    receivedSize = collection13.size();
    assert(originalSize != receivedSize);

    originalSize = collection13.size();
    collection13.erase("nothing");
    receivedSize = collection13.size();
    assert(originalSize == receivedSize);

    // Тестирование метода наличия ключа в коллекции.
    HashTable<std::string> collection14;
    collection14 << "value";
    assert(collection14.isHere("value"));
    assert(!(collection14.isHere("nothing")));


    return "All tests passed successfully";
}
