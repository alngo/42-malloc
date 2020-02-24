# ft_malloc [![Build Status](https://travis-ci.com/alngo/libft_malloc.svg?branch=master)](https://travis-ci.com/alngo/libft_malloc)
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

### Structure

```
[tiny][small]:

Arenas:					=> arena are getpagesize() aligned
	[size|flags][next] 	=> 16bits; 
	[null]
or:
	[size|flags][next] 	=> 16bits;
	[...]				=> payload are sizeof(void *) aligned
	[...]
	[...]
	[...]
	[size|flags][next] 	=> 16bits;
	[...]
	[...]

[large]:
	[size|flags][next] 	=> 16bits;
	[...]
	[...]
	[...]
	[...]
	[size|flags][next] 	=> 16bits;
	[...]
	[...]

flags = Mmap'd | PrevInUse
```

### Debug flags

`-DDCALLTRACE=[1-4]`
> Print call trace

`-DDHEXMEM=[1-...]`
> Print hex memory for x bytes

`-DDEBUG`
> show_allocation_mem after malloc, realloc, free call

