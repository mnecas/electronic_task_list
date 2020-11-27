typedef struct
{
	int year;
	int month;
	int day;
} Date;

typedef struct task
{
	Date date;
	int id;
	int time;
	int duration;
	int priority;
	char label[32];
	int finished;
	struct task* next;

} Task;