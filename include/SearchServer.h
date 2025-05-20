//SearchServer.h

#pragma once

#include "include/InvertedIndex.h"
#include <algorithm>
#include "Converter.h"
#include <set>

using namespace std;

struct RelativeIndex 
{
	size_t doc_id;
	float rank;
	bool operator ==(const RelativeIndex& other) const 
	{
		return (doc_id == other.doc_id && rank == other.rank);
	}
};

class SearchServer 
{
private:
	InvertedIndex _index;
	ConverterJSON file_recording;

	vector<string> words;
	string word;

	map<size_t, size_t> doc_freq;

	vector<RelativeIndex> ranked;
	vector<pair<int, float>> query_answers;
	vector<vector<RelativeIndex>> all_results;

	size_t max_freq;
public:
	
	SearchServer(InvertedIndex& idx) : _index(idx) {};

	vector<vector<RelativeIndex>> search(const vector<string>& queries_input);

};
