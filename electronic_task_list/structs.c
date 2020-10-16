typedef struct
{
    int year;
    int month;
    int day;
} Date;

typedef struct
{
    Date date;
    int time;
    int duration;
    int priority;
    char* label;
    int finished;
} Task;