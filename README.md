# ft_malloc
Projet plutôt UNIX


### Description

Une librairie de gestion de l'allocation dynamique de la mémoire.
Intégration des fonctions suivantes:
```
void free(void *ptr);
void *malloc(size_t size);
void *realloc(void *ptr, size_t size);
void show_alloc_mem();
```
### Fonctions autorisées
  - mmap
  - munmap
  - getpagesize
  - getrlimit
  - libpthread
  - libft
