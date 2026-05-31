# Todo CLI

A simple command-line todo manager written in c++.(Basee on some minor interests, I'm developing it in my spare time...  2026/5/31)

## What I Learned

Through this project I practiced:

- C++ project structure
- CMake build system
- Interface-based design (IStorage)
- Dependency Injection
- Unit testing with GoogleTest
- Continuous Intergration with Github Actions
- Git branch workflow

## Features

- Add task
- List task
- Mark task as done
- Delete  task
- Search task
- Edit task
## Build

### Requirements

- C++17
- CMake >= 3.10

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Add a task
```bash
./todo add text
```

### List tasks
```bash
./todo list
```

### Mark a task as done
```bash
./todo done id
```

### Delete a task
```bash
./todo. delete id
```

### Search tasks
```bash
./todo search text
```

### Edit a task
```bash
./todo edit id text
```

### Testing
```bash
./todo_tests
```

## Technologies Used

- C++17
- CMake
- nlohmann/json
- spdlog
- GoogleTest
- Github Actions