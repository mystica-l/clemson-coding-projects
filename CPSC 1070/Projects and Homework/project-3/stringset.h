/*
* Name: Kenny Sun
* Date Submitted: 2/29/2024
* Lab Section: CPSC 2121-003
* Assignment Name: Lab 5 - Spell Checker Using a Hash Table
*/

#pragma once

#include <string>
#include <vector>
#include <list>
using namespace std;

//Stringset class, do not modify definitions for existing members
class Stringset
{
    private:
        vector<list<string>> table;
        int num_elems;
        int size;
        std::hash<std::string> stringHash;
    public:
        Stringset();
        vector<list<string>> getTable() const;
        int getNumElems() const;
        int getSize() const;
        void insert(string word);
        bool find(string word) const;
        void remove(string word);
        void rehash();
};