/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);
        //Initialize a map for each file, iterate through word vector and add to map
        map<string, unsigned int> wmap;
        for (std::vector<string>::iterator it = words.begin(); it != words.end(); ++it){
        	  if (wmap.find(*it) == wmap.end()){
        	  		wmap[*it] = 1;		//set to 1
        	  }
        	  else{		//increase frequency
        	  		wmap[*it] ++;
        	  }
        }
        file_word_maps[i] = wmap;	//set current word map to file-specific map
    }
}

void CommonWords::init_common()
{	//maps a word to the number of documents the word appears in
	for (std::vector<map<string, unsigned int>>::iterator mapit = file_word_maps.begin(); mapit != file_word_maps.end(); ++mapit){			//map iterations
		for (map<string, unsigned int>::iterator wit = mapit->begin(); wit != mapit->end(); ++wit){	//word iterations
			if (common.find(wit->first) == common.end()){
				common[wit->first] = 1;
			}
			else{
				common[wit->first] ++;
			}
		}
	}
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    //iterate through common
    for (map<string, unsigned int>::const_iterator cit = common.begin(); cit != common.end(); ++cit){
    	if (file_word_maps.size() <= cit->second){		//if file number is same as common val
			unsigned int fileswword = 0;		//counter
			//iterate through each map
			for (vector<map<string, unsigned int>>::const_iterator mit = file_word_maps.begin(); mit != file_word_maps.end(); ++mit){
				if (mit->at(cit->first) >= n){	//if it happens n or more times
					fileswword++;			//increase counter
				}
			}
			if (fileswword >= file_word_maps.size()){	//compare counter to file #
				//cout<<cit->first<<endl;
				out.push_back(cit->first);					//push that shit
			}
    	}
    }

    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
