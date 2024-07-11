#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class cls_date
{
private:
	short _day, _month, _year;

public:
	cls_date()
	{
		*this = get_system_date();
	}

	cls_date(string string_date)
	{
		*this = from_string_to_date(string_date);
	}

	cls_date(short day, short month, short year)
	{
		_day = day;
		_month = month;
		_year = year;
	}

	cls_date(short day_order, short year)
	{
		*this = date_from_the_beginning_of_year(year, day_order);
	}

	void set_day(short day)
	{
		_day = day;
	}

	short get_day()
	{
		return _day;
	}

	__declspec(property(get = get_day, put = set_day)) short day;

	void set_month(short month)
	{
		_month = month;
	}

	short get_month()
	{
		return _month;
	}

	__declspec(property(get = get_month, put = set_month)) short month;

	void set_year(short year)
	{
		_year = year;
	}

	short get_year()
	{
		return _year;
	}

	__declspec(property(get = get_year, put = set_year)) short year;

	static enum en_dates_comparison { before = -1, equal, after };

	static bool is_leap_year(short year)
	{
		return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
	}

	bool is_leap_year()
	{
		return is_leap_year(_year);
	}

	static short days_in_year(short year)
	{
		return is_leap_year(year) ? 366 : 365;
	}

	short days_in_year()
	{
		return days_in_year(_year);
	}

	static short hours_in_year(short year)
	{
		return is_leap_year(year) ? 366 * 24 : 365 * 24;
	}

	short hours_in_year()
	{
		return hours_in_year(_year);
	}

	static int minutes_in_year(short year)
	{
		return is_leap_year(year) ? 366 * 24 * 60 : 365 * 24 * 60;
	}

	int minutes_in_year()
	{
		return minutes_in_year(_year);
	}

	static int seconds_in_year(short year)
	{
		return is_leap_year(year) ? 366 * 24 * 60 * 60 : 365 * 24 * 60 * 60;
	}

	int seconds_in_year()
	{
		return seconds_in_year(_year);
	}

	static short days_in_month(short year, short month)
	{
		if (month < 1 || month > 12) return 0;
		if (month == 2) return is_leap_year(year) ? 29 : 28;
		return (month == 4 || month == 6 || month == 9 || month == 11) ? 30 : 31;
	}

	short days_in_month()
	{
		return days_in_month(_year, _month);
	}

	static short hours_in_month(short year, short month)
	{
		return days_in_month(year, month) * 24;
	}

	short hours_in_month()
	{
		return hours_in_month(_year, _month);
	}

	static int minutes_in_month(short year, short month)
	{
		return days_in_month(year, month) * 24 * 60;
	}

	int minutes_in_month()
	{
		return minutes_in_month(_year, _month);
	}

	static int seconds_in_month(short year, short month)
	{
		return days_in_month(year, month) * 24 * 60 * 60;
	}

	int seconds_in_month()
	{
		return seconds_in_month(_year, _month);
	}

	static short get_day_order(short year, short month, short day)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		return ((day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7);
	}

	static short get_day_order(cls_date date)
	{
		return get_day_order(date.year, date.month, date.day);
	}

	short get_day_order()
	{
		return get_day_order(*this);
	}

	static string get_day_name(short day_order)
	{
		string days[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
		return days[day_order];
	}

	static string get_month_name(short month)
	{
		string months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		return months[month - 1];
	}

	string get_month_name()
	{
		return get_month_name(_month);
	}

	static void show_month_calendar(short year, short month)
	{
		cout << "\n_______________" << get_month_name(month) << "_______________\n";
		cout << "\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n";
		short number_of_days_in_month = days_in_month(year, month);
		short day_order = get_day_order(year, month, 1);
		for (short i = 0; i < day_order; i++)
			cout << "     ";
		for (short i = 1; i <= number_of_days_in_month; i++)
		{
			cout << setw(3) << i << "  ";
			day_order++;
			if (day_order == 7 && i != number_of_days_in_month)
			{
				cout << "\n";
				day_order = 0;
			}
		}
		cout << "\n_________________________________\n";
	}

	void show_month_calendar()
	{
		show_month_calendar(_year, _month);
	}

	static void show_year_calendar(short year)
	{
		cout << "\n_________________________________\n";
		cout << "\n\tCalendar - " << year;
		cout << "\n_________________________________\n";
		for (short month = 1; month <= 12; month++)
			show_month_calendar(year, month);
	}

	void show_year_calendar()
	{
		show_year_calendar(_year);
	}

	static short total_days_from_the_beginning_of_year(short year, short month, short day)
	{
		short total_days = 0;
		for (short i = 1; i < month; i++)
			total_days += days_in_month(year, i);
		total_days += day;
		return total_days;
	}

	short total_days_from_the_beginning_of_year()
	{
		return total_days_from_the_beginning_of_year(_year, _month, _day);
	}

	static cls_date date_from_the_beginning_of_year(short year, short day_order)
	{
		cls_date date;
		short month, day;
		for (month = 1; month <= 12; month++)
		{
			short number_of_days_in_month = days_in_month(year, month);
			if (day_order > number_of_days_in_month)
				day_order -= number_of_days_in_month;
			else
			{
				day = day_order;
				break;
			}
		}
		date.year = year, date.month = month, date.day = day;
		return date;
	}

	void date_from_the_beginning_of_year(short day_order)
	{
		*this = date_from_the_beginning_of_year(_year, day_order);
	}

	static cls_date adding_days_to_date(cls_date date, short added_days)
	{
		short number_of_days_in_month;
		while (true)
		{
			number_of_days_in_month = days_in_month(date.year, date.month);
			if (added_days > number_of_days_in_month)
				added_days -= number_of_days_in_month, date.month++;
			if (date.month == 13)
				date.year++, date.month = 1;
			if (added_days < number_of_days_in_month)
			{
				date.day += added_days;
				if (date.day > number_of_days_in_month)
					date.day -= number_of_days_in_month, date.month++;
				if (date.month == 13)
					date.year++, date.month = 1;
				break;
			}
		}
		return date;
	}

	void adding_days(short added_days)
	{
		*this = adding_days_to_date(*this, added_days);
	}

	static bool is_date1_before_date2(cls_date date1, cls_date date2)
	{
		if (date1.year < date2.year)
			return true;
		else if (date1.year > date2.year)
			return false;
		else
		{
			if (date1.month < date2.month)
				return true;
			else if (date1.month > date2.month)
				return false;
			else
			{
				if (date1.day < date2.day)
					return true;
				else return false;
			}
		}
	}

	bool is_before_date2(cls_date date2)
	{
		return is_date1_before_date2(*this, date2);
	}

	static bool is_date1_equal_date2(cls_date date1, cls_date date2)
	{
		return (date1.year == date2.year && date1.month == date2.month && date1.day == date2.day);
	}

	bool is_equal_date2(cls_date date2)
	{
		return is_date1_equal_date2(*this, date2);
	}

	static bool is_date1_after_date2(cls_date date1, cls_date date2)
	{
		return (!is_date1_before_date2(date1, date2) && !is_date1_equal_date2(date1, date2));
	}

	bool is_after_date2(cls_date date2)
	{
		return is_date1_after_date2(*this, date2);
	}

	static en_dates_comparison compare_two_dates(cls_date date1, cls_date date2)
	{
		return is_date1_before_date2(date1, date2) ? before : is_date1_equal_date2(date1, date2) ? equal : after;
	}

	en_dates_comparison compare_two_dates(cls_date date2)
	{
		return compare_two_dates(*this, date2);
	}

	static bool is_last_day_in_month(cls_date date)
	{
		return (date.day == days_in_month(date.year, date.month));
	}

	bool is_last_day_in_month()
	{
		return is_last_day_in_month(*this);
	}

	static bool is_last_month_in_year(short month)
	{
		return (month == 12);
	}

	bool is_last_month_in_year()
	{
		return is_last_month_in_year(_month);
	}

	static cls_date increase_date_by_one_day(cls_date date)
	{
		if (is_last_day_in_month(date))
		{
			if (is_last_month_in_year(date.month)) date.day = 1, date.month = 1, date.year++;
			else date.day = 1, date.month++;
		}
		else date.day++;
		return date;
	}

	void increase_by_one_day()
	{
		*this = increase_date_by_one_day(*this);
	}

	static cls_date increase_date_by_x_days(cls_date date, short increased_days)
	{
		date.day += increased_days;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		while (date.day > number_of_days_in_month)
		{
			date.day -= number_of_days_in_month;
			date.month++;
			if (date.month == 13)
				date.month = 1, date.year++;
			number_of_days_in_month = days_in_month(date.year, date.month);
		}
		return date;
	}

	void increase_by_x_days(short increased_days)
	{
		*this = increase_date_by_x_days(*this, increased_days);
	}

	static cls_date increase_date_by_one_week(cls_date date)
	{
		date.day += 7;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month)
		{
			date.day -= number_of_days_in_month, date.month++;
			if (date.month == 13)
				date.month = 1, date.year++;
		}
		return date;
	}

	void increase_by_one_week()
	{
		*this = increase_date_by_one_week(*this);
	}

	static cls_date increase_date_by_x_weeks(cls_date date, short increased_weeks)
	{
		date.day += (increased_weeks * 7);
		short number_of_days_in_month = days_in_month(date.year, date.month);
		while (date.day > number_of_days_in_month)
		{
			date.day -= number_of_days_in_month;
			date.month++;
			if (date.month == 13)
				date.month = 1, date.year++;
			number_of_days_in_month = days_in_month(date.year, date.month);
		}
		return date;
	}

	void increase_by_x_weeks(short increased_weeks)
	{
		*this = increase_date_by_x_weeks(*this, increased_weeks);
	}

	static cls_date increase_date_by_one_month(cls_date date)
	{
		date.month++;
		if (date.month == 13)
		{
			date.month == 1, date.year++;
			return date;
		}
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_one_month()
	{
		*this = increase_date_by_one_month(*this);
	}

	static cls_date increase_date_by_x_months(cls_date date, short increased_months)
	{
		date.month += increased_months;
		while (date.month > 12)
			date.month -= 12, date.year++;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_x_months(short increased_months)
	{
		*this = increase_date_by_x_months(*this, increased_months);
	}

	static cls_date increase_date_by_one_year(cls_date date)
	{
		date.year++;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_one_year()
	{
		*this = increase_date_by_one_year(*this);
	}

	static cls_date increase_date_by_x_years(cls_date date, short increased_years)
	{
		date.year += increased_years;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_x_years(short increased_years)
	{
		*this = increase_date_by_x_years(*this, increased_years);
	}

	static cls_date increase_date_by_one_decade(cls_date date)
	{
		date.year += 10;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_one_decade()
	{
		*this = increase_date_by_one_decade(*this);
	}

	static cls_date increase_date_by_x_decades(cls_date date, short increased_decades)
	{
		date.year += (10 * increased_decades);
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_x_decades(short increased_decades)
	{
		*this = increase_date_by_x_decades(*this, increased_decades);
	}

	static cls_date increase_date_by_one_century(cls_date date)
	{
		date.year += 100;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_one_century()
	{
		*this = increase_date_by_one_century(*this);
	}

	static cls_date increase_date_by_one_millennium(cls_date date)
	{
		date.year += 1000;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void increase_by_one_millennium()
	{
		*this = increase_date_by_one_millennium(*this);
	}

	static cls_date decrease_date_by_one_day(cls_date date)
	{
		if (date.day == 1)
		{
			if (date.month == 1) date.day = 31, date.month = 12, date.year--;
			else date.month--, date.day = days_in_month(date.year, date.month);
		}
		else date.day--;
		return date;
	}

	void decrease_by_one_day()
	{
		*this = decrease_date_by_one_day(*this);
	}

	static cls_date decrease_date_by_x_days(cls_date date, short decreased_days)
	{
		date.day -= decreased_days;
		short number_of_days_in_month;
		if (date.month == 1) number_of_days_in_month = days_in_month(date.year - 1, 12);
		else number_of_days_in_month = days_in_month(date.year, date.month - 1);
		while (date.day <= 0)
		{
			date.day += number_of_days_in_month;
			date.month--;
			if (date.month == 0)
				date.month = 12, date.year--;
			number_of_days_in_month = days_in_month(date.year, date.month - 1);
		}
		return date;
	}

	void decrease_by_x_days(short decreased_days)
	{
		*this = decrease_date_by_x_days(*this, decreased_days);
	}

	static cls_date decrease_date_by_one_week(cls_date date)
	{
		date.day -= 7;
		short number_of_days_in_month;
		if (date.month == 1) number_of_days_in_month = days_in_month(date.year - 1, 12);
		else number_of_days_in_month = days_in_month(date.year, date.month - 1);
		if (date.day <= 0)
		{
			date.day += number_of_days_in_month, date.month--;
			if (date.month == 0)
				date.month = 12, date.year--;
		}
		return date;
	}

	void decrease_by_one_week()
	{
		*this = decrease_date_by_one_week(*this);
	}

	static cls_date decrease_date_by_x_weeks(cls_date date, short decreased_weeks)
	{
		date.day -= (decreased_weeks * 7);
		short number_of_days_in_month;
		if (date.month == 1) number_of_days_in_month = days_in_month(date.year - 1, 12);
		else number_of_days_in_month = days_in_month(date.year, date.month - 1);
		while (date.day <= 0)
		{
			date.day += number_of_days_in_month;
			date.month--;
			if (date.month == 0)
				date.month = 12, date.year--;
			number_of_days_in_month = days_in_month(date.year, date.month - 1);
		}
		return date;
	}

	void decrease_by_x_weeks(short decreased_weeks)
	{
		*this = decrease_date_by_x_weeks(*this, decreased_weeks);
	}

	static cls_date decrease_date_by_one_month(cls_date date)
	{
		date.month--;
		if (date.month == 0)
		{
			date.month == 12, date.year--;
			return date;
		}
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_one_month()
	{
		*this = decrease_date_by_one_month(*this);
	}

	static cls_date decrease_date_by_x_months(cls_date date, short decreased_months)
	{
		date.month -= decreased_months;
		while (date.month <= 0)
			date.month += 12, date.year--;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_x_months(short decreased_months)
	{
		*this = decrease_date_by_x_months(*this, decreased_months);
	}

	static cls_date decrease_date_by_one_year(cls_date date)
	{
		date.year--;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_one_year()
	{
		*this = decrease_date_by_one_year(*this);
	}

	static cls_date decrease_date_by_x_years(cls_date date, short decreased_years)
	{
		date.year -= decreased_years;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_x_years(short decreased_years)
	{
		*this = decrease_date_by_x_years(*this, decreased_years);
	}

	static cls_date decrease_date_by_one_decade(cls_date date)
	{
		date.year -= 10;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_one_decade()
	{
		*this = decrease_date_by_one_decade(*this);
	}

	static cls_date decrease_date_by_x_decades(cls_date date, short decreased_decades)
	{
		date.year -= (10 * decreased_decades);
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_x_decades(short decreased_decades)
	{
		*this = decrease_date_by_x_decades(*this, decreased_decades);
	}

	static cls_date decrease_date_by_one_century(cls_date date)
	{
		date.year -= 100;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_one_century()
	{
		*this = decrease_date_by_one_century(*this);
	}

	static cls_date decrease_date_by_one_millennium(cls_date date)
	{
		date.year -= 1000;
		short number_of_days_in_month = days_in_month(date.year, date.month);
		if (date.day > number_of_days_in_month) date.day = number_of_days_in_month;
		return date;
	}

	void decrease_by_one_millennium()
	{
		*this = decrease_date_by_one_millennium(*this);
	}

	static int get_diff_in_days_between_two_dates(cls_date date1, cls_date date2, bool include_end_day = false)
	{
		if (is_date1_before_date2(date1, date2))
		{
			int diff_in_days = total_days_from_the_beginning_of_year(date2.year, date2.month, date2.day) - total_days_from_the_beginning_of_year(date1.year, date1.month, date1.day);
			for (short year = date1.year; year < date2.year; year++)
				diff_in_days += days_in_year(year);
			if (include_end_day) diff_in_days++;
			return diff_in_days;
		}
		else if (is_date1_before_date2(date2, date1))
			return (-1 * get_diff_in_days_between_two_dates(date2, date1, include_end_day));
		return 0;
	}

	int get_diff_in_days_between_two_dates(cls_date date2, bool include_end_day = false)
	{
		return get_diff_in_days_between_two_dates(*this, date2, include_end_day);
	}

	static cls_date get_system_date()
	{
		short day, month, year;
		time_t t = time(0);
		tm* now = localtime(&t);
		year = now->tm_year + 1900;
		month = now->tm_mon + 1;
		day = now->tm_mday;
		return cls_date(day, month, year);
	}

	static string get_system_time_string()
	{
		short hour, minute, second;
		time_t t = time(0);
		tm* now = localtime(&t);
		hour = now->tm_hour;
		minute = now->tm_min;
		second = now->tm_sec;
		return to_string(hour) + ':' + to_string(minute) + ':' + to_string(second);
	}

	static bool is_end_of_week(cls_date date)
	{
		return (get_day_order(date) == 6);
	}

	bool is_end_of_week()
	{
		return is_end_of_week(*this);
	}

	static bool is_weekend(cls_date date)
	{
		short day_order = get_day_order(date);
		return (day_order == 5 || day_order == 6);
	}

	bool is_weekend()
	{
		return is_weekend(*this);
	}

	static bool is_business_day(cls_date date)
	{
		return !is_weekend(date);
	}

	bool is_business_day()
	{
		return is_business_day(*this);
	}

	static short days_until_end_of_week(cls_date date)
	{
		return (6 - get_day_order(date));
	}

	short days_until_end_of_week()
	{
		return days_until_end_of_week(*this);
	}

	static short days_until_end_of_month(cls_date date)
	{
		return (days_in_month(date.year, date.month) - date.day + 1);
	}

	short days_until_end_of_month()
	{
		return days_until_end_of_month(*this);
	}

	static short days_until_end_of_year(cls_date date)
	{
		return (days_in_year(date.year) - total_days_from_the_beginning_of_year(date.year, date.month, date.day) + 1);
	}

	short days_until_end_of_year()
	{
		return days_until_end_of_year(*this);
	}

	static short get_vacation_period(cls_date date_from, cls_date date_to)
	{
		short vacation_days = get_diff_in_days_between_two_dates(date_from, date_to);
		while (date_from.year != date_to.year || date_from.month != date_to.month || date_from.day != date_to.day)
		{
			if (is_weekend(date_from)) vacation_days--;
			date_from = increase_date_by_one_day(date_from);
		}
		if (is_weekend(date_to)) vacation_days--;
		return vacation_days;
	}

	short get_vacation_period(cls_date date_to)
	{
		return get_vacation_period(*this, date_to);
	}

	static cls_date get_vacation_end_date(cls_date date, short vacation_period)
	{
		while (vacation_period > 0)
		{
			if (is_business_day(date)) vacation_period--;
			date = increase_date_by_one_day(date);
		}
		return date;
	}

	void get_vacation_end_date(short vacation_period)
	{
		*this = get_vacation_end_date(*this, vacation_period);
	}

	static bool is_valid_date(cls_date date)
	{
		return (date.year > 0 && date.month > 0 && date.month < 13 && date.day == days_in_month(date.year, date.month));
	}

	bool is_valid()
	{
		return is_valid_date(*this);
	}

	static cls_date from_string_to_date(string string_date)
	{
		cls_date date;
		string digit;
		short counter = 1;
		for (char& character : string_date)
		{
			if (character == '/')
			{
				if (counter == 1) date.day = stoi(digit);
				else if (counter == 2) date.month = stoi(digit);
				counter++;
				digit = "";
			}
			else digit += character;
		}
		date.year = stoi(digit);
		return date;
	}

	static string from_date_to_string(cls_date date, string format = "dd/mm/yyyy")
	{
		string string_date, digit;
		for (char& character : format)
		{
			digit += character;
			if (digit == "dd") string_date += to_string(date.day);
			else if (digit == "mm") string_date += to_string(date.month);
			else if (digit == "yyyy") string_date += to_string(date.year);
			else
			{
				if (digit == "d" || digit == "m" || digit == "y" || digit == "yy" || digit == "yyy") continue;
				else string_date += digit;
			}
			digit = "";
		}
		if (!digit.empty()) string_date += digit;
		return string_date;
	}

	string from_date_to_string(string format = "dd/mm/yyyy")
	{
		return from_date_to_string(*this);
	}

	static void swap_dates(cls_date& date1, cls_date& date2)
	{
		cls_date temp_date;
		temp_date = date1;
		date1 = date2;
		date2 = temp_date;
	}

	void swap_dates(cls_date date2)
	{
		swap_dates(*this, date2);
	}
};