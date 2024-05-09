#ifndef PARSEUR_H
#define PARSEUR_H

#include <stdarg.h>

// PARSEUR_C

struct option
{
    char lettre;
    char *complet;
    unsigned int num_c;
};

struct cpl_opt_arg
{
    char *option;
    char **tab_arg;
    int nbr_arg;
};

int valide_opt(int argc, char *argv[]);

void tiret_to_normal(char *opt);

void char_to_string(char **opt, struct option *registre, int t_registre);

int in_registre(struct option *registre, int t_registre, int cpt_opt, char **tab_opt_s_t);

int nbr_arg_registre(struct option *registre, int t_registre, int **tab_nbr_arg, int nbr_opt);

int double_opt(int argc, char **liste_opt);

int cpt_option(int argc, char *argv[]);

char **liste_opt_s_tirets(int argc, char *argv[]);

void afficher_opt(char **liste, int taille);

void afficher_nbr_arg(char **liste_opt, int **liste_arg, int taille);

int cpt_parameter_in_opt(int argc, char **argv, int num_opt);

int parsing(int argc, char *argv[], struct option *registre, int nbr_registre_opt, ...);

#endif // MODULE_ICMP_H