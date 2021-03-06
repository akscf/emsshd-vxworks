/**
 *
 * Copyright (C) AlexandrinKS
 * https://akscf.org/
 **/
#include "vxssh.h"

#ifdef VXSSH_INCLUDE_DEBUG_FUNCTIONS
static char b2hc (uint8_t b)  {
    return b + (b > 9 ? 'a' - 10 : '0');
}

void vxssh_hexdump2(const char *msg, const void *p, size_t len) {
    if(msg) {
        vxssh_log_debug(msg);
    }
    vxssh_hexdump(p,len);
}

void vxssh_hexdump(const void *p, size_t len) {
    char lbuf[255];
    char *xp = NULL;
    const char *buf = p;
    int j, ofs = 0, n = 0;
    int i, pos = 0;
    char v;

    if (!buf) { return; }
    for (i=0; i < len; i += 16) {
        xp = (void *)lbuf;
        n = sprintf(xp, "%08x ", i);
        xp += n;

        for (j=0; j<16; j++) {
            pos = i + j;
            if (pos < len) {
                const char cb = buf[pos] & 0xff;
                *xp = ' '; xp++;
                *xp = b2hc((cb >> 4) & 0xf); xp++;
                *xp = b2hc(cb & 0xf); xp++;
            } else {
                *xp = ' '; xp++;
                *xp = ' '; xp++;
                *xp = ' '; xp++;
            }
            if (j == 7) {
                *xp = ' '; xp++;
                *xp = ' '; xp++;
            }
        }
        *xp = ' '; xp++;
        *xp = ' '; xp++;
        *xp = '|'; xp++;

        for (j=0; j<16; j++) {
            pos = i+j;
            if (pos >= len) break;
            v = buf[pos];
            //
            *xp = isprint(v) ? v : '.';
            xp++;
            //
            if (j == 7) {
                *xp = ' ';
                xp++;
            }
        }
        *xp = '|'; xp++;
        *xp = '\0';
        //
        vxssh_log_debug((char *)lbuf);
    }
}

#endif

