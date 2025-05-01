//SearchServer.cpp

#include "include/SearchServer.h"

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries)
{

    for (int q = 0; q < queries.size(); ++q)
    {
        string query = queries[q];
        words.clear();
        word.clear();
        doc_freq.clear();
        ranked.clear();
        max_freq = 0;

        for (int i = 0; i < query.size(); ++i)
        {
            char c = query[i];
            if (c == ' ')
            {
                if (!word.empty()) words.push_back(word);
                word.clear();
            }
            else
            {
                word += c;
            }
        }
        words.push_back(word);

       
        for (int i = 0; i < words.size(); ++i)
        {
            for (int j = i + 1; j < words.size(); )
            {
                if (words[i] == words[j]) words.erase(words.begin() + j);
                else ++j;
            }
        }

        for (int i = 0; i < words.size(); ++i)
        {
            vector<Entry> entries = _index.GetWordCount(words[i]);
            for (int j = 0; j < entries.size(); ++j)
            {
                doc_freq[entries[j].doc_id] += entries[j].count;
            }
        }

        for (auto it = doc_freq.begin(); it != doc_freq.end(); ++it)
        {
            if (it->second > max_freq) max_freq = it->second;
        }

        for (auto it = doc_freq.begin(); it != doc_freq.end(); ++it)
        {
            float rank = 0;
            if (max_freq > 0) rank = (float)it->second / max_freq;

            ranked.push_back({ it->first, rank });
        }

      
        sort(ranked.begin(), ranked.end(), [](RelativeIndex a, RelativeIndex b)
        {
            if (a.rank != b.rank) return a.rank > b.rank;
                return a.doc_id < b.doc_id;
        });

        while (ranked.size() > 5)
        {
            ranked.pop_back();
        }

        all_results.push_back(ranked);

        for (int i = 0; i < ranked.size(); ++i)
        {
            query_answers.push_back({ ranked[i].doc_id, ranked[i].rank });
        }

        file_recording.putAnswers({ query_answers });
    }

    return all_results; 
}