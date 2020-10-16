#include <stdio.h>

#define WHITE_BACK "\x1b[7m"
#define RESET "\x1b[0m"

void render_header(int month, int year)
{
    printf("\t%d\t\t\t%s\n", year, get_month_name(month));
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
void render_month(int day, int month, int year)
{
    // Clear previous render
    system("cls");

    // Redner header
    render_header(month, year);

    int _numberDay = number_of_weekday(1, month, year);
    int _numberOfDays = number_of_days(month, year);

    // Padding
    for (int i = 0; i < _numberDay; i++)
        printf("\t");

    for (int i = 1; i < _numberOfDays + 1; i++)
    {
        if (day == i)
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
void render_day(int day, int month, int year)
{
    system("cls");
    printf("\t%d. %s %d\n", day, get_month_name(month), year);
    for (int i = 0; i < 10; i++)
        printf("\t" WHITE_BACK "test\n" RESET);

    render_options();
}
void render_week(int day, int month, int year)
{
    // Clear previous render
    system("cls");

    // Redner header
    render_header(month, year);
    int* daysInWeek = (int*)calloc(7, sizeof(int));
    int _numberDay = number_of_weekday(day, month, year);
    int _numberOfDays = number_of_days(month, year);
    get_days_in_week(day, month, year, daysInWeek);
    for (int i = 0; i < 7; i++) {
        if (*daysInWeek == day) printf(WHITE_BACK "\t%d" RESET, *daysInWeek);
        else printf("\t%d", *daysInWeek);
        daysInWeek++;
    }
    render_options();
}