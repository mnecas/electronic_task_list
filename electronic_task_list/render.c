#include "common.h"
#include <stdio.h>
#include <stdlib.h>

#define WHITE_BACK "\x1b[7m"
#define RESET "\x1b[0m"

void render_header(Date* date)
{
    printf("\t%d\t\t\t%s\n", date->year, get_month_name(date->month));
    printf("\tSun\tMon\tTue\tWed\tThu\tFri\tSat\n");
    printf("\t");
    for (int i = 0; i < 52; i++)
        printf("-");
    printf("\n");
}
void render_options()
{

    printf("\n\n");
    printf("\t View options:");
    printf("\n");
    printf("\t m - month");
    printf("\t w - week");
    printf("\t d - day");
    printf("\n");
    printf("\n");
    printf("\t Control options:");
    printf("\n");
    printf("\t a - add");
    printf("\t c - copy");
    printf("\t m - move");
    printf("\t f - find");
    printf("\n");
}
void render_month(Date* date)
{
    // Clear previous render
    system("cls");

    // Redner header
    render_header(date);

    int _numberDay = number_of_weekday(1, date->month, date->year);
    int _numberOfDays = number_of_days(date->month, date->year);

    // Padding
    for (int i = 0; i < _numberDay; i++)
        printf("\t");

    for (int i = 1; i < _numberOfDays + 1; i++)
    {
        if (date->day == i)
        {
            printf(WHITE_BACK "\t%d" RESET, i);
        }
        else
        {
            printf("\t%d", i);
        }
        if ((_numberDay + i) % 7 == 0)
        {
            printf("\n");
        }
    }
    render_options();
}
void render_day(Date* date)
{
    system("cls");
    printf("\t%d. %s %d\n", date->day, get_month_name(date->month), date->year);
    for (int i = 0; i < 10; i++)
        printf("\t" WHITE_BACK "test\n" RESET);

    render_options();
}
void render_week(Date * date)
{
    // Clear previous render
    system("cls");

    // Redner header
    render_header(date);
    int daysInWeek[7];
    //int _numberDay = number_of_weekday(date->day, date->month, date->year);
    //int _numberOfDays = number_of_days(date->month, date->year);
    get_days_in_week(date, daysInWeek);
    for (int i = 0; i < 7; i++) {
        if (daysInWeek[i] == (*date).day) printf(WHITE_BACK "\t%d" RESET, daysInWeek[i]);
        else printf("\t%d", daysInWeek[i]);
    }
    render_options();
}