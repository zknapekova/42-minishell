#include "../include/main.h"
#include "stdlib.h"

int init_env(char **env)
{
    t_env_node *env_n;

    env_n = malloc(sizeof(t_env_node));
    if (!env_n)
        return (error_handler("Memory allocation failed"), 0);

    return (1);
}