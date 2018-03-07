#include "tcpheader.h"

int getSourcePort(const unsigned char *tcp_hdr) {
    int res = 0;
    
    for (int octet = 0; octet < 2; octet++) {
        unsigned char tcp_octet = *(tcp_hdr + octet);
        res |= tcp_octet << (1 - octet) * 8;
    }

    return res;
}

int getDestinationPort(const unsigned char *tcp_hdr) {
    int res = 0;

    for (int octet = 2; octet < 4; octet++) {
        unsigned char tcp_octet = *(tcp_hdr + octet);
        res |= tcp_octet << (3 - octet) * 8;
    }

    return res;
}

void setSourcePort(unsigned char *tcp_hdr, int port) {
    for (int octet = 0; octet < 2; octet++) {
        *(tcp_hdr + octet) = 0;
        *(tcp_hdr + octet) |= (port >> (1 - octet) * 8) & 0xff;
    }
}

void setDestinationPort(unsigned char *tcp_hdr, int port) {
    for (int octet = 2; octet < 4; octet++) {
        *(tcp_hdr + octet) = 0;
        *(tcp_hdr + octet) |= (port >> (3 - octet) * 8) & 0xff;
    }
}

int getAckFlag(const unsigned char *tcp_hdr) {
    unsigned char tcp_octet = *(tcp_hdr + 13);
    int res = (tcp_octet >> 4) & 1;

    return res;
}

void setAckFlag(unsigned char *tcp_hdr, int flag) {
    if (flag) {
        *(tcp_hdr + 13) |= (1 << 4);
    } else {
        *(tcp_hdr + 13) &= ~(1 << 4);
    }
}

int getDataOffset(const unsigned char *tcp_hdr) {
    int res = 0;

    unsigned char tcp_octet = *(tcp_hdr + 12);
    res |= (tcp_octet >> 4) & 0x0f;

    return res;
}

void setDataOffset(unsigned char *tcp_hdr, int offset) {
    *(tcp_hdr + 12) &= 0x0f;
    *(tcp_hdr + 12) |= (0x0f & offset) << 4;
}

