#pragma once

#include <iostream>
#include <string>
#include "cls_date.h"

using namespace std;

class cls_utility
{
public:
    enum en_char_type {
        small_letter, capital_letter,
        digit, mix_chars, special_character
    };

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int random_number(int from, int to)
    {
        int rand_num = rand() % (to - from + 1) + from;
        return rand_num;
    }

    static char get_random_character(en_char_type char_type)
    {
        if (char_type == mix_chars)
        {
            char_type = (en_char_type)random_number(1, 3);
        }
        switch (char_type)
        {
        case en_char_type::small_letter:
        {
            return char(random_number(97, 122));
            break;
        }
        case en_char_type::capital_letter:
        {
            return char(random_number(65, 90));
            break;
        }
        case en_char_type::special_character:
        {
            return char(random_number(33, 47));
            break;
        }
        case en_char_type::digit:
        {
            return char(random_number(48, 57));
            break;
        }
    defualt:
        {
            return char(random_number(65, 90));
            break;
        }
        }
    }

    static string generate_word(en_char_type char_type, short length)
    {
        string word;
        for (int i = 1; i <= length; i++)
        {
            word = word + get_random_character(char_type);
        }
        return word;
    }

    static string generate_key(en_char_type char_type = capital_letter)
    {
        string key = "";
        key = generate_word(char_type, 4) + "-";
        key = key + generate_word(char_type, 4) + "-";
        key = key + generate_word(char_type, 4) + "-";
        key = key + generate_word(char_type, 4);
        return key;
    }

    static void generate_keys(short number_of_keys, en_char_type char_type)
    {
        for (int i = 1; i <= number_of_keys; i++)
        {
            cout << "Key [" << i << "] : ";
            cout << generate_key(char_type) << endl;
        }
    }

    static void fill_array_with_random_numbers(int arr[100], int arr_length, int from, int to)
    {
        for (int i = 0; i < arr_length; i++)
            arr[i] = random_number(from, to);
    }

    static void fill_array_with_random_words(string arr[100], int arr_length, en_char_type char_type, short word_length)
    {
        for (int i = 0; i < arr_length; i++)
            arr[i] = generate_word(char_type, word_length);
    }

    static void fill_array_with_random_keys(string arr[100], int arr_length, en_char_type char_type)
    {
        for (int i = 0; i < arr_length; i++)
            arr[i] = generate_key(char_type);
    }

    static void swap(int& A, int& B)
    {
        int temp;
        temp = A;
        A = B;
        B = temp;
    }

    static void swap(double& A, double& B)
    {
        double temp;
        temp = A;
        A = B;
        B = temp;
    }

    static void swap(bool& A, bool& B)
    {
        bool temp;
        temp = A;
        A = B;
        B = temp;
    }

    static void swap(char& A, char& B)
    {
        char temp;
        temp = A;
        A = B;
        B = temp;
    }

    static void swap(string& A, string& B)
    {
        string temp;
        temp = A;
        A = B;
        B = temp;
    }

    static void swap(cls_date& A, cls_date& B)
    {
        cls_date::swap_dates(A, B);
    }

    static void shuffle_array(int arr[100], int arr_length)
    {
        for (int i = 0; i < arr_length; i++)
        {
            swap(arr[random_number(1, arr_length) - 1], arr[random_number(1, arr_length) - 1]);
        }
    }

    static void shuffle_array(string arr[100], int arr_length)
    {
        for (int i = 0; i < arr_length; i++)
        {
            swap(arr[random_number(1, arr_length) - 1], arr[random_number(1, arr_length) - 1]);
        }
    }

