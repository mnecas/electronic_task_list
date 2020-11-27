#include "common.h"
#include <time.h>


int main()
{
	// zmena
	struct tm newtime;
	time_t now = time(0);
	localtime_s(&newtime, &now);

	Date date;
	date.day = newtime.tm_mday;
	date.month = newtime.tm_mon + 1;
	date.year = newtime.tm_year + 1900;

	// TODO use dynamic variable

	Task* task = NULL;

	//int time, int duration, int finished, int priority, char *label, Date date, Task **task
	add_task(0, 12, 1, 0, 0, "test0", date, &task);
	add_task(1, 12, 1, 0, 0, "test1", date, &task);
	add_task(2, 12, 1, 0, 0, "test2", date, &task);
	add_task(3, 12, 1, 0, 0, "test3", date, &task);


	run(&date, &task, day);

	return 0;
}
