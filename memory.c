#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@ptr: the pointer to the memory area
 *@Byte: the byte to fill *ptr with
 *@n: the amount of bytes to be filled
 *Return: (ptr) a pointer to the memory area ptr
 */
char *_memset(char *ptr, char Byte, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		ptr[i] = Byte;
	return (ptr);
}

/**
 * ffree - frees a string of strings
 * @pptr: string of strings
 */
void ffree(char **pptr)
{
	char **a = pptr;

	if (!pptr)
		return;
	while (*pptr)
		free(*pptr++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @oldSize: byte size of previous block
 * @newSize: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int oldSize, unsigned int newSize)
{
	char *p;

	if (!ptr)
		return (malloc(newSize));
	if (!newSize)
		return (free(ptr), NULL);
	if (newSize == oldSize)
		return (ptr);

	p = malloc(newSize);
	if (!p)
		return (NULL);

	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		p[oldSize] = ((char *)ptr)[oldSize];
	free(ptr);
	return (p);
}

/**
 * bfree - frees a pointer and NULLs the address.
 * @ptr: address of the pointer to free.
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
