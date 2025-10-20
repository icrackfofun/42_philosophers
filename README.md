# Philosophers

## Overview
This project is an implementation of the Dining Philosophers Problem using C. It focuses on Concurrency and synchronization of multiple threads with the use of Mutexes. This project was developed during my time at 42 Lisbon.

---

## Features

- Implements a simulation of the Dining Philosophers problem:
  - Philosophers can **think**, **eat**, and **sleep** in cycles
  - Uses **threads** to represent each philosopher
  - Synchronizes access to forks using **mutexes**

- Deadlock Prevention:
  - Ensures no philosopher waits indefinitely
  - Proper locking and unlocking of resources

- Accurate timing for actions:
  - Controlled using `gettimeofday` and `usleep`
  - Logs philosopher actions with timestamps

- Handles program termination gracefully:
  - Stops simulation when a philosopher dies
  - Frees all allocated resources
  - Proper cleanup of mutexes and threads

---

## Installation

1. **Clone the repository**
```bash
git clone https://github.com/icrackfofun/philosophers.git
```

2. **Compile the program**
```bash
make
```

## Usage

**Run the program**

```bash
./philo `number_of_philosophers` `time_to_die` `time_to_eat` `time_to_sleep` `optional: number_of_times_each_philosopher_must_eat`
```

**Example**

$ ./philo 5 800 200 200

- `number_of_philosophers` Number of philosophers in the simulation

- `time_to_die` Time (ms) before a philosopher dies without eating

- `time_to_eat` Time (ms) a philosopher takes to eat

- `time_to_sleep` Time (ms) a philosopher spends sleeping

- `number_of_times_each_philosopher_must_eat` (optional): Stops simulation after each philosopher eats this many times
