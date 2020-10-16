#include "common.h"
#include <conio.h>

void run_month(Date *date)
{

    render_month(date);
    int ch;
    while ((ch = _getch()) != 27)
    {
        if (ch == 0 || ch == 224)
        {
            int arrow = _getch();
            switch (arrow)
            {
            case 72:
                // Arrow up
                update_date(date, -7);
                render_month(date);
                break;
            case 75:
                // Arrow left
                update_date(date, -1);
                render_month(date);
                break;
            case 80:
                // Arrow down
                update_date(date, 7);
                render_month(date);
                break;
            case 77:
                // Arrow right
                update_date(date, 1);
                render_month(date);
                break;
            }
        }
        else if ((char)ch == 'w' || (char)ch == 'd')
        {
            break;
        }
    }
    if ((char)ch == 'w')
        run_week(date);
    else if ((char)ch == 'd')
        run_day(date);
}
void run_day(Date * date)
{

    render_day(date);
    int ch;
    while ((ch = _getch()) != 27)
    {
        if (ch == 0 || ch == 224)
        {
            int arrow = _getch();
            switch (arrow)
            {
            case 72:
                // Arrow up
                update_date(date, -7);
                render_day(date);
                break;
            case 75:
                // Arrow left
                update_date(date, -1);
                render_day(date);
                break;
            case 80:
                // Arrow down
                update_date(date, 7);
                render_day(date);
                break;
            case 77:
                // Arrow right
                update_date(date, 1);
                render_day(date);
                break;
            }
        }
        else if ((char)ch == 'w' || (char)ch == 'm')
        {
            break;
        }
    }
    if ((char)ch == 'w')
        run_week(date);
    else if ((char)ch == 'm')
        run_month(date);
}

void run_week(Date* date)
{
    printf("%d", date->day);
    render_week(date);
    int ch;
    while ((ch = _getch()) != 27)
    {
        if (ch == 0 || ch == 224)
        {
            int arrow = _getch();
            switch (arrow)
            {
            case 72:
                // Arrow up
                update_date(date, -7);
                render_week(date);
                break;
            case 75:
                // Arrow left
                update_date(date, -1);
                render_week(date);
                break;
            case 80:
                // Arrow down
                update_date(date, 7);
                render_week(date);
                break;
            case 77:
                // Arrow right
                update_date(date, 1);
                render_week(date);
                break;
            }
        }
        else if ((char)ch == 'd' || (char)ch == 'm')
        {
            break;
        }
    }
    if ((char)ch == 'm')
        run_month(date->day, date->month, date->year);
    else if ((char)ch == 'd')
        run_day(date->day, date->month, date->year);
}
void run(Date *date) {
    run_day(date);
}