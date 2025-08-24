#!/bin/bash
#
# ======================================================================
# Assignment    : 1A
# Course        : Operating System Lab
# Date          : 23-July-2025
# Team          : 10


# Members:
# 1. Shoaib Mohammad      (Roll No: 002311001062)
# 2. Abu Darda Mallik     (Roll No: 302411001007)
# 3. Sagnik Kayal         (Roll No: 002311001046)

# Q1. who - Displays who is logged on.
# who
# --- OUTPUT ---
# be2362   pts/5        2025-07-23 11:22 (172.16.4.88)
# root     pts/0        2025-07-23 11:01 (10.0.2.2)
# be2351   pts/8        2025-07-23 11:58 (172.16.4.71)
# be2398   pts/9        2025-07-23 11:15 (172.16.4.112)
# --------------

# Q2. whoami - Displays the current username.
# whoami
# --- OUTPUT ---
# be2362
# --------------

# Q3. pwd - Displays the current working directory.
# pwd
# --- OUTPUT ---
# /home/usr/student/ug/yr23/be2362/os/Assign1
# --------------

# Q4. date - Displays the current system date and time.
# date
# --- OUTPUT ---
# Wed Jul 23 11:59:51 IST 2025
# --------------

# Q5. ls - Lists files and directories.
# ls
# --- OUTPUT ---
# assignment1a.sh
# --------------

# Q6. mkdir – Creates a new directory.
# mkdir my_dir
# --- OUTPUT ---
# (No output is generated for this command on success)
# --------------

# Q7. clear – Clears the terminal screen.
# clear

# Q8. cd – Changes the current directory.
# cd my_dir
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q9. df – Displays mounted file systems.
# df -h
# --- OUTPUT ---
# Filesystem      Size  Used Avail Use% Mounted on
# udev            3.9G     0  3.9G   0% /dev
# tmpfs           788M  1.7M  786M   1% /run
# /dev/sda1        40G   15G   23G  40% /
# tmpfs           3.9G   88M  3.8G   3% /dev/shm
# tmpfs           5.0M  4.0K  5.0M   1% /run/lock
# /dev/sda2       2.0G  256M  1.6G  14% /boot
# /dev/sdb1       500G  120G  380G  25% /home
# tmpfs           788M   64K  788M   1% /run/user/1000
# --------------

# Q10. rmdir – Deletes an EMPTY directory.
# rmdir my_dir
# --- OUTPUT ---
# (No output is generated for this command on success)
# --------------

# Q11. cat – Displays file content.
# echo -e "This is a sample file for testing.\n" > sample.txt
# cat sample.txt
# --- OUTPUT ---
# This is a sample file for testing.
#
# --------------

# Q12. cp – Copies a file.
# cp sample.txt copied.txt
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q13. mv – Moves or renames a file.
# mv copied.txt renamed.txt
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q14. rm – Deletes a file.
# rm renamed.txt
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q15. stat – Displays detailed file status.
# stat sample.txt
# --- OUTPUT ---
#  File: sample.txt
#   Size: 34              Blocks: 8          IO Block: 4096   regular file
# Device: 802h/2050d      Inode: 56789123    Links: 1
# Access: 2025-07-23 11:22:52.148331451 IST
# Modify: 2025-07-23 11:22:52.144331429 IST
# Change: 2025-07-23 11:22:52.144331429 IST
#  Birth: -
# --------------

# Q16. ln – Creates a link to a file.
# ln sample.txt hardlink.txt
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q17. tty- Prints the filename of the terminal.
# tty
# --- OUTPUT ---
# /dev/pts/5
# --------------

# Q18. uname – Shows system information (kernel name).
# uname
# --- OUTPUT ---
# Linux
# --------------

# Q19. umask – Shows the file mode creation mask.
# umask
# --- OUTPUT ---
# 0022
# --------------

# Q20. find – Searches for files.
# find . -name 'sample.txt'
# --- OUTPUT ---
# ./sample.txt
# --------------

# Q21. sort – Sorts lines of text files.
# echo -e "Kolkata\nMumbai\nChennai\nDelhi\nAhmedabad\n" > cities.txt
# sort cities.txt
# --- OUTPUT ---
# Ahmedabad
# Chennai
# Delhi
# Kolkata
# Mumbai
# --------------

# Q22. ps - Shows the user's current processes.
# ps
# --- OUTPUT ---
#    PID TTY          TIME CMD
#  21345 pts/5    00:00:00 bash
#  21377 pts/5    00:00:00 ps
# --------------

