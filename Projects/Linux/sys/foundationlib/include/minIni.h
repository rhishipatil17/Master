#ifndef MININI
#define MININI

#include<string>
#include<stack>
#include<fstream>

namespace
{
    #define MAX_LINE_SIZE 1024
}

namespace ConfigReader
{
    class minIni
    {
        public:
            minIni(std::string &filename) : m_file(filename)
            {}
            minIni(const char *filename) : m_file(filename)
            {}
            ~minIni()
            { m_file.clear(); }

            minIni* operator=(std::string &filename);
            minIni* operator=(const char *filename);

            bool isPresent(void);
            bool getKeyValue(const std::string &key, std::string &value);

        private:
            std::string m_file;

    };
}

#endif