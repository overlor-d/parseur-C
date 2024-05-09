#ifndef PARSEUR_H
#define PARSEUR_H

// Prototype des structures pour un parser d'options

// Structure pour les options disponibles
typedef struct
{
    char shortcut;
    const char *long_name;
    int arg_count;
} OptionDef;

typedef struct
{
    const char *long_name;
    char **arguments;
    int arg_count;
} ParsedOption;

// Structure pour la configuration complète après parsing
typedef struct
{
    ParsedOption *options;
    int count;
} ParsedOptions;

// Prototype de la fonction de parsing

/**
 * Parse les arguments de ligne de commande.
 *
 * @param argc Le nombre d'arguments passés à la ligne de commande.
 * @param argv Le tableau des arguments passés à la ligne de commande.
 * @param options_def La liste des options disponibles (tableau d'OptionDef).
 * @param num_options Le nombre d'options disponibles dans options_def.
 * @param parsed_options Un pointeur vers une structure ParsedOptions qui sera
 * @return 0 si le parsing est réussi, ou un code d'erreur en cas de problème.
 */
int parse_arguments(int argc, char *argv[], const OptionDef *options_def,
                    int num_options, ParsedOptions *parsed_options);

#endif /*PARSEUR_H*/