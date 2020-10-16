
const char* months[13] = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

int year_code(int year)
{
    return year % 100 + ((year % 100) % 4);
}
int number_of_weekday(int day, int month, int year)
{
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
void get_days_in_week(int day, int month, int year, int* resp)
{

    int _numberDay = number_of_weekday(day, month, year);
    int _numberOfDays = number_of_days(month, year);

    int _numberOfDays2;
    if (month - 1 > 0)
        _numberOfDays2 = number_of_days(month - 1, year);
    else
        _numberOfDays2 = number_of_days(12, year);

    int counter = 0;

    for (int i = 0; i < 7; i++)
    {
        int x = day - _numberDay + i;
        int y = _numberOfDays + 1;
        int _day = (day - _numberDay + i) % (number_of_days(month, year) + 1);
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
void update_date(int* day, int* month, int* year, int change)
{
    int _numberOfDays = number_of_days(*month, *year);
    int original = *day;
    *day += change;
    if (*day <= 0)
    {
        *month -= 1;
        if (*month == 0)
        {
            *month = 12;
            *year -= 1;
            *day += 1;
        }
        *day = number_of_days(*month, *year) + *day;
    }
    else if (*day > number_of_days(*month, *year))
    {
        *month += 1;
        if (*month == 13)
        {
            *month = 1;
            *year += 1;
            *day -= 1;
        }
        *day = *day - _numberOfDays;
    }
}