#include <stdio.h>
#include <assert.h>
#include "mem_manage.h"

int main()
{
    __pid_t pid = getpid();
    printf("El PID del proceso es: %d\n", pid);

    Process newProc = create_process(pid, 4256); 
    
    printf("Process %d created with size %d KB and %d pages.\n", newProc.id, newProc.size / 1000, newProc.num_pages);
    return 0;
}