#include <time.h>
#include "run.h"

int main()
{

    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);

    int month = newtime.tm_mon + 1;
    int year = newtime.tm_year + 1900;
    int day = newtime.tm_mday;

    run(day, month, year);
    return 0;
}
