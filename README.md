# OS_UE-2

As part of the OS course at the University of Vienna, simplified versions of the programs uname, ps, pstree, killall and statx are to be implemented.

## uname

In this task, the syscall uname should be used (man 2 uname), which can query version information about the currently running kernel.
After querying the information, the following information should be output:

- OS: Name of the operating system
- Hostname: Current hostname of the machine
- Release: Release number of the kernel
- Version: Version of the kernel (e.g. preemptive/non-preemptive, etc.)

## ps

A simple variant of the ps Linux tool should be recreated. The following information should be collected and output in JSON format (see example):

- pid: The PID of the process
- exe: The path to the executable file of the process
- cwd: The current working directory of the process
- base_address: The base address of the executable file in memory (decimal)
- state: The current process status
- cmdline: The complete command line of the process, as an array

## pstree

In this task, all processes and their child processes should be listed hierarchically, again using JSON output. Each node in the tree should contain the following information:

- pid: The PID of the process
- name: The name of the process
- children: Array with the children of the process

## killall

This task is about building a simple version of the killall program. </br>
A string is passed as the first command line parameter (argv[1]). All processes that contain this string in the name should be terminated using the kill syscall (man 2 kill) and the SIGKILL signal.

## statx

In this task, a relatively new syscall named statx (man 2 statx) should be used
(added in Linux 4.11). This syscall allows the determination of file attributes, such as
permissions, size, etc. An absolute path is passed as the first command line
parameter (argv[1]). The attributes to be queried are:

1. Permissions: On the first statx call, only the permissions should be queried, and simply Read, Write, Execute for Owner, Group and Other. These permissions
should then be output as with ls, e.g. rwxr-xr-x.

2. UID/GID: On the second statx call, the UID of the owner and the GID
of the group of the file should be queried at the same time. The IDs should then be output as follows: UID:
1000, GID: 1000

3. File size: On the last statx call, the file size in bytes should be queried and output in decimal
e.g. 39503.
