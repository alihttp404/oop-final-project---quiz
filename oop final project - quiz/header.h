#pragma once

class Question
{
private:
	int a;
	string _text;
	vector<pair<string, bool>>_answers; // bool cavabin duz olub olmadigini gosterir

public:
	const string getText() { cout << _text << endl; }
	const vector<pair<string, bool>> getAnswers() { return _answers; }

	void setText(string text)
	{
		if (text.size() > 6) _text = text;
		else throw "Question body must be at least 6 characters";
	}
};