    static string tabs(short number_of_tabs)
    {
        string t = "";
        for (int i = 1; i < number_of_tabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }

    static string encrypt_text(string text, short encryption_key)
    {
        for (int i = 0; i <= text.length(); i++)
        {
            text[i] = char((int)text[i] + encryption_key);
        }
        return text;
    }

    static string decrypt_text(string text, short encryption_key)
    {
        for (int i = 0; i <= text.length(); i++)
        {
            text[i] = char((int)text[i] - encryption_key);
        }
        return text;
    }

    static string convert_number_to_text(long long number)
    {
        string str_number = to_string(number), group_name, text_number;
        short number_of_digits_in_group;
        while (str_number.length() > 0)
        {
            number_of_digits_in_group = str_number.length() % 3;
            if (number_of_digits_in_group == 0) number_of_digits_in_group += 3;
            if (number_of_digits_in_group >= 1)
            {
                switch (str_number[number_of_digits_in_group - 1])
                {
                case '1': group_name = "one "; break;
                case '2': group_name = "two "; break;
                case '3': group_name = "three "; break;
                case '4': group_name = "four "; break;
                case '5': group_name = "five "; break;
                case '6': group_name = "six "; break;
                case '7': group_name = "seven "; break;
                case '8': group_name = "eight "; break;
                case '9': group_name = "nine ";
                }
            }
            if (number_of_digits_in_group >= 2)
            {
                switch (str_number[number_of_digits_in_group - 2])
                {
                case '1':
                    if (group_name == "one ")
                        group_name = "eleven ";
                    else if (group_name == "two ")
                        group_name = "twelve ";
                    else if (group_name == "three ")
                        group_name = "thirteen ";
                    else if (group_name == "four ")
                        group_name = "fourteen ";
                    else if (group_name == "five ")
                        group_name = "fifteen ";
                    else if (group_name == "six ")
                        group_name = "sixteen ";
                    else if (group_name == "seven ")
                        group_name = "seventeen ";
                    else if (group_name == "eight ")
                        group_name = "eighteen ";
                    else if (group_name == "nine ")
                        group_name = "nineteen ";
                    else group_name = "ten "; break;
                case '2': group_name = "twenty " + group_name; break;
                case '3': group_name = "thirty " + group_name; break;
                case '4': group_name = "forty " + group_name; break;
                case '5': group_name = "fifty " + group_name; break;
                case '6': group_name = "sixty " + group_name; break;
                case '7': group_name = "seventy " + group_name; break;
                case '8': group_name = "eighty " + group_name; break;
                case '9': group_name = "ninety " + group_name;
                }
            }
            if (number_of_digits_in_group == 3)
            {
                switch (str_number[number_of_digits_in_group - 3])
                {
                case '1': group_name = "one hundred " + group_name; break;
                case '2': group_name = "two hundreds " + group_name; break;
                case '3': group_name = "three hundreds " + group_name; break;
                case '4': group_name = "four hundreds " + group_name; break;
                case '5': group_name = "five hundreds " + group_name; break;
                case '6': group_name = "six hundreds " + group_name; break;
                case '7': group_name = "seven hundreds " + group_name; break;
                case '8': group_name = "eight hundreds " + group_name; break;
                case '9': group_name = "nine hundreds " + group_name;
                }
            }
            if (12 >= str_number.length() && str_number.length() > 9)
            {
                if (group_name == "one ")
                    group_name += "billion ";
                else group_name += "billions ";
            }
            else if (9 >= str_number.length() && str_number.length() > 6)
            {
                if (group_name == "one ")
                    group_name += "million ";
                else group_name += "millions ";
            }
            else if (6 >= str_number.length() && str_number.length() > 3)
            {
                if (group_name == "one ")
                    group_name += "thousand ";
                else group_name += "thousands ";
            }
            text_number += group_name;
            str_number = str_number.substr(number_of_digits_in_group);
        }
        return text_number;
    }

    static string encrypt_string(string string_input, short key)
    {
        for (char& character : string_input) character += key;
        return string_input;
    }

    static string decrypt_string(string string_input, short key)
    {
        for (char& character : string_input) character -= key;
        return string_input;
    }
};