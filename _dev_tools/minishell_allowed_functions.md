# Minishell — Allowed Functions (42) Cheat Sheet

> Headers indicate what to `#include`.  
> **Link** shows extra libraries to add in your Makefile. If it says **none (libc)**, no extra link flag is needed beyond the default C runtime.  
> On most 42 setups you’ll need: **`-lreadline`** for readline/history, and **`-ltermcap`** (or sometimes **`-lncurses`**) for termcap/terminfo functions.

---

## Readline & History

### `readline`
- **Prototype**
  ```c
  char *readline(const char *prompt);
  ```
- **Headers**: `<readline/readline.h>`  
- **Description**: Read a line of input with line editing; returns malloc’ed string (NULL on EOF).  
- **Link**: `-lreadline`

### `rl_clear_history`
- **Prototype**
  ```c
  void rl_clear_history(void);
  ```
- **Headers**: `<readline/history.h>`  
- **Description**: Clear the interactive history list.  
- **Link**: `-lreadline` *(on some systems also `-lhistory`)*

### `rl_on_new_line`
- **Prototype**
  ```c
  int rl_on_new_line(void);
  ```
- **Headers**: `<readline/readline.h>`  
- **Description**: Tell readline we are on a new line (use with `rl_replace_line` / `rl_redisplay`).  
- **Link**: `-lreadline`

### `rl_replace_line`
- **Prototype**
  ```c
  void rl_replace_line(const char *text, int clear_undo);
  ```
- **Headers**: `<readline/readline.h>`  
- **Description**: Replace the current input buffer; optionally clear undo history.  
- **Link**: `-lreadline`

### `rl_redisplay`
- **Prototype**
  ```c
  void rl_redisplay(void);
  ```
- **Headers**: `<readline/readline.h>`  
- **Description**: Refresh the screen to show the current line buffer.  
- **Link**: `-lreadline`

### `add_history`
- **Prototype**
  ```c
  void add_history(const char *line);
  ```
- **Headers**: `<readline/history.h>`  
- **Description**: Append a line to the history list.  
- **Link**: `-lreadline` *(on some systems also `-lhistory`)*

---

## Stdio / Memory / I/O Basics

### `printf`
- **Prototype**
  ```c
  int printf(const char *format, ...);
  ```
- **Headers**: `<stdio.h>`  
- **Description**: Formatted output to stdout.  
- **Link**: none (libc)

### `malloc`
- **Prototype**
  ```c
  void *malloc(size_t size);
  ```
- **Headers**: `<stdlib.h>`  
- **Description**: Allocate dynamic memory.  
- **Link**: none (libc)

### `free`
- **Prototype**
  ```c
  void free(void *ptr);
  ```
- **Headers**: `<stdlib.h>`  
- **Description**: Free dynamic memory.  
- **Link**: none (libc)

### `write`
- **Prototype**
  ```c
  ssize_t write(int fd, const void *buf, size_t count);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Write bytes to a file descriptor.  
- **Link**: none (libc)

### `read`
- **Prototype**
  ```c
  ssize_t read(int fd, void *buf, size_t count);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Read bytes from a file descriptor.  
- **Link**: none (libc)

### `access`
- **Prototype**
  ```c
  int access(const char *pathname, int mode);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Check file accessibility (existence/permissions).  
- **Link**: none (libc)

### `open`
- **Prototype**
  ```c
  int open(const char *pathname, int flags, ... /* mode_t mode */);
  ```
- **Headers**: `<fcntl.h>`  
- **Description**: Open a file; may create based on flags/mode.  
- **Link**: none (libc)

### `close`
- **Prototype**
  ```c
  int close(int fd);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Close a file descriptor.  
- **Link**: none (libc)

---

## Process Control & Signals

