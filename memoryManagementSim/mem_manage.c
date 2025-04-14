#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include "anbui.h"
#include "mem_manage.h"

#define RAM_SIZE 65536 // Total memory size in KB
#define PAGE_SIZE 4096    // Size of each page in KB


Process create_process(int id, int size);
void assign_pages(Process *p, int num_free_frames);
void show_page_table(Process *p);
void free_process(int id);
void show_memory();

Process create_process(int id, int size)
{
    Process newProcess;
    newProcess.id = id;
    newProcess.size = size;
    return newProcess;
}

