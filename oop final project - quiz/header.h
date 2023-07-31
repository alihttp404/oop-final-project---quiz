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

void setText(string& text, int minTextLength) // userden stringlere min. simvol sayi ile input almaq ucun
{
	while (true)
	{
		try
		{
			getline(cin, text);
			if (text.size() >= minTextLength) break;
			else 
			{
				string msg = "Sual minimum " + to_string(minTextLength) + " simvol olmalidir";
				throw Exception(msg, __FILE__, __DATE__, __LINE__);
			}
		}
		catch (Exception& ex) { cout << ex.what() << "\n\n\n"; }
	}
}

class Question;
void setCorrect(int option, Question* question);

class Question
{
private:
	string _text;
	pair<string, bool> _ans1; // bool cavabin duz olub olmadigini gosterir
	pair<string, bool> _ans2;
	pair<string, bool> _ans3;
	pair<string, bool> _ans4;

public:
	const string getText() { return _text; }
	const pair<string, bool> getAns1() { return _ans1; }
	const pair<string, bool> getAns2() { return _ans2; }
	const pair<string, bool> getAns3() { return _ans3; }
	const pair<string, bool> getAns4() { return _ans4; }

	void setAns(pair<string, bool>& destination, pair<string, bool> source) 
	{
		destination.first = source.first;
		destination.second = source.second;
	}
	void setText(string text) { _text = text; }

	Question() = default;
	Question(string text) : Question() { setText(text); }
	Question(string text, pair<string, bool> ans1, pair<string, bool> ans2, pair<string, bool> ans3, pair<string, bool> ans4)
	{
		setText(text);
		setAns(_ans1, ans1);
		setAns(_ans2, ans2);
		setAns(_ans3, ans3);
		setAns(_ans4, ans4);
	}
	friend void setCorrect(int option, Question* question);
};

void setCorrect(int option, Question* question) // cavabin duzgun olub olmadigini teyin edir
{
	if (!option) question->_ans1.second = true;
	else if (option == 1) question->_ans2.second = true;
	else if (option == 2) question->_ans3.second = true;
	else if (option == 3) question->_ans4.second = true;
}

class Quiz
{
private:
	string _name;

public:
	vector<Question*> _questions;

	const string getName() { return _name; }
	vector<Question*> getQuestions() { return _questions; }
	void setName(string name) { _name = name; }
	void setQuestions(vector<Question*> questions) { _questions = questions; }

	Quiz() = default;
	Quiz(string name) : Quiz() { setName(name); }
	Quiz(string name, vector<Question*> questions) : Quiz() { setName(name); setQuestions(questions); }

	void save()
	{
		ofstream file(_name + ".txt", ios::out);
		if (!file)
		{
			cerr << "Error: Could not open the file for writing." << endl;
			return;
		}

		for (Question* question : _questions)
		{
			file << "Question: " << question->getText() << endl;

			file << "Answers:" << endl;
			file << "1. " << question->getAns1().first << " - " << (question->getAns1().second ? "1" : "0") << endl;
			file << "2. " << question->getAns2().first << " - " << (question->getAns2().second ? "1" : "0") << endl;
			file << "3. " << question->getAns3().first << " - " << (question->getAns3().second ? "1" : "0") << endl;
			file << "4. " << question->getAns4().first << " - " << (question->getAns4().second ? "1" : "0") << endl;

			file << endl;
		}

		file.close();
		cout << "Quiz saved successfully!" << endl;
	}
};