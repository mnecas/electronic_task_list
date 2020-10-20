#include "common.h"

const char* months[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

int year_code(int year)
{
    return year % 100 + ((year % 100) % 4);
}
int number_of_weekday(int day, int month, int year)
{
    // TODO: when for diffrent years than 2020

    /*
    Input:
        int day 1-31;
        int month 1-12;
        int year any year from 21st century;
    Retrun:
        0 - for Sunday and 6 for Saturday
    */
    int monthCodes[13] = { 0, 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };
    int centuryCode = 4;
    return (year_code(year) + monthCodes[month] + centuryCode + day) % 7;
}
int is_leap_year(int year)
{
    // Return: if year is leap year
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
const char* get_month_name(int month)
{
    return months[month];
}
int number_of_days(int month, int year)
{
    /*
        Input:
            int month 1-12;
            int year;
        Return:
            days in month

    */
    int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (is_leap_year(year))
    {
        days[2] = 29;
    }
    return days[month];
}
void get_days_in_week(Date * date, int resp[])
{

    int _numberDay = number_of_weekday(date->day, date->month, date->year);
    int _numberOfDays = number_of_days(date->month, date->year);

    int _numberOfDays2;
    if (date->month - 1 > 0)
        _numberOfDays2 = number_of_days(date->month - 1, date->year);
    else
        _numberOfDays2 = number_of_days(12, date->year);

    int counter = 0;

    for (int i = 0; i < 7; i++)
    {
        int x = date->day - _numberDay + i;
        int y = _numberOfDays + 1;
        int _day = (date->day - _numberDay + i) % (number_of_days(date->month, date->year) + 1);
        if (x >= y)
        {
            _day = ++counter;
        }
        else if (x <= 0)
        {
            _day = _numberOfDays2 + _day;
        }
        resp[i] = _day;
    }
}
void update_date(Date *date, int change)
{
    int _numberOfDays = number_of_days(date->month, date->year);
    int original = date->day;
    date->day += change;
    if (date->day <= 0)
    {
        date->month -= 1;
        if (date->month == 0)
        {
            date->year--;
            date->month = 12;
        }
        if (date->month == 2 && is_leap_year(date->year)) {
            date->day--;
        }
        date->day += number_of_days(date->month, date->year);
    }
    else if (date->day > _numberOfDays)
    {
        date->month += 1;
        if (date->month == 13)
        {
            date->year++;
            date->month = 1;
        }
        if (date->month == 2 && is_leap_year(date->year)) {
            date->day++;
        }
        date->day -= _numberOfDays;
    }
}