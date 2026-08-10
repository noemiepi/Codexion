<div align="center">
    <i>This project has been created as part of the 42 curriculum by npillet</i>
    <h1>Codexion</h1>
    <h3>Master the race for resources before the deadline masters you</h3>
</div>

## Description
A **thread** is the smallest unit of processing that can be scheduled by an operating system. It is a sequence of instructions within a program that can be managed independently.<br>
Threads share the same process resources, including memory and file descriptors, but they run independently and can be executed simultaneously, allowing for multitasking within a single program.

A **mutex** is a **MUT***ual* **EX***clusion* device, and is useful for protecting shared data structures from concurrent modifications, and implementing critical sections and monitors.<br>
A mutex has two possible states: unlocked (not owned by any thread), and locked (owned by one thread).<br>
A mutex can never be owned by two different threads simultaneously.

In this project, a defined numbers of coders are created and put in a circle. For each of them, a dongle is also created. These dongles are between each coders.<br>
Here is a visual representation:

```mermaid
flowchart LR
    classDef finish fill:#e8f5e9,stroke:#388e3c,stroke-width:2px,color:#333;

    A(Coder 1) ---|Dongle 1| B
    B(Coder 2) ---|Dongle 2| C
    C(Coder 3) ---|Dongle 3| D
    D(Coder 4) ---|Dongle 4| E
    E(Coder 5) ---|Dongle 5| A

    class A,B,C,D,E finish
    linkStyle default stroke:green;
```

Each coders is represented by a thread and needs two dongles to compile and this is where the challenge lies. For this project, the coders need to hit their target compile numbers before burning out. However, if one of them burns out before reaching its goal, the program stops.

Every action each coders take needs to be printed inside the terminal. Below is an exemple of the desired terminal output:
```bash
timestamp_in_ms X has taken a dongle
timestamp_in_ms X is compiling
timestamp_in_ms X is debugging
timestamp_in_ms X is refactoring
timestamp_in_ms X burned out
```

## Instructions
This first command compile the project:
```bash
make
```

To run the program, the command below can be used:
```bash
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> <time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

Here is a list of every parameters needed to run the program:

| Parameter | Limits | Description |
| --- | --- | --- |
| **number_of_coders** | Between 1 and 300 | The numbers of coders, and dongles. |
| **time_to_burnout** | Above or equal to 1 | The time limit a coder has before burning out (in milliseconds) |
| **time_to_compile** | Above or equal to 1 | The time a coder holds two dongles at once to compile (in milliseconds) |
| **time_to_debug** | Above or equal to 1 | The time a coder takes to debug (in milliseconds) |
| **time_to_refactor** | Above or equal to 1 | The time a coder takes to be able to code again (in milliseconds) |
| **number_of_compiles_required** | Above or equal to 1 |  |
| **dongle_cooldown** | Above or equal to 1 | The time a dongle to be used once again (in milliseconds) |
| **scheduler** | `fifo` (First In, First Out) or `edf` (Earliest Deadline First) | Choose the priority order of the coders |

## Blocking cases handled
- **Deadlock Prevention**</br>
&emsp;To be able to prevent one, knowing Coffman's condition can help. These conditions are listed below:
  - Mutual Exclusion
  - Circular Wait
  - Hold and Wait
  - No pre-emption

</br>

- **Starvation Prevention**</br>
&emsp;

- **Cooldown Handling**</br>
&emsp;

- **Precise Burnout Detection**</br>
&emsp;

- **Log Serialization**</br>
&emsp;

*describing all the concurrency issues addressed in your solution (e.g., deadlock prevention and Coffman’s conditions, starvation prevention, cooldown handling, precise burnout detection, and log serialization).*

## Thread synchronization mechanisms
Two kinds of thread synchronization mechanisms are used in this program to handle shared ressources such as dongles, logging and monitor state:
- `pthread_mutex_t`
  - l
- `pthread_cond_t`
  - j


*Include examples of how race conditions are prevented and how thread-safe communication is achieved between coders and the monitor.*

Below is a chart showing how a coder works:
```mermaid
flowchart TD

    classDef start fill:#eceff1,stroke:#607d8b,stroke-width:2px,color:#333;
    classDef take_dongle fill:#fff3e0,stroke:#f57c00,stroke-width:2px,color:#333;
    classDef coder_compile fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px,color:#333;
    classDef finish fill:#e8f5e9,stroke:#388e3c,stroke-width:2px,color:#333;

    classDef dongle stroke:#fff3e0,stroke-width:2px;
    classDef compile stroke:#f3e5f5,stroke-width:2px;

    A(Coder) --> B(Takes the first dongle)

    subgraph Dongles
    B --> C{{Is the second dongle free?}}
    C -->|Yes| D(Takes the second dongle)
    C -->|No| E(Drops the first dongle)
    end

    subgraph Compile
    E -->|Waits| B
    D --> F(Compiles with two dongles)
    F --> G(Releases the dongles)
    G --> H(Debugs)
    H --> I(Refractors)
    I --> J{{Finished every compiles?}}
    J -->|Yes| K(End)
    J -->|No| B
    end

    class Dongles dongle
    class Compile compile

    class A start
    class B,C,D,E take_dongle
    class F,G,H,I,J,K coder_compile
    class K finish

    linkStyle default stroke:gray;
