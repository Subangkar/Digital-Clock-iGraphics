#include <stdio.h>
#include <time.h>

void gettime(int t[])
{
    time_t ctime;
    struct tm * current;
    time ( &ctime );
    current = localtime ( &ctime );
    t[0] = current->tm_hour;
    t[1] = current->tm_min;
    t[2] = current->tm_sec;
}

int main()
{
    int t[3] = {};

    while(1)
    {
        gettime(t);
        printf("%02d : %02d : %02d\n", t[0], t[1], t[2]); // hour, minute, second
    }
    return 0;

}
