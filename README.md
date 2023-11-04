# 42_Philosophers

## Description
This project consists of creating a program that simulates the famous Dining Philosophers problem, using multi-threads/multi-process programming with the use of mutex and semaphore.

## Prerequisites
- Nothing needed

## Usage
- `make` for creating binary
- `./philo <nbr_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> [nbr_of_times_each_philo_must_eat]` for execution
- Example: `./philo 5 800 200 200 3`

## Lessons
- Multi-threads/multi-process
- Mutex
- Semaphore
- Shared memory
- C optimization

## Resources
- [Philosophers - 42born2code (YouTube)](https://www.youtube.com/watch?v=LeV9u-l40hA "Philosophers - 42born2code (YouTube)")
- [pthread_create(3) — man](https://man7.org/linux/man-pages/man3/pthread_create.3.html "pthread_create(3) — man")
- [gettimeofday function in C](https://linuxhint.com/gettimeofday_c_language/ "gettimeofday function in C")
- [pthread_mutex_init(3p)](https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html "pthread_mutex_init(3p)")
- [Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer/ "Philosophers visualizer")
- [Tester: socrates](https://github.com/nesvoboda/socrates "Tester: socrates")
- [Tester: Philosphers-42Project-Tester](https://github.com/newlinuxbot/Philosphers-42Project-Tester "Tester: Philosphers-42Project-Tester")
- [Tester: philosophers_test](https://github.com/cacharle/philosophers_test "Tester: philosophers_test")
