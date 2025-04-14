#include "minIni.h"

using namespace ConfigReader;

minIni* minIni::operator=(std::string &filename)
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
    std::ifstream file(m_file);
    if(file)
        result = 1;
    else
        result = 0;
    file.close();
    return result;
}

bool minIni::getKeyValue(const std::string key, std::string &value)
{
    bool result = 0;
    std::ifstream file(m_file);
    do
    {
        if(!file)
        {
            break;
        }

        std::string line;
        while(std::getline(file, line))
        {
            //remove spaces in the line
            std::size_t pos = 0;
            while( (pos = line.find_first_of(" ", pos)) != std::string::npos )
            {
                line.erase(pos);
            }

            //find the position of key in the line, find position of '=' in the line, return everyting after '='
            pos = line.find(key);
            if(pos != std::string::npos)
            {
                if(pos != 0 && line[key.length()] != '=')
                {
                    continue;
                }
                value = line.substr( key.length() + 1 );
                result = 1;
                break;
            }
        }
    }
    while(0);
    file.close();
    return result;
}