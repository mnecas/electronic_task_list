#include "common.h"

const char* get_month_name(int month)
{
	// Retrun month name depending on the month
	static char* months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	return months[month];
}

void update_date(Date* date, int change)
{
	// Restart selected task
	selected = 0;
	selected_id = -1;
	
	// Add change (-7,-1,1,7) to the date
	date->tm_mday += change;
	mktime(date);
}

void add_task(int id, Time duration, int finished, int priority, char* label, Date date, Task** task)
{
	Task* new_task = (Task*)malloc(sizeof(Task));
	Task* this_task;
	if (!new_task) {
		// Could not allocate memory
		return;
	}

	// Add all variables
	strcpy_s(new_task->label, STR_SIZE, label);
	new_task->duration = duration;
	new_task->finished = finished;
	new_task->priority = priority;
	new_task->date = date;
	new_task->id = id;
	new_task->next = NULL;

	// Store the Task by Date in linked list from mallest to biggest
	if (*task == NULL)
	{
		*task = new_task;
		return;
	}
	else if (difftime(mktime(&new_task->date), mktime(&(*task)->date))< 0)
	{
		new_task->next = *task;
		*task = new_task;
		return;
	}
	this_task = *task;
	while (this_task) {
		if (this_task->next == NULL)
		{
			this_task->next = new_task;
			return;
		}
		else if (difftime(mktime(&new_task->date), mktime(&(*task)->date)) < 0)
		{
			new_task->next = this_task->next;
			this_task->next = new_task;
			return;
		}
		this_task = this_task->next;
	}
}

void print_task_label(Task task) {
	// Print Task label depending on the status of the Task (finished/prioprity)
	if (task.finished) printf(GREEN "%s" RESET, task.label);
	else if (task.priority == minimal) printf(YELLOW "%s" RESET, task.label);
	else if (task.priority == maximal) printf(RED "%s" RESET, task.label);
	else printf("%s", task.label);
}

void del_task(int id, Task** task)
{

	Task* new_task;

	// Delete taks with specific ID
	while (*task && (*task)->id == id)
	{
		Task* new_first = (*task)->next;
		free(*task);
		*task = new_first;
	}

	new_task = *task;
	while (new_task && new_task->next)
	{
		if (new_task->next->id == id)
		{
			Task* next_new = new_task->next->next;
			free(new_task->next);
			new_task->next = next_new;
		}
		new_task = new_task->next;
	}
}
