#pragma once

template <typename T>
class Menu
{
public:
	vector<T> _options;
	Menu() = default;
	Menu(vector<T> options) : _options(options) {}

	void print(int& option)
	{
		system("CLS");
		if (option >= _options.size()) option = 0;
		else if (option < 0) option = _options.size() - 1;

		for (int i = 0; i < _options.size(); i++)
		{
			if (option == i) cout << ">>";
			cout << _options[i] << endl;
		}
	}

	void print(int& option, string optionalMessage)
	{
		system("CLS");
		cout << optionalMessage << endl;
		if (option >= _options.size()) option = 0;
		else if (option < 0) option = _options.size() - 1;

		for (int i = 0; i < _options.size(); i++)
		{
			if (option == i) cout << ">>";
			cout << _options[i] << endl;
		}
	}

	int start()
	{
		int ch = 0;
		int option = 0;

		while (true)
		{
			print(option);

			ch = _getch();
			if (ch == 27 || ch == 10 || ch == 13 || ch == '\n') return option;
			else if (ch == 72)
			{
				option--;
			}
			else if (ch == 80)
			{
				option++;
			}
		}
	}

	int start(string optionalMessage)
	{
		int ch = 0;
		int option = 0;

		while (true)
		{
			print(option, optionalMessage);

			ch = _getch();
			if (ch == 27 || ch == 10 || ch == 13 || ch == '\n') return option;
			else if (ch == 72)
			{
				option--;
			}
			else if (ch == 80)
			{
				option++;
			}
		}
	}
};