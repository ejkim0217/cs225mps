/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
	ifstream wordsFile(filename);
	string word;
	if (wordsFile.is_open()) {
	/* Reads a line from `wordsFile` into `word` until the file ends. */
		while (getline(wordsFile, word)) {
			string srt = word;
			std::sort(srt.begin(), srt.end());
			dict[srt].push_back(word);
		}
	}
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for(std::vector<string>::const_iterator wds = words.begin(); wds != words.end(); ++wds){
    	string word = *wds;
    	std::sort(word.begin(), word.end());
    	dict[word].push_back(*wds);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
	//vector<string> out;
	string srt = word;
	std::sort(srt.begin(),srt.end());
	return (dict.find(srt))->second;
	//return out;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
	vector<vector<string>> out;
	//iterate through map keys
	for (std::map<string, vector<string>>::const_iterator mit = dict.begin(); mit != dict.end(); ++mit){
		int anagrams = (mit->second).size();
		if(anagrams >= 2){	//if two or more elements, push to output vector
			out.push_back(mit->second);
		}
	}
	return out;
}
