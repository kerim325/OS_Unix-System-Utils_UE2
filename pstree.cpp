extern "C"
{ 
    #include <sys/procfs.h> 
}
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <set>


std::string recursion(const std::string&);

int main() 
{
    //Herausfinden, welche Prozesse die Wurzel darstellen
    std::set<std::string> s, s1;
    for(const auto& entry : std::filesystem::directory_iterator{std::filesystem::path ("/proc")})
        if(isdigit(std::string(entry.path()).at(6))) s.insert(std::string(entry.path()).substr(6));

    for(const auto& id : s) {
        std::fstream f;
        f.open("/proc/" + id + "/task/" + id + "/children", std::ios::in);
        if (f.is_open()) {
            std::string temp, alle;
            size_t i{0};

            while (getline(f, temp))
                alle += temp;
            temp.clear();

            while (i < alle.length()) {
                if (alle.at(i) == ' ') {
                    s1.insert(temp);
                    temp.clear();
                } else
                    temp.push_back(alle[i]);
                i += 1;
            }
            s1.insert(temp);
            f.close();
        }
    }
    for_each(s1.begin(), s1.end(), [&](auto p){s.erase(p);});

    std::string output = "[";
    for_each(s.begin(), s.end(), [&](auto p){ output += recursion(p); } );
    *output.rbegin() = ']';

    std::cout << output;
    return 0;
}

//Rekursiv den Prozess baum von der Wurzel beginnend hinunterarbeiten
std::string recursion(const std::string& pid)
{
    std::string name, children;
    std::fstream fname, fchild;

    fname.open("/proc/" + pid + "/status", std::ios::in);
    if(fname.is_open())
    {
        getline(fname, name);
        fname.close();
        name = name.substr(6);
    }
    for (auto& entry : std::filesystem::directory_iterator{std::filesystem::path("/proc/"+pid+"/task")})
    {
        fchild.open(std::string(entry.path()) + "/children", std::ios::in);
        if(fchild.is_open())
        {
            std::string temp, all;
            while(getline(fchild, temp))
                all += temp;

            fchild.close();
            temp.clear();
            std::vector<std::string> vec1;

            for_each(all.begin(), all.end(), [&temp, &vec1](auto cs)->void
            {
                if(cs == ' ')
                {
                    vec1.push_back(temp);
                    temp.clear();
                }
                else
                    temp += cs;
            });

            for_each(vec1.begin(), vec1.end(),
                     [&](auto p)
                     {children += recursion(p);});

        }
    }

    if(!children.empty())
        children.pop_back();

    return "{\"pid\":" +pid + "," +
           "\"name\":\"" + name + "\"," +
           "\"children\":[" + children + "]" + "},";
}