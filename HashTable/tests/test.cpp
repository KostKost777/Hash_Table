#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int CMD_LEN = 512;

int main(const int argc, const char* argv[]) {

    const char* file_name = "base.txt";
    if (argc > 1) file_name = argv[1];

    const char* bin_file_name = "./a";
    if (argc > 1) bin_file_name = argv[2];
    
    for (int i = 1; i <= 10; i++) {
        char command[CMD_LEN];

        snprintf(command, sizeof(command), 
                 "echo '\n+++++++++++++++++++++++++++++++++++++++++ TEST %d +++++++++++++++++++++++++++++++++++++++++\n' >> %s && "
                 "sudo bash -c \"taskset -c 0 perf stat %s\" >> %s 2>&1 && "
                 "echo '\n+++++++++++++++++++++++++++++++++++++++++ END TEST %d +++++++++++++++++++++++++++++++++++++++++\n\n' >> %s",
                 i, file_name, bin_file_name, file_name, i, file_name);
        
        system(command);
        sleep(30);
    }
    return 0;
}