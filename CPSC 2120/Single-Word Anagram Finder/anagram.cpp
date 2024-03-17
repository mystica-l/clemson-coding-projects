/*
 * Name: Kenny Sun
 * Date Submitted: 3/14/2024
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

/*
int main()
{
    vector<string> words;
    vector<string> anagrams;
    string inputWord;
    words=loadWordlist("wordlist.txt");
    cout << "Find single-word anagrams for the following word: ";
    cin >> inputWord;
    anagrams = anagram(inputWord, words);
    for (int i=0; i<anagrams.size(); i++)
    {
        cout << anagrams[i] << endl;
    }
    return 0;
}
*/

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

/* anagram */
//Takes in a word and a word list and returns a vector
//With all the words that are an anagram of the input word
vector<string> anagram(string word, vector<string> wordlist)
{
    //map stores all of the data
    unordered_map <string, vector<string>> map;

    //For each word in the word list
    for(string word : wordlist)
    {
        //Create a numCharacters vector storing the number of letters for each letter based on index
        //So having 5 a's means numCharacters[0] = 5
        vector<int> numCharacters(26, 0);
        for(int i = 0; i < word.length(); i ++)
        {
            numCharacters[static_cast<int>(word[i]) - 97]++;
        }
        //Create a key string
        string key = "";
        //For each letter in the alphabet
        for(int i = 0; i < 26; i ++)
        {
            //First add the letter to the key string
            key += static_cast<char> (i + 97);
            //Then the number of times that letter appeared from numCharacters
            stringstream ss;
            ss << numCharacters[i];
            key += ss.str();
        }
        //Output of the key for a word like "baby" should be something like...
        //a1b2c0...x0y1z0

        //If the map has vector in the specificed key...
        //Add in the new word with it's key into the associated vector
        map.at(key).push_back(word);
    }

    //Create a key for the given word by the user such as before
    vector<int> numCharacters(26, 0);
    for(int i = 0; i < word.length(); i ++)
    {
        numCharacters[static_cast<int>(word[i]) - 97]++;
    }
    string key = "";
    for(int i = 0; i < 26; i ++)
    {
        key += static_cast<char> (i + 97);
        stringstream ss;
        ss << numCharacters[i];
        key += ss.str();
    }

    //If there is no vector at the specified key, return an empty vector
    if(map.find(key) == map.end())
    {
        vector<string> empty;
        return empty;
    }
    //Otherwise, return the vector at that key
    else
    {
        return map.at(key);
    }
}