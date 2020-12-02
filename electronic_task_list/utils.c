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
    int adjustment, mm, yy;

    adjustment = (14 - month) / 12;
    mm = month + 12 * adjustment - 2;
    yy = year - adjustment;
    return (day + (13 * mm - 1) / 5 +
        yy + yy / 4 - yy / 100 + yy / 400) % 7;
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
    if (is_leap_year(year)) days[2] = 29;
    return days[month];
}
void get_days_in_week(Date *date, Date resp[])
{

    int _numberDay = number_of_weekday(date->day, date->month, date->year);
    int _numberOfDays = number_of_days(date->month, date->year);

    int _numberOfDays2;
    if (date->month - 1 > 0) _numberOfDays2 = number_of_days(date->month - 1, date->year);
    else _numberOfDays2 = number_of_days(12, date->year);

    int counter = 0;
    Date resp_date;

    for (int i = 0; i < 7; i++)
    {
        resp_date.month = date->month;
        int x = date->day - _numberDay + i;
        int y = _numberOfDays + 1;
        int _day = (date->day - _numberDay + i) % (number_of_days(date->month, date->year) + 1);
        if (x >= y) {
            _day = ++counter;
            resp_date.month = date->month+1;
        }
        else if (x <= 0) {
            _day = _numberOfDays2 + _day;
            resp_date.month = date->month-1;
        }
        resp_date.day=_day;
        resp[i] = resp_date;
    }
}

void update_date(Date *date, int change)
{
    selected = 0;
    selected_id = -1;
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

void add_task(int id, Time time, Time duration, int finished, int priority, char* label, Date date, Task** task)
{
    Task* new_task = (Task*)malloc(sizeof(Task));
    Task* this_task;

    strcpy_s(new_task->label, STR_SIZE, label);
    new_task->time = time;
    new_task->duration = duration;
    new_task->finished = finished;
    new_task->priority = priority;
    new_task->date = date;
    new_task->id = id;
    new_task->next = NULL;

    if (*task == NULL)
    {
        *task = new_task;
        return;
    }
    else if (new_task->id < (*task)->id)
    {
        new_task->next = *task;
        *task = new_task;
        return;
    }
    this_task = *task;
    while (this_task) {
        if (this_task->next == NULL)
        {
            this_task->next = new_task;
            return;
        }
        else if (new_task->id < this_task->id)
        {
            new_task->next = this_task->next;
            this_task->next = new_task;
            return;
        }
        this_task = this_task->next;
    }
}
Time* eval_time(Time time, Time duration) {
    Time* resp = (Time*)malloc(sizeof(time));
    resp->min = duration.min + time.min;
    resp->hour = duration.hour + time.hour;
    if (resp->min >= 60) {
        resp->hour += resp->min / 60;
        resp->min %= 60;
    }
    return resp;
}

void print_task_label(Task task) {
    if (task.finished) printf(GREEN "%s" RESET, task.label);
    else if (task.priority == minimal) printf(YELLOW "%s" RESET, task.label);
    else if (task.priority == maximal) printf(RED "%s" RESET, task.label);
    else printf("%s", task.label);
}

void del_task(int id, Task** task)
{

    Task* new_task;

    while (*task && (*task)->id == id)
    {
        Task* new_first = (*task)->next;
        free(*task);
        *task = new_first;
    }

    new_task = *task;
    while (new_task && new_task->next)
    {
        if (new_task->next->id == id)
        {
            Task* next_new = new_task->next->next;
            free(new_task->next);
            new_task->next = next_new;
        }
        new_task = new_task->next;
    }
}
