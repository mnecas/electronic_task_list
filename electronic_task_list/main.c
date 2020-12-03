#include "common.h"


int main()
{
	time_t now = time(0);

	Date date;
	localtime_s(&date, &now);

	Task* task = NULL;

	//int time, int duration, int finished, int priority, char *label, Date date, Task **task

	Time duration;
	duration.hour = 1;
	duration.min = 20;
	add_task(0, duration, 0, normal, "test1", date, &task);
	add_task(1, duration, 0, minimal, "test2", date, &task);
	add_task(2, duration, 0, minimal, "test3", date, &task);
	add_task(3, duration, 0, maximal, "test4", date, &task);


	int ret;
	Date info;
	char buffer[80];

	info.tm_year = 2020 - 1900;
	info.tm_mon = 12 - 1;
	info.tm_mday = 6;
	info.tm_hour = 10;
	info.tm_min = 0;
	info.tm_sec = 1;
	info.tm_isdst = -1;
	ret = mktime(&info);
	printf("FIRST %d\n", info.tm_wday);
	info.tm_mday+=1;
	ret = mktime(&info);
	printf("SEC %d\n", info.tm_mday);


	run(&date, &task, day);

	return 0;
}
