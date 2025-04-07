#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main()
{
    FILE *file;
    regex_t error, warning, info;
    int errors = 0, warns = 0, infos = 0;
    
    file = fopen("./logs/example.log", "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    
    printf("File example.log opened successfully!\n");
    printf("Reading file content:\n");
    
    char content[1000];
    
    regcomp(&error, "ERROR", 0);
    regcomp(&warning, "WARNING", 0); regcomp(&info, "INFO", 0);
    
    while (fgets(content, sizeof(content), file))
    {
        // printf("%s", content);
        
        if (regexec(&error, content, 0, NULL, 0) == 0)
        {
            // printf("Found ERROR in line: %s", content);
            
            errors++;
        } else if(regexec(&warning, content, 0, NULL, 0) == 0)
        {
            // printf("Found WARNING in line: %s", content);
            warns++;
        } else if (regexec(&info, content, 0, NULL, 0) == 0)
        {
            // printf("Found INFO in line: %s", content);
            infos++;
        }
    }
    regfree(&error);
    regfree(&warning);
    regfree(&info);
    printf("Total errors: %d\n", errors);
    printf("Total warnings: %d\n", warns);
    printf("Total infos: %d\n", infos);
    
    fclose(file);
    return 0;
}
