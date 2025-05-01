//Converter.h

#pragma once

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using namespace std;
using json = nlohmann::json;

class ConverterJSON
{
private:
	
	const string config_path = "ConverterJSON/config.json";
	const string requests_path = "ConverterJSON/request.json";
	const string answers_path = "ConverterJSON/answers.json";

	string request_id = "request";
	string word;
	
	ifstream file_i;
	ofstream file_o;
	
	json dict;
	
	int max_responses{};
	
	vector<string> config_file;
	vector<string> config_text;
	vector<string> requests_file;
	vector<pair<int, float>> requests_answers;

public:
	ConverterJSON() = default;

	vector<string> GetTextDocuments(); 

	int GetResponsesLimit();

	vector<string> GetRequests();

	void putAnswers(vector<vector<pair<int, float>>> answers);
};


