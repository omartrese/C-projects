#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include "anbui.h"
#include "mem_manage.h"

Process create_process(int id, int size);
void assign_pages(Process *process, int num_free_frames);
void show_page_table(Process *process);
void free_process(int id);
void show_memory();

Process create_process(int id, int size)
{
    Process newProcess;
    newProcess.id = id;
    if(size > MAX_PROCESS_SIZE) {
        newProcess.size = MAX_PROCESS_SIZE;
        printf("Process size exceeds maximum limit. Setting to maximum size.\n");
    }
    newProcess.size = size;
    newProcess.num_pages = (size + FRAME_SIZE - 1) / FRAME_SIZE; // Calculate number of pages needed
    return newProcess;
}

void assign_pages(Process *process, int num_free_frames)
{
    if(process->num_pages > NUM_PAGES_FRAMES) 
    {
        printf("Not enough frames available for process %d\n", process->id);
        return;
    }
}
