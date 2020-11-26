#include "common.h"
#include <conio.h>

void run(Date *date, enum runType format) {
    render(date, format);
    int ch;
    while ((ch = _getch()) != 27)
    {
        render(date, format);
        if (ch == 0 || ch == 224)
        {
            int arrow = _getch();
            switch (arrow)
            {
            case 72:
                // Arrow up
                update_date(date, -7);
                break;
            case 75:
                // Arrow left
                update_date(date, -1);
                break;
            case 80:
                // Arrow down
                update_date(date, 7);
                break;
            case 77:
                // Arrow right
                update_date(date, 1);
                break;
            }
        }
        else if ((char)ch == 'd')
        {
            format = day;
        }
        else if ((char)ch == 'w')
        {
            format = week;
        }
        else if ((char)ch == 'm')
        {
            format = month;
        }
        else {
            break;
        }
    }
}