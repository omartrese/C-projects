#ifndef MEM_MANAGE_SIM_H
#define MEM_MANAGE_SIM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
// #include "anbui.h"

#define RAM_SIZE 16384 // Total memory size in KB
#define FRAME_SIZE 4096    // Size of each page in KB
#define MAX_PROCESS_SIZE 8192 // Maximum size of a process in KB
#define NUM_PAGES_FRAMES (RAM_SIZE / FRAME_SIZE) // Total number of pages


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
*   - `num_pages`: Number of pages assigned to the process
*/
typedef struct {
    uint16_t id;
    uint16_t size; // (KB)
    uint16_t num_pages;
} Process;

/*
* Create a process with the given ID and size.
*   - `id`: Process ID
*   - `size`: Size of the process in KB
*   - Returns a Process structure with the given ID and size.
*/
Process create_process(int id, int size);


void assign_pages(Process *process, int num_free_frames);

void show_page_table(Process *process);

void free_process(int id);

void show_memory();

#endif