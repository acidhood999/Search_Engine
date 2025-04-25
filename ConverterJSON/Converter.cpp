//Converter.cpp

#include "Converter.h"

vector<string> ConverterJSON::GetTextDocuments()
{

	file_i.open(config_path);
	
	if (!file_i.is_open())
	{
		cout << "error opening file" << endl;
		return {};
	}
	
	file_i >> dict;
	
	for (auto path : dict["files"])
	{
		config_file.push_back(path.get<string>());
	}
	
	file_i.close();
	
	for (int i{}; i < config_file.size(); ++i)
	{  
		file_i.open(config_file[i]);  
		if (!file_i.is_open())
		{
			cout << "error opening file " << config_file[i] << endl;
			continue;
		}

		while (file_i >> word) 
		{  
			config_text.push_back(word);
		}
		file_i.close();
	}

	return config_text;

}

int ConverterJSON::GetResponsesLimit()
{

	file_i.open(config_path);

	if (!file_i.is_open())
	{
		cout << "error opening file" << endl;
		return {};
	}

	file_i >> dict;

	max_responses = dict["config"]["max_responses"].get<int>();

	file_i.close();

	return max_responses;
}

vector<string> ConverterJSON::GetRequests()
{
	file_i.open(requests_path);

	if (!file_i.is_open())
	{
		cout << "error opening file" << endl;
		return {};
	}

	file_i >> dict;

	
	for (auto path : dict["requests"])
	{
		string request = path.get<string>();
		istringstream word_line(request);
		while (word_line >> word)
		{
			requests_file.push_back(word);
		}
		
	}

	file_i.close();

	return requests_file;
}

void ConverterJSON::putAnswers(vector<vector<pair<int, float>>> answers)
{
	for (int i = 0; i < answers.size(); i++)
	{
		json request_r;
		request_r["result"] = !answers[i].empty();

		if (!answers[i].empty())
		{
			json relevance_a;
			for (int j = 0; j < answers[i].size(); ++j)
			{
				relevance_a.push_back({ {"docid", answers[i][j].first}, {"rank", answers[i][j].second} });
			}
			request_r["relevance"] = relevance_a;
		}
		dict["answers"][request_id + to_string(i + 1)] = request_r;
	}

	file_o.open(answers_path);
	file_o << setw(4) << dict << endl;
	file_o.close();
}
