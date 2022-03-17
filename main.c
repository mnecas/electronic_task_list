#include "common.h"

int main()
{
	time_t now = time(0);

	Date date;
	date = *localtime(&now);

	Task *task = NULL;
	system("/bin/stty raw");

	run(&date, &task, day);
	system("/bin/stty cooked");

	return 0;
}
