//InvertedIndex.cpp

#include "include/InvertedIndex.h"
#include <thread>
#include <mutex>
#include <algorithm>

mutex freq_dictionary_mutex;

void InvertedIndex::UpdateDocumentBase(vector<string> input_docs) 
{
    docs.clear();
    freq_dictionary.clear();

    docs = input_docs;
    vector<thread> threads;

    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id)
    {
        threads.push_back(thread([this, doc_id]()
        {
            istringstream text_word(docs[doc_id]);
            map<string, size_t> word_count;
            string word;

            
            while (text_word >> word) 
            {
                word_count[word] += 1;
            }

            freq_dictionary_mutex.lock();
            for (auto it = word_count.begin(); it != word_count.end(); ++it) 
            {
                auto word = it->first;
                auto count = it->second;
                freq_dictionary[word].push_back({ doc_id, count });
            }
            freq_dictionary_mutex.unlock();
        }));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    for (auto it = freq_dictionary.begin(); it != freq_dictionary.end(); ++it)
    {
        sort(it->second.begin(), it->second.end(), [](auto a, auto b) { return a.doc_id < b.doc_id; });
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
