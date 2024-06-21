###  **1. La structure**

La structure `cpl_opt_arg` est une structure servant à être initialisée dans la fonction main et donnée en paramètre de la fonction de parsing daans la fonction parsing elle sera initialisée de façon à avoir un pointeur vers cette structure afin de pouvoir l'utiliser au bon vouloir de l'utilisateur.

Le user devra donner dans l'ordre du registre ses poitneur vers structure cpl_opt_arg.

La strcture se présente comme tel :

```c
struct cpl_opt_arg
{
char *option;
char **tab_arg;
int nbr_arg;
};
```

L'initialisation prendra la forme suivante :
- Le `char *option` correspond au nom de l'option en entier, le nom complet, ce sera un pointeur vers une chaîne de caractère de longueur prédéfinie dans le registre des options que nous verrons plus tard.
- Le `char **tab_arg` correspond à la liste de tous les arguments donné avec l'option. Il reste à voir comment gérer les longueurs variables pour les noms des arguments (soit je prendrais une autre version de C soit je prendrais une longueur très grande mais pour une question de sécurité je prendrais la version numéro 1)
- Le `int nbr_arg` est le nombre d'arguments qui se trouve dans le `tab_arg`.

Pour l'instant aucun autre membre n'est à prévoir mais peut-être que cela changera en fonction des besoins.

###  **2. Le registre**

Le registre sert à définir les options autorisée ou non ainsi que les racourcis type -l pour --list on aura également un chiffre qui permettra de définir si l'option a le droit ou non de posséder des arguments. Lorsqu'un utilisateur mettra en paramètres une option qui n'appartient pas au registre ils sera automatiquement renvoyé dans le help du projet s'il en existe un.

La structure se présente comme tel :

```C
struct option
{
    char lettre;
    char *complet;
    int num_c;
};
```

L'initialisation prendra la forme suivante :
- Le `char lettre`correspond à la miniature pour que l'on puisse se référencer au nom complet. Dans le cas où il y a plusieurs fois la même lettre dans le registre une erreur registre sera renvoyée on l'utilise comme cela `-o argument1 argument2` où le -o signifie --option en nom complet
- Le `char *complet` correspond au nom complet de l'option. Dans le cas où une option a la même lettre qu'une autre mettez un '_'.
- Le `unsigned int num_c` sert à dire combien d'arguments sont autorisé par l'option:
    - le 1 pour une option max 2 pour 2 etc jusqu'à x pour x.
    - 0 pour 0 option.
    - -1 pour autant d'arguments que l'on veut.

Dans chaque cas si un nombre d'argument est trop élevé par rapport à ce qui est autorisé l'utilisateur sera redirigé vers la page help prédéfinie.

---

Avant de renvoyer les structure initialisée j'aimerais trouver quelque chose d'optimisé.

L'ordre dans lequel sont données les structures d'option sera le même que celui du registre.
on doit injecter au fur et à mesure du passage sur registre dans les structure allouées. 

1. On entre dans une boucle for qui fait tant que le registre ne fini pas par 0
    1. On regarde le nom de l'option du registre puis on ajoute deux tiret devant et pour la lettre un seul tiret ces deux nom seront enregistrés en mémoire pour comparer avec les options.
    2. Si le nom de l'option est reconnu on calcule le nombre d'argument derrière jusqu'à la prochaine option et on continue à parcourir les option pour voir s'il y a une autre initialisation de celle-ci plus tard.
        1. Une fois que le nombre d'argument ont été traités on peut allouer le nom de l'option dans la structure
        2. On allouer en mémoire la taille de la liste avec les arguments
        3. On parcourt la liste des options et args pour allouer en mémoire chacune des options dans la liste.
        4. On alloue le nombre d'argument de la structure dans le dernier slot de la structure 

    on passe à la structure suivante

    
La fonction ne renvoie rien.