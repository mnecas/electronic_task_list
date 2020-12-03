#include "common.h"


int main()
{
	time_t now = time(0);

	Date date;
	localtime_s(&date, &now);

	Task* task = NULL;

	Time duration;
	duration.hour = 1;
	duration.min = 20;
	add_task(0, duration, 0, normal, "test1", date, &task);
	add_task(1, duration, 0, minimal, "test2", date, &task);
	add_task(2, duration, 0, minimal, "test3", date, &task);
	add_task(3, duration, 0, maximal, "test4", date, &task);

	run(&date, &task, day);

	return 0;
}
