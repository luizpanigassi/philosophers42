/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:44:00 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/19 17:12:31 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_valid_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return 0;
	}

	int i = 1;
	while (i < argc)
	{
		char *endptr;
		long val = strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || val <= 0 || val > INT_MAX)
		{
			printf("Error: Invalid argument %s\n", argv[i]);
			return 0;
		}
		i++;
	}

	return 1;
}

size_t get_current_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void print_formatted_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct tm *tm_info = localtime(&tv.tv_sec);

	printf("[%02d:%02d:%02d.%03ld] ",
		   tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec, tv.tv_usec / 1000);
}