```
If they reach their burnout during this loop, the entire program will stop.

The monitor will look over every coder present and check if one of them burned out, causing the program to come to an end.

In this program, the user has to choose a scheduler between `FIFO (First In, First Out)` and `EDF (Earliest Deadline First)`. They will determine in which order the coder goes.</br>
For `FIFO`, the coders are put in a queue based on a first come, first save logic. Once the first finishes a compile, it leaves the queue to enter it back in the last position.
As for `EDF`, the coders are placed in a heap based on their burnout. Lowest one has priority and is therefore first.
To visualize both scheduler, there is a side by side representation below with 7 coders:

```mermaid
flowchart TD
    classDef coders fill:#fff3e0,stroke:#f57c00,stroke-width:2px,color:#333;
    classDef fifo stroke:#fff3e0,stroke-width:2px;

    subgraph FIFO
    H(Coder 1) --> I(Coder 3)
    I --> J(Coder 4)
    J --> K(Coder 2)
    K --> L(Coder 5)
    L --> M(Coder 7)
    M --> N(Coder 6)
    end

    class FIFO fifo
    class H,I,J,K,L,M,N coders

    linkStyle default stroke:orange;
```

```mermaid
flowchart TD

    classDef start fill:#eceff1,stroke:#607d8b,stroke-width:2px,color:#333;
    classDef next_level fill:#fff3e0,stroke:#f57c00,stroke-width:2px,color:#333;
    classDef sub_levels fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px,color:#333;
    classDef other_sublevel fill:#e8f5e9,stroke:#388e3c,stroke-width:2px,color:#333;
    classDef edf stroke:#fff3e0,stroke-width:2px;

    subgraph EDF
    B(Coder 1) --> A(Coder 5)
    C(Coder 6) --> A
    D(Coder 2) --> B
    E(Coder 4) --> B
    F(Coder 7) --> C
    G(Coder 3) --> C
    end

    class EDF edf
    class A start
    class B,C next_level
    class D,E sub_levels
    class F,G other_sublevel

    linkStyle default stroke:gray;
```

## Resources
### Notions
#### Threads
- https://dev.to/emanuelgustafzon/mastering-concurrency-in-c-with-pthreads-a-comprehensive-guide-56je

- https://www.geeksforgeeks.org/c/multithreading-in-c/

#### Mutex
- https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/#what-is-a-mutex-

#### Deadlock
- https://stackoverflow.com/questions/34512/what-is-a-deadlock

- https://csresources.github.io/SystemProgrammingWiki/SystemProgramming/Deadlock,-Part-2:-Deadlock-Conditions/

#### FIFO (First In, First Out)
- https://dev.to/pmbanugo/write-your-own-fifo-queue-an-essential-data-structure-for-modern-systems-2kjn

- https://medium.com/@noransaber685/understanding-queue-data-structures-in-c-the-first-in-first-out-principle-fbd1f89d40dc

#### EDF (Earliest Deadline First)
- https://www.w3schools.com/dsa/dsa_data_binarytrees.php

- https://data-flair.training/blogs/binary-tree-in-c/

### GitHub
- [Overtekk](https://github.com/Overtekk/Codexion)

- [buchy16](https://github.com/buchy16/Codexion)
