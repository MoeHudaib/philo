/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohammad <mohammad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 16:34:54 by mohammad          #+#    #+#             */
/*   Updated: 2025/10/11 21:52:04 by mohammad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include "../parse/parse.h"
#include "../validation/validation.h"

typedef struct s_philosopher
{
    int             id;
    int             philo_no;
    long long       last_meal_time;
    long long       time_to_die;
    long long       time_to_eat;
    long long       time_to_sleep;
    int             meals_eaten;
    pthread_mutex_t left;
    pthread_mutex_t right;
    pthread_t       thread;
}                   t_philosopher;



/*     routine     */
void	detector(void *arg);
void    picking_status(int rtorlft, int tkorlv, int id);
void    eat(int id, int time_to_eat);
void    sleeping(int id, int time_to_sleep);
void    think(int id);
long long current_micros();
#endif