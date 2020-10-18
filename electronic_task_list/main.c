#include "common.h"
#include <time.h>
#include <stdio.h>

int main()
{
    // zmena
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    Date date;
    date.day = newtime.tm_mday ;
    date.month = newtime.tm_mon + 1;
    date.year = newtime.tm_year + 1900;
    
    Task list_of_tasks[10];




    Task first;
    first.date = date;
    first.time = 12;
    first.duration = 1;
    first.label = "test";
    first.finished = 0;
    first.priority = 0;

    date.day = newtime.tm_mday+1;


    printf("%d\n", date.day);
    printf("%d\n", first.date.day);


    run(&date);
    
    return 0;
}
