/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:14:54 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/07 19:42:58 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ARGS "Program exited. Number of arguments not sufficient..."
# define INPUT "Program exited. Input invalid..."
# define THREAD "Program exited. Thread creation failed..."
# define JOIN "Threads failed to finish execution..."
# define TIME "gettimeofday() function failed..."
# define INIT "Program failed to initialize structs.."

typedef struct s_philo
{
	int				id;
	int				num_of_meals;
	size_t			last_ate;
	size_t			time_to_die;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_data	*general;

}					t_philo;

typedef struct s_data
{
	int				ph_count;
	int				must_eat;
	int				all_ate;
	int				dead;
	size_t			time_to_eat;
	size_t			time_to_die;
	size_t			time_to_sleep;
	size_t			begin_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	eating;
	pthread_mutex_t	ate;
	pthread_mutex_t	printing;
	struct s_philo	*philos;

}					t_data;

/*VALIDATING THE INPUT*/
int					input(int argc, char **argv);
int					one_philo(t_philo *philos);

/*ERROR IN PROGRAM*/
int					error_msg(char *msg);
int					free_struct(t_data *general);
int					destroy_mutex(t_data *general);
int					thread_creation_failed(int i, t_data *general);

/*THREADS*/
int					threads(t_data *general);
int					join_threads(t_data *general);

/*TIME MANAGEMENT*/
void				ft_usleep(size_t milliseconds, t_philo *philos);
size_t				log_event(void);
void				print_event(t_philo *philos, int id, char *msg);
void				time_manipulation(t_data *general, t_philo *philos);

/*PHILOSOPHERS ROUTINE*/
void				*routine(void *ptr);
void				fork_etiquette(t_philo *philos);
void				eating(t_philo *philos);
void				thinking(t_philo *philos);
void				sleeping(t_philo *philos);

/*MONITORING THE PHILOSOPHERS*/
void				monitor(t_data *general);
int					check_meal(t_philo *philos);
int					check_meal_helper(t_philo *philos);
int					meal_number_check(t_philo *philos);
int					philo_all_ate(t_philo *philos);
int					philo_is_dead(t_philo *philos);

/*INITIALIZING*/
int					init_philos(t_data *general);
int					init_mutex(t_data *general);
int					init(t_data *general, char **argv);

/*UTILS*/
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_itoa(int n);
int					ft_atoi(const char *str);
int					ft_isdigit(int arg);

#endif
