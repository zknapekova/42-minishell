/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:48:02 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/02 17:52:48 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (!nmemb || !size)
	{
		ptr = malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb * size > 2147483647)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

// #include <assert.h>
// int main(void) 
// {
//     int i;
//     int n = 21474836; // Fixed size of the array
//     int *arr;

//     // Allocate memory using calloc for 'n' integers
//     arr = (int*) ft_calloc(n, sizeof(int));

//     // Use assert to check if memory allocation was successful
//     assert(arr != NULL);

//     // Use assert to verify if calloc initialized memory to zero
//     for (i = 0; i < n; i++) {
//         assert(arr[i] == 0);
//     }

//     printf("Memory allocation and initialization successful.\n");

//     // Free the allocated memory
//     free(arr);

//     return 0;
// }