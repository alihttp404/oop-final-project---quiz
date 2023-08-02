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
			+ "Line: " + to_string(_line)
			+ "\n\n";
	}

	char const* what() const override
	{
		return _message.c_str();
	}
};
class Quiz;
Quiz loadQuizFromFile(const string& filename);
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
void setCorrect(int option, Question*& question);

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

	Question() : _ans1{ "", false }, _ans2{ "", false }, _ans3{ "", false }, _ans4{ "", false } {}
	Question(string text) : Question() { setText(text); }
	Question(string text, pair<string, bool> ans1, pair<string, bool> ans2, pair<string, bool> ans3, pair<string, bool> ans4)
	{
		setText(text);
		setAns(_ans1, ans1);
		setAns(_ans2, ans2);
		setAns(_ans3, ans3);
		setAns(_ans4, ans4);
	}
	friend void setCorrect(int option, Question*& question);
	friend Quiz loadQuizFromFile(const string& filename);

	friend Question* createQuestion();

	friend ostream& operator<<(ostream& out, Question* q);
};

ostream& operator<<(ostream& out, Question* q)
{
	cout << q->_text << endl;
	cout << "1: " << q->_ans1.first << endl;
	cout << "2: " << q->_ans2.first << endl;
	cout << "3: " << q->_ans3.first << endl;
	cout << "4: " << q->_ans4.first << endl;
	return out;
}

void setCorrect(int option, Question*& question) // cavabin duzgun olub olmadigini teyin edir
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
		try
		{
			if (!file) throw Exception("File could not be opened", __FILE__, __DATE__, __LINE__);
		}
		catch (Exception& ex) { cout << ex.what() << endl; return; }

		for (Question* question : _questions)
		{
			file << "Question: " << question->getText() << endl;

			file << "Answer: " << question->getAns1().first << " - " << (question->getAns1().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns2().first << " - " << (question->getAns2().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns3().first << " - " << (question->getAns3().second ? "1" : "0") << endl;
			file << "Answer: " << question->getAns4().first << " - " << (question->getAns4().second ? "1" : "0") << endl;

			file << endl;
		}

		file.close();
		cout << "Quiz saved" << endl;
	}

	void show()
	{
		cout << "Quiz Name: " << _name << endl;

		int questionNumber = 1;
		for (Question* question : _questions)
		{
			cout << "\nQuestion " << questionNumber << ": " << question->getText() << endl;

			cout << "Answers:" << endl;
			cout << "1. " << question->getAns1().first << endl;
			cout << "2. " << question->getAns2().first << endl;
			cout << "3. " << question->getAns3().first << endl;
			cout << "4. " << question->getAns4().first << endl;

			questionNumber++;
		}
	}
	friend void createQuiz();
};

Quiz loadQuizFromFile(const string& filename)
{
	ifstream file(filename);
	try
	{
		if (!file)
		{
			throw Exception("File could not be opened for loading", __FILE__, __DATE__, __LINE__);
		}
	}
	catch (Exception& ex) { cout << ex.what() << endl; return Quiz(); }

	vector<Question*> questions;
	Quiz quiz(filename.substr(0, filename.size() - 4), questions);
	string line;

	while (getline(file, line))
	{
		if (line.substr(0, 8) == "Question")
		{
			Question* currQuestion = new Question();

			currQuestion->setText(line.substr(10));
			getline(file, line);
			currQuestion->_ans1.first = line.substr(0, line.size()-3);
			currQuestion->_ans1.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans2.first = line.substr(0, line.size() - 3);
			currQuestion->_ans2.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans3.first = line.substr(0, line.size() - 3);
			currQuestion->_ans3.second = (line.substr(line.size() - 1) == "1");

			getline(file, line);
			currQuestion->_ans4.first = line.substr(0, line.size() - 3);
			currQuestion->_ans4.second = (line.substr(line.size() - 1) == "1");

			questions.push_back(currQuestion);
		}
	}

	quiz.setQuestions(questions);
	return quiz;
}

Question* createQuestion()
{
	Question* question = new Question();
	string text, ans1, ans2, ans3, ans4;

	system("CLS");
	cout << "Question: ";
	setText(text, 3);
	question->setText(text);

	cout << "Answer 1: ";
	setText(ans1, 2);
	question->_ans4.first = ans4;

	cout << "Answer 2: ";
	setText(ans2, 2);
	question->_ans4.first = ans4;

	cout << "Answer 3: ";
	setText(ans3, 2);
	question->_ans4.first = ans4;

	cout << "Answer 4: ";
	setText(ans4, 2);
	question->_ans4.first = ans4;

	system("CLS");
	cout << "Select correct answer" << endl;
	cout << question;

	Menu<string> menu(vector<string>{ans1, ans2, ans3, ans4});
	int option = menu.start();
	setCorrect(option, question);

	return question;
}

void createQuiz()
{
	Quiz* quiz = new Quiz();
	string quizName;
	vector<string> options =
	{
		"New",
		"Back",
		"Save"
	};
	Menu<string>* menu = new Menu<string>(options);
	
	system("CLS");
	cout << "Quiz name: ";
	setText(quizName, 2);
	quiz->_name = quizName;

	while (true)
	{
		int option = menu->start();
		if (option == 0)
		{
			quiz->_questions.push_back(createQuestion());
		}
		else if (option == 2) quiz->save();
	}
}