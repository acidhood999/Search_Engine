//Converter.cpp

#include "include/Converter.h"

vector<string> ConverterJSON::GetTextDocuments()
{
	file_i.open(config_path);

	if (!file_i.is_open())
	{
		throw runtime_error("config file is missing");
	}

	file_i >> dict;
	file_i.close();

	for (auto path : dict["files"])
	{
		config_file.push_back(path.get<string>());
	}

	for (auto filepath : config_file)
	{
		file_i.open(filepath);
		if (!file_i.is_open())
		{
			cout << "error opening file " << filepath <<endl;
			continue;
		}

		stringstream buffer;
		buffer << file_i.rdbuf();
		config_text.push_back(buffer.str());

		file_i.close();
	}

	return config_text;
}

int ConverterJSON::GetResponsesLimit()
{

	file_i.open(config_path);

	if (!file_i.is_open())
	{
		throw runtime_error("config file is missing");
	}

	file_i >> dict;

	if (dict.contains("config")) 
	{
		max_responses = dict["config"]["max_responses"].get<int>();
	}
	else 
	{
		throw runtime_error("config file is empty");
	}
	
	

	file_i.close();

	return max_responses;
}

vector<string> ConverterJSON::GetRequests()
{
	file_i.open(requests_path);

	if (!file_i.is_open())
	{
		throw runtime_error("request file is missing");
	}

	file_i >> dict;
	file_i.close();

	for (auto path : dict["requests"])
	{
		requests_file.push_back(path.get<string>());
	}

	return requests_file;
	
}

void ConverterJSON::putAnswers(vector<vector<pair<int, float>>> answers) 
{

	for (int i = 0; i < answers.size(); i++)
	{
		json request_r;
		auto result_vector = answers[i];

		ostringstream req_id_stream;
		req_id_stream << "request" << setfill('0') <<setw(3) << (i + 1);
		string request_id = req_id_stream.str();

		request_r["result"] = !result_vector.empty();

		
		if (result_vector.size() > 1) 
		{
			json relevance_a = json::array();
			for (auto [docid, rank] : result_vector) 
			{
				relevance_a.push_back({
					{"docid", docid},
					{"rank", rank}
					});
			}
			request_r["relevance"] = relevance_a;
		}

		output_json["answers"][request_id] = request_r;
	}

	file_o.open(answers_path);
	file_o << setw(4) << output_json <<endl;
	file_o.close();
}
