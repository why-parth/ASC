#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int cmd_len = 0;
#define append_cmd(cmd) cmd_len++, cmd[cmd_len - 1] =

void append_cmd_from_str(char * cmd, char * str);

int main (int argc, char ** argv) {

    char * file_name = NULL;
    if (argc == 1) {
        printf("\033[0;91mNo file(s) provided!\033[0;0m");
        return 0;
    }
    else file_name = argv[1]; 

    unsigned int len = 0;
    while (file_name[len]) len++;

    char * cmd_1 = "gcc \
    .\\reader.c\
    \
    \".\\for reader.c\\asc_apc.c\" \
    \".\\for reader.c\\asc_apc_character_class.c\" \
    \
    \".\\for buffer.h\\asc_simple_buffer.c\" \
    \".\\for buffer.h\\asc_type.c\" \
    \".\\buffer.c\" \
    \
    -o reader";

    char * cmd_2 = malloc(sizeof(char) * (len + 4));

    append_cmd_from_str(cmd_2, ".\\reader.exe ");

    strcpy(cmd_2 + cmd_len, file_name);
    cmd_len += len;

    system(cmd_1);
    system(cmd_2);

    free(cmd_2);

    char * cmd_3; // for future add-on(s) like providing dev.c(s) via face, etc.

    return 0;
}

void append_cmd_from_str(char * cmd, char * str) {
    while (* str) append_cmd(cmd) * str, str++;
}
