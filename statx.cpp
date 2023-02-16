extern "C"
{
	#include <sys/stat.h>
	#include <fcntl.h>
}
#include<iostream>


int main(int argc, char* argv[])             //argv[1] absoluter Pfad
{
    std::string op;
    struct statx sax;

    // 1.statx-Aufruf: Berechtigungen
    statx(AT_FDCWD, argv[1], 0, 0x00000002U, &sax);
    if (sax.stx_mask & 0x00000002U)
    {
        if (sax.stx_mode & 0400) op += 'r';
        else op += '-';
        if (sax.stx_mode & 0200) op += 'w';
        else op += '-';
        if (sax.stx_mode & 0100) op += 'x';
        else op += '-';
        if (sax.stx_mode & (0400 >> 3)) op += 'r';
        else op += '-';
        if (sax.stx_mode & (0200 >> 3)) op += 'w';
        else op += '-';
        if (sax.stx_mode & (0100 >> 3)) op += 'x';
        else op += '-';
        if (sax.stx_mode & ((0400 >> 3) >> 3)) op += 'r';
        else op += '-';
        if (sax.stx_mode & ((0200 >> 3) >> 3)) op += 'w';
        else op += '-';
        if (sax.stx_mode & ((0100 >> 3) >> 3)) op += 'x';
        else op += '-';
    }
    op += '\n';

    // 2.statx-Aufruf: UID/GID
    statx(AT_FDCWD, argv[1], 0, 0x00000010U | 0x00000008U, &sax);
    if (sax.stx_mask & 0x00000008U)
    {
        op += "UID: ";
        op += std::to_string(sax.stx_uid);
        op += ", ";
    }
    if (sax.stx_mask & 0x00000010U)
    {
        op += "GID: ";
        op += std::to_string(sax.stx_gid);
        op += "\n";
    }

    // 3.statx-Aufruf: Dateigröße
    statx(AT_FDCWD, argv[1], 0, 0x00000200U, &sax);
    if (sax.stx_mask & 0x00000200U)
    {
        op += "Size: ";
        op += std::to_string(sax.stx_size);
        op += "\n";
    }

    std::cout << op;

    if (argc == 2)
        return 0;
    return -1;
}