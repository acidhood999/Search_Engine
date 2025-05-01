//InvertedIndex.h

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Entry
{
	size_t doc_id, count;

	bool operator ==(const Entry& other) const
	{
		return (doc_id == other.doc_id &&
			count == other.count);
	}
};


class InvertedIndex
{
private:
	vector<string> docs; 
	map<string, vector<Entry>> freq_dictionary;

	string word;
	 
public:
	InvertedIndex() = default;
	
	void UpdateDocumentBase(vector<string> input_docs);

	vector<Entry> GetWordCount(const string& word);


};

