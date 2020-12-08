#include "common.h"

int main()
{
	time_t now = time(0);

	Date date;
	localtime_s(&date, &now);

	Task* task = NULL;

	FILE* file;

	fopen_s(&file, "D:\\data.txt", "r");

	Task input;

    if (file == NULL) {
		printf("Soubor nebyl nalezen\n");
		exit(1);
	}
	while (fread_s(&input, sizeof(Task), sizeof(Task), 1, file)) {
		add_task(input.id, input.duration, input.finished, input.priority, input.label, input.date, &task);
    }

	fclose(file);

	run(&date, &task, day);


	fopen_s(&file, "D:\\data.txt", "w");
	if (file == NULL) {
		printf("Soubor nebyl nalezen\n");
		exit(1);
	}

	while (task) {
		fwrite(task, sizeof(Task), 1, file);
		task = task->next;
	}
	fclose(file);
	
	return 0;
}
