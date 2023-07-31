#pragma once

class Exception : public exception
{
	string _message;
	string _file;
	string _date;
	string _time;
	int _line;
public:
	Exception() : _message(), _file(), _date(), _time(), _line() {}

	Exception(string message, string file, string date, int line) : exception(message.c_str())
	{
		_file = file;
		_date = date;
		_line = line;

		time_t currentTime = time(nullptr);
		_time = ctime(&currentTime);

		_message = "Message: " + string(exception::what())
			+ "\nFile: " + _file
			+ "\nDate: " + _date
			+ "\nTime: " + _time
			+ "\nLine: " + to_string(_line);
	}

	char const* what() const override
	{
		return _message.c_str();
	}
};

class Question
{
private:
	string _text;
	pair<string, bool> _ans1; // bool cavabin duz olub olmadigini gosterir
	pair<string, bool> _ans2;
	pair<string, bool> _ans3;
	pair<string, bool> _ans4;

public:
	const string getText() { cout << _text << endl; }
	const pair<string, bool> getAns1() { return _ans1; }
	const pair<string, bool> getAns2() { return _ans2; }
	const pair<string, bool> getAns3() { return _ans3; }
	const pair<string, bool> getAns4() { return _ans4; }

	void setText(string text)
	{
		if (text.size() > 6) _text = text;
		else throw "Question body must be at least 6 characters";
	}
};