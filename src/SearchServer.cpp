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

        istringstream iss(query);
        while (iss >> word)
        {
            words.push_back(word);
        }

        
        set<string> unique_words(words.begin(), words.end());
        words.assign(unique_words.begin(), unique_words.end());

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
            if (max_freq > 0) rank = float(it->second) / max_freq;

            ranked.push_back({ it->first, rank });
        }

        sort(ranked.begin(), ranked.end(), [](const auto& a, const auto& b)
        {
            return b.rank < a.rank;
        });

        int limit = file_recording.GetResponsesLimit();

        if (ranked.size() > limit)
        {
            ranked.resize(limit);
        }

        all_results.push_back(ranked);

        query_answers.clear();
        for (int i = 0; i < ranked.size(); ++i)
        {
            query_answers.push_back({ ranked[i].doc_id, ranked[i].rank });
        }

        file_recording.putAnswers({ query_answers });
    }

    return all_results;
}
