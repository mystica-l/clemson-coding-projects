/*
* Name: Kenny Sun
* Date Submitted: 2/29/2024
* Lab Section: CPSC 2121-003
* Assignment Name: Lab 5 - Spell Checker Using a Hash Table
*/

#include "stringset.h"
#include <iostream>

Stringset::Stringset() : table(200000), num_elems(0), size(200000) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
  return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
  return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
  return size;
}

/* insert */
//Inserts a word into the string set
void Stringset::insert(string word)
{
	//If the word isn't already in the set
	if(!find(word))
	{
		//And if there's enough room
		if(size <= num_elems)
		{
			rehash();
		}
		//Hash and insert the word
		int index = stringHash(word) % size;
		table[index].push_front(word);
		num_elems++;
	}
}

/* find */
//Returns whether or not a word is in the string set
bool Stringset::find(string word) const
{
	int index = stringHash(word) % size;
	for(string saved : table[index])
	{
		if(saved == word)
		{
			return true;
		}
	}
	return false;
}

/* remove */
//Removes a word from the stringset
void Stringset::remove(string word)
{
	//Hash the word to get the table index, then remove it
	int index = stringHash(word) % size;
	table[index].remove(word);
	num_elems--;
}

/* rehash */
//Rehashes all the values of a string 
void Stringset::rehash()
{
	//Iterates thorgh the entirety of the table and stores it in storage
	vector<string> storage;
	for(int i = 0; i < size; i ++)
	{
		while(!table[i].empty())
		{
			storage.push_back(table[i].back());
			table[i].pop_back();
		}
	}

	//Multiply the size by 2 and expand the hash table
	size *= 2;
	while(table.size() < size)
	{
		list<string> emptyList;
		table.push_back(emptyList);
	}

	//Reinsert all the words
	for(int i = 0; i < storage.size(); i ++)
	{
		int index = stringHash(storage[i]) % size;
		table[index].push_front(storage[i]);
	}
}