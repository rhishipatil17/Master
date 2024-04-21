#ifndef MININI
#define MININI

#include<string>
#include<fstream>

class minIni
{
    public:
        minIni(std::string &filename) : m_file(filename)
        {}
        minIni(const char *filename) : m_file(filename)
        {}
        ~minIni()
        { m_file.clear(); }

        minIni* operator=(std::string filename);
        minIni* operator=(const char *filename);

        bool isPresent(void);
        bool appS(std::string data);

    private:
        std::string m_file;

};

#endif