extern "C"
{
    #include <signal.h>
}
#include <fstream>
#include <filesystem>


int main(int, char** argv)
{
    for (const auto& entry : std::filesystem::directory_iterator{"/proc"})
    {
        try
        {
            if(isdigit(std::string(entry.path()).at(6)))
            {
                std::fstream f;
                std::string isim;
                f.open("/proc/" + std::string(entry.path()).substr(6) + "/status", std::ios::in);
                if (f.is_open())
                {
                    getline(f, isim);
                    f.close();
                    isim = isim.substr(6);
                }
                if (isim.find(argv[1]) != std::string::npos)
                    kill(static_cast<pid_t>(stoi(std::string(entry.path()).substr(6))), 9);
            }
        }
        catch(std::filesystem::filesystem_error&)
        {
            //cout << e.what();
            //Wenn kein Zugriff auf Proc, dann soll nichts geschehen
        }
    }
}
