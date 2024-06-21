#include <stdio.h>
#include <stdlib.h>

#include "parseur.h"

int main(int argc, char *argv[])
{
    struct option registre_des_options[] = {
        {'t', "test", 0}, //r1
        {'c', "client", 0}, //r2
        {'s', "server", 0}, //r3
        {'d', "directory", 0}, //r4
        {0},
    };

    int t_registre = 4;

/*     struct cpl_opt_arg *r1;
    struct cpl_opt_arg *r2;
    struct cpl_opt_arg *r3;
    struct cpl_opt_arg *r4; */

    return parsing(argc, argv, registre_des_options);
}