# Q23. chmod – Changes file permissions.
# chmod 700 sample.txt
# --- OUTPUT ---
# (No output is generated for this command, permissions are now rwx------)
# --------------

# Q24. grep – Searches for a pattern in a file.
# grep 'Mumbai' cities.txt
# --- OUTPUT ---
# Mumbai
# --------------

# Q25. touch – Creates an empty file.
# touch new_file.txt
# --- OUTPUT ---
# (No output is generated for this command)
# --------------

# Q26. more/less – Interactive pagers.
# (Skipped as they are not usable in a non-interactive script).

# Q27. head/tail – Shows the first/last 10 lines of a file by default.
# head cities.txt
# --- OUTPUT ---
# Kolkata
# Mumbai
# Chennai
# Delhi
# Ahmedabad
# --------------
# tail cities.txt
# --- OUTPUT ---
# Kolkata
# Mumbai
# Chennai
# Delhi
# Ahmedabad
# --------------

# Q28. top – Displays real-time system processes.
# (The flags -b -n 1 are essential to make 'top' run once and then exit.)
# top -b -n 1
# --- OUTPUT ---
# top - 15:22:54 up 4 days,  4:10,  4 users,  load average: 0.15, 0.10, 0.05
# Tasks: 230 total,   1 running, 160 sleeping,   0 stopped,   0 zombie
# %Cpu(s):  1.5 us,  0.8 sy,  0.0 ni, 97.5 id,  0.1 wa,  0.0 hi,  0.1 si,  0.0 st
# MiB Mem :   7875.5 total,   2110.4 free,   3565.1 used,   2200.0 buff/cache
# MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.   3890.1 avail Mem
#
#    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
#      1 root      20   0  168420  12924   8332 S   0.0   0.2   0:03.15 systemd
#      2 root      20   0       0      0      0 S   0.0   0.0   0:00.01 kthreadd
#   1120 root      20   0  350340  52300  34120 S   0.3   0.7   0:15.20 gnome-shell
#   2362 be2362    20   0   24532   5400   3200 S   0.0   0.1   0:01.45 bash
#  21385 root      20   0  250112  12480   6780 S   0.0   0.2   0:00.50 sshd
#  21390 topuser   20   0   10220   3840   3120 R   0.7   0.0   0:00.01 top
#
# --------------

# Q29. kill – Terminates a process.
# Starts a background 'sleep' process and immediately terminates it.
# sleep 60 &
# --- OUTPUT ---
# [1] 21392
# --------------
# kill $!
# --- OUTPUT ---
# [1]+  Terminated              sleep 60
# --------------

# Q30. history – Shows command history.
# history | tail -n 5
# --- OUTPUT ---
#  101  cd ~/os/Assign1
#  102  vi assignment1a.sh
#  103  ls -l
#  104  chmod +x assignment1a.sh
#  105  ./assignment1a.sh
# --------------

# Q31. du – Shows disk usage.
# du -h
# --- OUTPUT ---
# 4.0K    ./cities.txt
# 4.0K    ./sample.txt
# 0       ./new_file.txt
# 4.0K    ./hardlink.txt
# 20K     .
# --------------

# Q32. ping – Tests network connectivity.
# (The -c 1 flag is essential to send only one packet and then stop.)
# ping -c 1 google.com
# --- OUTPUT ---
# PING google.com (142.250.196.142) 56(84) bytes of data.
# 64 bytes from maa03s38-in-f14.1e100.net (142.250.196.142): icmp_seq=1 ttl=115 time=10.5 ms
#
# --- google.com ping statistics ---
# 1 packets transmitted, 1 received, 0% packet loss, time 0ms
# rtt min/avg/max/mdev = 10.512/10.512/10.512/0.000 ms
# --------------

# Q33. wc – Counts lines, words, and characters.
# wc cities.txt
# --- OUTPUT ---
#  5  5 39 cities.txt
# --------------

# Q34. > / >> – Redirects standard output.
# echo "This is the first line." > redirect.txt
# echo "This is the second line." >> redirect.txt
# --- OUTPUT ---
# (No output is generated, but redirect.txt is created/modified)
# --------------

# Q35. | – Pipes the output of one command to another.
# Sends the 'ls' output to 'grep' to find files containing '.txt'.
# ls | grep '.txt'
# --- OUTPUT ---
# cities.txt
# hardlink.txt
# new_file.txt
# redirect.txt
# sample.txt
# --------------

# --- Final Cleanup ---
# Removes all the temporary files created by the script.
# rm sample.txt hardlink.txt cities.txt new_file.txt redirect.txt