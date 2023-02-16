extern "C"
{
    #include <sys/procfs.h>
}
#include <iostream>
#include <fstream>
#include <filesystem>


int main() 
{
   std::string op = "[";
    for (auto entry : std::filesystem::directory_iterator{"/proc"})
    {
        if(isdigit(std::string(entry.path()).at(6)))
        {            
            try
            {
               std::string stt {}, cl {}, x { std::filesystem::read_symlink(std::string(entry.path()) + "/exe") };
                std::fstream fstate, fmaps, fcmd;

                fstate.open(std::string(entry.path()) + "/status", std::ios::in);
                if (fstate.is_open())
                {
                   std::string temp;
                    while(getline(fstate, temp))
                    {
                        if(temp.find("State") ==std::string::npos)
                            continue;
                        stt = temp.at(7);
                        break;
                    }
                    fstate.close();
                }

                long base_addr {0};
                fmaps.open(std::string(entry.path()) + "/maps", std::ios::in);
                if (fmaps.is_open())
                {
                   std::string temp;
                    while(getline(fmaps, temp))
                    {
                        if(temp.find(x) ==std::string::npos)
                            continue;
                        base_addr = stol (temp.substr(0, temp.find('-')),nullptr,16);
                        break;
                    }
                    fmaps.close();
                }

                fcmd.open(std::string(entry.path()) + "/cmdline", std::ios::in);
                if (fcmd.is_open())
                {
                    std::string temp;
                    cl += "[";
                    while(getline(fcmd, temp))
                    {
                        temp.pop_back();
                        cl += "\"";
                        for(auto charr : temp)
                        {
                            if(charr == ' ' || charr =='\t' || charr =='\n')
                                cl += "\",\"";
                            else if(charr == '\"' || charr == '\\')
                                cl.push_back('\\'), cl.push_back(charr);
                            else
                                cl += charr;
                        }
                        cl += "\"";
                    }
                    cl += "]";
                    fcmd.close();
                }

                op += "{\"pid\":" + std::string(entry.path()).substr(6) + "," + "\"exe\":\"" + x + "\","
                        + "\"cwd\":\"" +std::string(std::filesystem::read_symlink(std::string(entry.path())+"/cwd")) + "\"," + "\"base_address\":"
                        + std::to_string(base_addr) + "," + "\"state\":\"" + stt +"\","
                        + "\"cmdline\":" + cl + "},";
            }
            catch(std::filesystem::filesystem_error&)
            {
                // cerr << e.what();
                // bei error darf nichts geschehen, da dieser prozess einfach übersprungen werden soll
            }
        }
    }
    *op.rbegin() = ']';
    std::cout << op;
    return 0;
}