#include "parseur.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    OptionDef options_def[] = {
        { 'h', "help", 0 },      { 'v', "verbose", 0 }, { 'o', "output", 1 },
        { 'd', "directory", 1 }, { 'f', "files", -1 },
    };
    int num_options = sizeof(options_def) / sizeof(options_def[0]);

    ParsedOptions parsed_options;
    parsed_options.options = NULL;
    parsed_options.count = 0;

    int result =
        parse_arguments(argc, argv, options_def, num_options, &parsed_options);

    if (result != 0)
    {
        fprintf(stderr, "Erreur lors du parsing des arguments.\n");
        return EXIT_FAILURE;
    }

    printf("Options détectées (%d):\n", parsed_options.count);
    for (int i = 0; i < parsed_options.count; ++i)
    {
        ParsedOption opt = parsed_options.options[i];
        printf("Option: --%s\n", opt.long_name);
        for (int j = 0; j < opt.arg_count; ++j)
        {
            printf("  Argument %d: %s\n", j + 1, opt.arguments[j]);
        }
    }

    for (int i = 0; i < parsed_options.count; ++i)
    {
        free(parsed_options.options[i].arguments);
    }
    free(parsed_options.options);

    return EXIT_SUCCESS;
}
