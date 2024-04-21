#include "minIni.h"

minIni* minIni::operator=(std::string filename)
{
    m_file = filename;
    return this;
}

minIni* minIni::operator=(const char *filename)
{
    m_file = filename;
    return this;
}

bool minIni::isPresent(void)
{
    bool result;
    std::fstream file(m_file, std::ios::in);
    if(file)
        result = 1;
    else
        result = 0;
    file.close();
    return result;
}

bool minIni::appS(std::string data)
{
    std::fstream file(m_file, std::ios::app);
    if(!file)
    {
        file.close();
        return 0;
    }
    file << data.c_str();
    file.close();
    return 1;
}