#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include "anbui.h"
#include "mem_manage.h"

Process create_process(int id, int size);
void assign_pages(Process *p, int num_free_frames);
void show_page_table(Process *p);
void free_process(int id);
void show_memory();

__pid_t new_pid(void)
{
    __pid_t pid = getpid();
    return pid;
}

Process create_process(int id, int size)
{
    Process newProcess;
    newProcess.id = id;
    newProcess.size = size;
    return newProcess;
}

