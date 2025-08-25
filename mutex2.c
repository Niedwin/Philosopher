long get_last_meal(t_philo *philo)
{
    long time;
    pthread_mutex_lock(&philo->meal_mutex);
    time = philo->last_meal;
    pthread_mutex_unlock(&philo->meal_mutex);
    return (time);
}
