#pragma once

#include <iostream>
#include <vector>

using namespace std;

class cls_string
{
private:
	string _value;

public:
	cls_string()
	{
		_value = "";
	}

	cls_string(string value)
	{
		_value = value;
	}

	void set_string(string value)
	{
		_value = value;
	}

	string read_string()
	{
		return _value;
	}

	__declspec(property(get = read_string, put = set_string)) string value;

	static short length(string S1)
	{
		return S1.length();
	};

	short length()
	{
		return length(_value);
	}

	static short count_words(string S1)
	{
		string delim = " ";  
		short Counter = 0;
		short pos = 0;
		string sWord;  
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);  
			if (sWord != "")
			{
				Counter++;
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			Counter++;
		}
		return Counter;
	}

	short count_words()
	{
		return count_words(_value);
	}

	static string upper_first_letter_of_each_word(string S1)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}
			isFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}

	void upper_first_letter_of_each_word()
	{
		_value = upper_first_letter_of_each_word(_value);
	}

	static string lower_first_letter_of_each_word(string S1)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ' && isFirstLetter)
			{
				S1[i] = tolower(S1[i]);

			}
			isFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}

	void lower_first_letter_of_each_word()
	{
		_value = lower_first_letter_of_each_word(_value);
	}

	static string upper_all_string(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = toupper(S1[i]);
		}
		return S1;
	}

	void upper_all_string()
	{
		_value = upper_all_string(_value);
	}

	static string lower_all_string(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = tolower(S1[i]);
		}
		return S1;
	}

	void lower_all_string()
	{
		_value = lower_all_string(_value);
	}

	static char invert_letter_case(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static string invert_all_letters_case(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			S1[i] = invert_letter_case(S1[i]);
		}
		return S1;
	}

	void invert_all_letters_case()
	{
		_value = invert_all_letters_case(_value);
	}

	enum en_what_to_count { small_letters = 0, capital_letters = 1, all = 3 };

	static short count_letters(string S1, en_what_to_count what_to_count = en_what_to_count::all)
	{
		if (what_to_count == en_what_to_count::all)
		{
			return S1.length();
		}
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (what_to_count == en_what_to_count::capital_letters && isupper(S1[i]))
				Counter++;
			if (what_to_count == en_what_to_count::small_letters && islower(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short count_letters(en_what_to_count what_to_count = en_what_to_count::all)
	{
		return count_letters(_value, what_to_count);
	}

	static short count_capital_letters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (isupper(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short count_capital_letters()
	{
		return count_capital_letters(_value);
	}

	static short count_small_letters(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (islower(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short count_small_letters()
	{
		return count_small_letters(_value);
	}

	static short count_specific_letter(string S1, char Letter, bool match_case = true)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (match_case)
			{
				if (S1[i] == Letter)
					Counter++;
			}
			else
			{
				if (tolower(S1[i]) == tolower(Letter))
					Counter++;
			}
		}
		return Counter;
	}

	short count_specific_letter(char Letter, bool match_case = true)
	{
		return count_specific_letter(_value, Letter, match_case);
	}

	static bool is_vowel(char Ch1)
	{
		Ch1 = tolower(Ch1);
		return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
	}

	static short count_vowels(string S1)
	{
		short Counter = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (is_vowel(S1[i]))
				Counter++;
		}
		return Counter;
	}

	short count_vowels()
	{
		return count_vowels(_value);
	}

	static vector <string> split(string S1, string Delim)
	{
		vector <string> vString;
		short pos = 0;
		string sWord;  
		while ((pos = S1.find(Delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			vString.push_back(sWord);
			S1.erase(0, pos + Delim.length());
		}
		if (S1 != "")
		{
			vString.push_back(S1);
		}
		return vString;
	}

	vector <string> split(string Delim)
	{
		return split(_value, Delim);
	}

	static string trim_left(string S1)
	{
		for (short i = 0; i < S1.length(); i++)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(i, S1.length() - i);
			}
		}
		return "";
	}

	void trim_left()
	{
		_value = trim_left(_value);
	}

	static string trim_right(string S1)
	{
		for (short i = S1.length() - 1; i >= 0; i--)
		{
			if (S1[i] != ' ')
			{
				return S1.substr(0, i + 1);
			}
		}
		return "";
	}

	void trim_right()
	{
		_value = trim_right(_value);
	}

	static string trim(string S1)
	{
		return (trim_left(trim_right(S1)));
	}

	void trim()
	{
		_value = trim(_value);
	}

	static string join_string(vector <string> vString, string Delim)
	{
		string S1 = "";
		for (string& s : vString)
		{
			S1 = S1 + s + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}

	static string join_string(string arrString[], short Length, string Delim)
	{
		string S1 = "";
		for (short i = 0; i < Length; i++)
		{
			S1 = S1 + arrString[i] + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}

	static string reverse_words_in_string(string S1)
	{
		vector <string> vString;
		string S2 = "";
		vString = split(S1, " ");
		vector<string>::iterator iter = vString.end();
		while (iter != vString.begin())
		{
			--iter;
			S2 += *iter + " ";
		}
		S2 = S2.substr(0, S2.length() - 1);
		return S2;
	}

	void reverse_words_in_string()
	{
		_value = reverse_words_in_string(_value);
	}

	static string replace_word(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
	{
		vector<string> vString = split(S1, " ");
		for (string& s : vString)
		{
			if (MatchCase)
			{
				if (s == StringToReplace)
				{
					s = sRepalceTo;
				}
			}
			else
			{
				if (lower_all_string(s) == lower_all_string(StringToReplace))
				{
					s = sRepalceTo;
				}
			}
		}
		return join_string(vString, " ");
	}

	string replace_word(string StringToReplace, string sRepalceTo)
	{
		return replace_word(_value, StringToReplace, sRepalceTo);
	}

	static string remove_punctuations(string S1)
	{
		string S2 = "";
		for (short i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}

	void remove_punctuations()
	{
		_value = remove_punctuations(_value);
	}
};