### `fork`
- **Prototype**
  ```c
  pid_t fork(void);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Create a child process by duplicating the caller.  
- **Link**: none (libc)

### `wait`
- **Prototype**
  ```c
  pid_t wait(int *wstatus);
  ```
- **Headers**: `<sys/wait.h>`  
- **Description**: Wait for any child to change state.  
- **Link**: none (libc)

### `waitpid`
- **Prototype**
  ```c
  pid_t waitpid(pid_t pid, int *wstatus, int options);
  ```
- **Headers**: `<sys/wait.h>`  
- **Description**: Wait for a specific child with options (e.g., `WNOHANG`).  
- **Link**: none (libc)

### `wait3`
- **Prototype**
  ```c
  pid_t wait3(int *wstatus, int options, struct rusage *rusage);
  ```
- **Headers**: `<sys/wait.h>`, `<sys/resource.h>`  
- **Description**: Wait for any child and collect resource usage.  
- **Link**: none (libc)

### `wait4`
- **Prototype**
  ```c
  pid_t wait4(pid_t pid, int *wstatus, int options, struct rusage *rusage);
  ```
- **Headers**: `<sys/wait.h>`, `<sys/resource.h>`  
- **Description**: Wait for a specific child and collect resource usage.  
- **Link**: none (libc)

### `signal`
- **Prototype**
  ```c
  void (*signal(int sig, void (*func)(int)))(int);
  ```
- **Headers**: `<signal.h>`  
- **Description**: Install a simple signal handler (less precise than `sigaction`).  
- **Link**: none (libc)

### `sigaction`
- **Prototype**
  ```c
  int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
  ```
- **Headers**: `<signal.h>`  
- **Description**: Install signal handlers with fine‑grained control.  
- **Link**: none (libc)

### `sigemptyset`
- **Prototype**
  ```c
  int sigemptyset(sigset_t *set);
  ```
- **Headers**: `<signal.h>`  
- **Description**: Initialize an empty signal set.  
- **Link**: none (libc)

### `sigaddset`
- **Prototype**
  ```c
  int sigaddset(sigset_t *set, int signum);
  ```
- **Headers**: `<signal.h>`  
- **Description**: Add a signal to a signal set.  
- **Link**: none (libc)

### `kill`
- **Prototype**
  ```c
  int kill(pid_t pid, int sig);
  ```
- **Headers**: `<signal.h>`  
- **Description**: Send a signal to a process or process group.  
- **Link**: none (libc)

### `exit`
- **Prototype**
  ```c
  void exit(int status);
  ```
- **Headers**: `<stdlib.h>`  
- **Description**: Terminate the process with given status.  
- **Link**: none (libc)

---

## Directories / File Status / Paths

### `getcwd`
- **Prototype**
  ```c
  char *getcwd(char *buf, size_t size);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Get current working directory; returns `buf` or malloc’ed string if `buf == NULL`.  
- **Link**: none (libc)

### `chdir`
- **Prototype**
  ```c
  int chdir(const char *path);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Change current working directory.  
- **Link**: none (libc)

### `stat`
- **Prototype**
  ```c
  int stat(const char *pathname, struct stat *buf);
  ```
- **Headers**: `<sys/stat.h>`  
- **Description**: Get file status by path.  
- **Link**: none (libc)

### `lstat`
- **Prototype**
  ```c
  int lstat(const char *pathname, struct stat *buf);
  ```
- **Headers**: `<sys/stat.h>`  
- **Description**: Like `stat` but does not follow symlinks.  
- **Link**: none (libc)

### `fstat`
- **Prototype**
  ```c
  int fstat(int fd, struct stat *buf);
  ```
- **Headers**: `<sys/stat.h>`  
- **Description**: Get file status by file descriptor.  
- **Link**: none (libc)

### `unlink`
- **Prototype**
  ```c
  int unlink(const char *pathname);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Remove a name from the filesystem (delete a file).  
- **Link**: none (libc)

### `execve`
- **Prototype**
  ```c
  int execve(const char *pathname, char *const argv[], char *const envp[]);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Execute a program, replacing the current process image.  
- **Link**: none (libc)

### `dup`
- **Prototype**
  ```c
  int dup(int oldfd);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Duplicate a file descriptor to the lowest available number.  
- **Link**: none (libc)

### `dup2`
- **Prototype**
  ```c
  int dup2(int oldfd, int newfd);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Duplicate a file descriptor to a specified descriptor.  
- **Link**: none (libc)

### `pipe`
- **Prototype**
  ```c
  int pipe(int pipefd[2]);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Create a unidirectional data channel (`pipefd[0]=read`, `pipefd[1]=write`).  
- **Link**: none (libc)

---

## Directory Streams

### `opendir`
- **Prototype**
  ```c
  DIR *opendir(const char *name);
  ```
- **Headers**: `<dirent.h>`  
- **Description**: Open a directory stream.  
- **Link**: none (libc)

### `readdir`
- **Prototype**
  ```c
  struct dirent *readdir(DIR *dirp);
  ```
- **Headers**: `<dirent.h>`  
- **Description**: Read next directory entry.  
- **Link**: none (libc)

