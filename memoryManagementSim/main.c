#include <stdio.h>
#include <assert.h>
#include "mem_manage.h"

int main()
{
    __pid_t pid = getpid();
    printf("El PID del proceso es: %d\n", pid);

    Process newProc = create_process(pid, 1024); // Crear un proceso de 1024 KB
    printf("Proceso creado con ID: %d y tamaño: %d KB\n", newProc.id, newProc.size);
    return 0;
}