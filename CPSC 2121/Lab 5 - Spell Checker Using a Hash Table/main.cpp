/*
* Name: Kenny Sun
* Date Submitted: 2/29/2024
* Lab Section: CPSC 2121-003
* Assignment Name: Lab 5 - Spell Checker Using a Hash Table
*/

#include "stringset.h"
#include <iostream>
#include <fstream>

void testStringset(Stringset& words);
void loadStringset(Stringset& words, string filename);
vector<string> spellcheck(const Stringset& words, string word);

/*
int main()
{
Stringset wordlist;
testStringset(wordlist);
return 0;
}
*/

void testStringset(Stringset& words)
{
  string choice;
  string word;
  do
  {
    cout << "I: insert word" << endl;
    cout << "F: find word" << endl;
    cout << "R: remove word" << endl;
    cout << "P: print words in stringset" << endl;
    cout << "Q: quit" << endl;
    cin >> choice;
    switch (choice[0])
    {
    case 'I':
    case 'i':
      cout << "Enter word to insert: ";
      cin >> word;
      words.insert(word);
      break;
    case 'F':
    case 'f':
      cout << "Enter word to find: ";
      cin >> word;
      if (words.find(word))
      {
        cout << word << " in stringset" << endl;
      }
      else
      {
        cout << word << " not in stringset" << endl;
      }
      break;
    case 'R':
    case 'r':
      cout << "Enter word to remove: ";
      cin >> word;
      words.remove(word);
      break;
    case 'P':
    case 'p':
      vector<list<string>> t = words.getTable();
      int numWords = words.getNumElems();
      int tSize = words.getSize();
      for(int i=0; i<tSize; ++i)
      {
        list<string>::iterator pos;
        for (pos = t[i].begin(); pos != t[i].end(); ++pos)
        {
          cout << *pos << endl;
        }
      }
      cout << "Words: " << numWords << endl;
    }
  } while (choice[0] != 'Q' && choice[0] != 'q');
}

/* loadStringset */
//Adds all the words from a file to a stringset
void loadStringset(Stringset& words, string filename)
{
  //Creates an ifstraem object, opens the file, and input validates
  ifstream inputFile;
  inputFile.open(filename);
  if(!inputFile.fail())
  {  
    //Iterate through through the entire file and save the word into the hash table
    string word;
    while(inputFile >> word)
    {
      words.insert(word);
    }
  }
  inputFile.close();
}

/* spellCheck */
//Returns a vector of every version of a given word that's one letter off
//from a word in a string set
vector<string> spellcheck(const Stringset& words, string word)
{
  //Initialization of variable and setting word to lower case
  vector<string> oneLetterOff;
  for(int i = 0; i < word.length(); i ++)
  {
    word[i] = tolower(word[i]);
  }

  //Save the original word word
  string startingWord = word;

  //For each character in word
  for(int i = 0; i < word.length(); i ++)
  {
    //Reset the word and save the initial character
    word = startingWord;
    int initialCharacter = static_cast<int>(word[i]);

    //For each letter there is
    for(int j = 97; j <= 122; j ++)
    {
      //If the letter is not the initial character
      if(j != initialCharacter)
      {
        //Change it and find it in the words string set
        word[i] = static_cast<char>(j);
        if(words.find(word))
        {
          //If it's in the word string set, add it to the return vector
          oneLetterOff.push_back(word);
        }
      }
    }
  }
  return oneLetterOff;
}