### `closedir`
- **Prototype**
  ```c
  int closedir(DIR *dirp);
  ```
- **Headers**: `<dirent.h>`  
- **Description**: Close a directory stream.  
- **Link**: none (libc)

---

## Error Reporting / TTY / IOCTL / Env

### `strerror`
- **Prototype**
  ```c
  char *strerror(int errnum);
  ```
- **Headers**: `<string.h>`  
- **Description**: Return a pointer to a string describing the error code.  
- **Link**: none (libc)

### `perror`
- **Prototype**
  ```c
  void perror(const char *s);
  ```
- **Headers**: `<stdio.h>`  
- **Description**: Print a descriptive message for the last error (`errno`).  
- **Link**: none (libc)

### `isatty`
- **Prototype**
  ```c
  int isatty(int fd);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Test whether a file descriptor refers to a terminal.  
- **Link**: none (libc)

### `ttyname`
- **Prototype**
  ```c
  char *ttyname(int fd);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Return the pathname of the terminal device.  
- **Link**: none (libc)

### `ttyslot`
- **Prototype**
  ```c
  int ttyslot(void);
  ```
- **Headers**: `<unistd.h>`  
- **Description**: Return the index of the current terminal in utmp (legacy, optional).  
- **Link**: none (libc)

### `ioctl`
- **Prototype**
  ```c
  int ioctl(int fd, unsigned long request, ...);
  ```
- **Headers**: `<sys/ioctl.h>`  
- **Description**: Device-specific input/output control operations.  
- **Link**: none (libc)

### `getenv`
- **Prototype**
  ```c
  char *getenv(const char *name);
  ```
- **Headers**: `<stdlib.h>`  
- **Description**: Get environment variable value (do not free the returned pointer).  
- **Link**: none (libc)

---

## Termcap / Terminfo (Optional Utilities)

### `tcsetattr`
- **Prototype**
  ```c
  int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
  ```
- **Headers**: `<termios.h>`  
- **Description**: Set terminal attributes (canonical mode, echo, etc.).  
- **Link**: none (libc)

### `tcgetattr`
- **Prototype**
  ```c
  int tcgetattr(int fd, struct termios *termios_p);
  ```
- **Headers**: `<termios.h>`  
- **Description**: Get terminal attributes.  
- **Link**: none (libc)

### `tgetent`
- **Prototype**
  ```c
  int tgetent(char *bp, const char *name);
  ```
- **Headers**: `<term.h>`  
- **Description**: Load terminal capability database entry for `TERM`.  
- **Link**: `-ltermcap` *(or `-lncurses` depending on platform)*

### `tgetflag`
- **Prototype**
  ```c
  int tgetflag(const char *id);
  ```
- **Headers**: `<term.h>`  
- **Description**: Query a boolean terminal capability.  
- **Link**: `-ltermcap` *(or `-lncurses`)*

### `tgetnum`
- **Prototype**
  ```c
  int tgetnum(const char *id);
  ```
- **Headers**: `<term.h>`  
- **Description**: Query a numeric terminal capability.  
- **Link**: `-ltermcap` *(or `-lncurses`)*

### `tgetstr`
- **Prototype**
  ```c
  char *tgetstr(const char *id, char **area);
  ```
- **Headers**: `<term.h>`  
- **Description**: Query a string terminal capability.  
- **Link**: `-ltermcap` *(or `-lncurses`)*

### `tgoto`
- **Prototype**
  ```c
  char *tgoto(const char *cap, int col, int row);
  ```
- **Headers**: `<term.h>`  
- **Description**: Build cursor‑addressing control sequence from a capability.  
- **Link**: `-ltermcap` *(or `-lncurses`)*

### `tputs`
- **Prototype**
  ```c
  int tputs(const char *str, int affcnt, int (*putc)(int));
  ```
- **Headers**: `<term.h>`  
- **Description**: Output a termcap capability string with padding handling.  
- **Link**: `-ltermcap` *(or `-lncurses`)*

---

## Linker Flags Summary (Makefile)
- Readline / history: `-lreadline` *(sometimes also `-lhistory`)*  
- Termcap/terminfo: `-ltermcap` *(or)* `-lncurses`  
- libc functions: no extra flag needed

> Tip: on some 42 setups, you may also need to add include/library search paths for `readline`:
> ```make
> CFLAGS  += -I/usr/local/opt/readline/include
> LDFLAGS += -L/usr/local/opt/readline/lib -lreadline
> ```

