//InvertedIndex.cpp

#include "include/InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(vector<string> input_docs)
{
	docs = input_docs;

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id)
    {
        istringstream text_word(docs[doc_id]);

        map<string, size_t> word_count;

        while (text_word >> word)
        {
            word_count[word] += 1;
        }

        for (auto it = word_count.begin(); it != word_count.end(); ++it)
        {
            auto word = it->first;   
            auto count = it->second;
            freq_dictionary[word].push_back({ doc_id, count });
        }
    }
}

 
vector<Entry> InvertedIndex::GetWordCount(const string& word)
{
	auto it = freq_dictionary.find(word);
	if (it != freq_dictionary.end())
	{
		return it->second;
	}
	return {};
}

