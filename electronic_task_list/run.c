#include <conio.h>

#include "render.h"
#include "utils.h"
#include "structs.c"

void run_day(Date* date);
void run_week(Date* date);
void run_month(Date* date);

void run_week(Date* date)
{

    render_week((*date).day, (*date).month, (*date).year);
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
                update_date(&day, &month, &year, -7);
                render_week(day, month, year);
                break;
            case 75:
                // Arrow left
                update_date(&day, &month, &year, -1);
                render_week(day, month, year);
                break;
            case 80:
                // Arrow down
                update_date(&day, &month, &year, 7);
                render_week(day, month, year);
                break;
            case 77:
                // Arrow right
                update_date(&day, &month, &year, 1);
                render_week(day, month, year);
                break;
            }
        }
        else if ((char)ch == 'd' || (char)ch == 'm')
        {
            break;
        }
    }
    if ((char)ch == 'm')
        run_month(day, month, year);
    else if ((char)ch == 'd')
        run_day(day, month, year);
}
void run_day(Date* date)
{

    render_day(day, month, year);
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
                update_date(&day, &month, &year, -7);
                render_day(day, month, year);
                break;
            case 75:
                // Arrow left
                update_date(&day, &month, &year, -1);
                render_day(day, month, year);
                break;
            case 80:
                // Arrow down
                update_date(&day, &month, &year, 7);
                render_day(day, month, year);
                break;
            case 77:
                // Arrow right
                update_date(&day, &month, &year, 1);
                render_day(day, month, year);
                break;
            }
        }
        else if ((char)ch == 'w' || (char)ch == 'm')
        {
            break;
        }
    }
    if ((char)ch == 'w')
        run_week(day, month, year);
    else if ((char)ch == 'm')
        run_month(day, month, year);
}
void run_month(Date* date)
{

    render_month(day, month, year);
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
                update_date(&day, &month, &year, -7);
                render_month(day, month, year);
                break;
            case 75:
                // Arrow left
                update_date(&day, &month, &year, -1);
                render_month(day, month, year);
                break;
            case 80:
                // Arrow down
                update_date(&day, &month, &year, 7);
                render_month(day, month, year);
                break;
            case 77:
                // Arrow right
                update_date(&day, &month, &year, 1);
                render_month(day, month, year);
                break;
            }
        }
        else if ((char)ch == 'w' || (char)ch == 'd')
        {
            break;
        }
    }
    if ((char)ch == 'w')
        run_week(day, month, year);
    else if ((char)ch == 'd')
        run_day(day, month, year);
}
void run(Date *date) {
    run_day((*date).day, (*date).month, (*date).year);
}