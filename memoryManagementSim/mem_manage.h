#ifndef MEM_MANAGE_SIM_H
#define MEM_MANAGE_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include "anbui.h"


/*
*   
*   Page table entry structure to hold page information.
*   - `process_id`: ID of the process
*   - `page`: Page number
*   - `frame`: Frame number in memory
*/
typedef struct {
    int process_id;
    int page;
    int frame;
} PageTableEntry;

/*
*   Process structure to hold process information.
*   - `id`: Process ID
*   - `size`: Size of the process in KB
*   - `table`: Page table entries
*   - `num_pages`: Number of pages assigned to the process
*/
typedef struct {
    int id;
    int size; // (KB)
    PageTableEntry table[32]; // example, maximum 32 pages
    int num_pages;
} Process;

//functions
Process create_process(int id, int size);

void assign_pages(Process *p, int num_free_frames);

void show_page_table(Process *p);

void free_process(int id);

void show_memory();

#endif