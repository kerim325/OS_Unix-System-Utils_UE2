#include <iostream>
extern "C"
{
    #include <sys/utsname.h>
}

int main() 
{
    struct utsname struct_info;
    uname(&struct_info);

    size_t i {0};
    std::string op = "OS: ";

    while(struct_info.sysname[i] != '\0')
        op += struct_info.sysname[i++];

    op += "\nHostname: "; i=0;
    while(struct_info.nodename[i] != '\0')
        op += struct_info.nodename[i++];

    op += "\nRelease: "; i=0;
    while(struct_info.release[i] != '\0')
        op += struct_info.release[i++];

    op += "\nVersion: "; i=0;
    while(struct_info.version[i] != '\0')
        op += struct_info.version[i++];

    op += "\n";
    std::cout << op;

    return 0;
}