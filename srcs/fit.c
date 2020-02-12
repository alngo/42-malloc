#include "malloc.h"

void		*fit_block_large(void *heap, size_t size)
{
	t_meta	*heap_meta;

	heap_meta = get_meta(heap);
	if (heap_meta->flags & INUSE)
		return (NULL);
	set_meta(heap, size, INUSE | MMAPD, NULL);
	return (heap);
}

void		*fit_block_tiny_small(void *heap, size_t size)
{
	void	*block;
	void	*next;
	t_meta	*block_meta;
	size_t	aligned_size;

	block = get_payload(heap);
	next = NULL;
	while (block)
	{
		block_meta = get_meta(block);
		if (!(block_meta->flags & INUSE))
		{
			if (block_meta->size == 0 || block_meta->size >= size)
			{
				aligned_size = size_alignment(size, sizeof(void *));
				next = block + sizeof(t_meta) + aligned_size;
				if (next > (heap + get_meta(heap)->size))
					next = NULL;
				set_meta(block, size, INUSE, next);
				break ;
			}
		}
		block = block_meta->next;
	}
	return (block);
}

void		*fit_block(void **heap, size_t size)
{
	void	*block;

	if (!*heap && !(*heap = init_heap(size)))
		return (NULL);
	if (size > SMALL)
		block = fit_block_large(*heap, size);
	else
		block = fit_block_tiny_small(*heap, size);
	if (block)
		return (block);
	return (fit_block(&((t_meta *)(*heap))->next, size));
}
