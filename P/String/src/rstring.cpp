#include <rstring.h>

using namespace rstring;

u32 rstrlen(const char *str)
{
	u32 len = 0;
	while(*str != STR_END)
	{
		len++;
		str++;
	}
	return len;
}

u32 rstrnlen(const char *str, u32 max_len)
{
	u32 len = 0;
	while(len < max_len)
	{
		if(*str == STR_END)
		{
			break;
		}
		len++;
		str++;
	}
	return len;
}

s8 rstrncmp(const char *str1, const char *str2, u32 size)
{
	u32 ix = 0;
	while( ix != size )
	{
		if( str1[ix] != str2[ix])
		{
			break;
		}
		if( str1[ix] == STR_END )
		{
			break;
		}
		ix++;
	}

	if( str1[ix] > str2[ix] )
	{
		return 1;
	}
	if( str1[ix] < str2[ix] )
	{
		return -1;
	}
	if( str1[ix] == str2[ix] )
	{
		return 0;
	}
}

s8 rstrcmp(const char *str1, const char *str2)
{
	while(*str1)
	{
		if( *str1 != *str2 )
		{
			break;
		}
		str1++;
		str2++;
	}

	if( *str1 > *str2 )
	{
		return 1;
	}
	if( *str1 < *str2)
	{
		return -1;
	}
	if( *str1 == *str2 )
	{
		return 0;
	}
}

char * rstrchr(const char *str, const char &ch)
{
	char *ptr = str;
	while(*ptr)
	{
		if( *ptr == ch )
		{
			return ptr;
		}
		ptr++;
	}

	return -1;
}

char * rstrrchr(const char *str, const char &ch)
{
	char *ptr = str;
	while(*ptr)
	{
		ptr++;
	}
	while(ptr != str)
	{
		if( *ptr == ch )
		{
			return ptr;
		}
		ptr--;
	}

	return -1;
}

char * rstrcpy(char *str1, const char *str2)
{
	char *ptr = str1;
	if( rstrlen(str1) >= rstrlen(str2) )
	{
		while(*str2)
		{
			*ptr = *str2;
			ptr++;
			str2++;
		}
		*str1 = STR_END;
		return str1;
	}
	else
	{
		return -1;
	}
}

char *rstrncpy(char *str1, const char *str2, u16 size)
{
	u32 idx = 0;
	if( rstrlen(str1) >= rstrlen(str2) )
	{
		while(idx != size)
		{
			if(str2[idx])
			{
				str1[idx] = str1[idx];
			}
			else
			{
				break;
			}
		}
		str1[idx] = STR_END;
		return str1;
	}
	else
	{
		return -1;
	}
}

s8 rstrcasecmp(const char *str1, const char *str2)
{
	char ch1, ch2;
	ch1 = *str1;
	ch2 = *str2;
	while(ch1)
	{
		if( (*ch1 >= 'A') && (*ch1 <= 'Z') )
		{
			ch1 += 32;
		}
		if( (*ch2 >= 'A') && (*ch2 <= 'Z') )
		{
			ch2 += 32;
		}
		if( ch1 != ch2 )
		{
			break;
		}
		str1++;
		str2++;
		ch1 = *str1;
		ch2 = *str2;
	}

	if( ch1 > ch2 )
	{
		return 1;
	}
	if( ch1 < ch2 )
	{
		return -1;
	}
	if( ch1 == ch2 )
	{
		return 0;
	}
}

RSTRING::RSTRING(u32 size)
{
	Pstring = new char[size];
	string_len = size;
}
RSTRING::RSTRING(const char *str)
{
	string_len = rstrlen(str);
	Pstring = new char[string_len];
}
RSTRING::RSTRING(const RSTRING str, bool deep)
{
	if(!deep)
	{
		Pstring = str.Pstring;
	}
	else
	{
		Pstring = new char[str.string_len];
	}
}

/*------class string operations-------------------------------*/
u32 RSTRING::rstrnlen(u32 max_len)
{
	return rstrnlen(Pstring, max_len);
}

s8 RSTRING::rstrcmp(const char *str)
{
	return rstrcmp(Pstring, str);
}

s8 RSTRING::rstrcmp(const RSTRING &str)
{
	return rstrcmp(Pstring, str.Pstring);
}

s8 RSTRING::rstrncmp(const char *str, u32 size)
{
	return rstrncmp(Pstring, str, size);
}

s8 RSTRING::rstrncmp(const RSTRING &str, u32 size)
{
	return rstrncmp(Pstring, str.Pstring, size);
}

RSTRING * RSTRING::rstrcpy(const char *str)
{
	if( rstrcpy(Pstring, str) != -1 )
	{
		return this;
	}
	else
	{
		return -1;
	}
}

RSTRING * RSTRING::rstrcpy(const RSTRING &str)
{
	if( rstrcpy(Pstring, str.Pstring) != -1 )
	{
		return this;
	}
	else
	{
		return -1;
	}
}

RSTRING * RSTRING::rstrncpy(const char *str, u32 size)
{
	if( rstrncpy(Pstring, str, size) != -1 )
	{
		return this;
	}
	else
	{
		return -1;
	}
}

RSTRING * RSTRING::rstrncpy(const RSTRING &str, u32 size)
{
	if( rstrncpy(Pstring, str.Pstring) != -1 )
	{
		return this;
	}
	else
	{
		return -1;
	}
}

s8 RSTRING::rstrcasecmp(const char *str)
{
	return rstrcasecmp(Pstring, str);
}

s8 RSTRING::rstrcasecmp(const RSTRING &str)
{
	return rstrcasecmp(Pstring, str.Pstring);
}

/*------class operators--------------------------------------------*/
char RSTRING::operator[](u32 index)
{
	return this->Pstring[index];
}

RSTRING * RSTRING::operator=(const char *str)
{
	if(Pstring != 0)
	{
		delete Pstring;
	}
	string_len = rstrlen(str);
	Pstring = new char[string_len];
	return this;
}

RSTRING * RSTRING::operator=(const RSTRING &str)
{
	if(Pstring != 0)
	{
		delete Pstring;
	}
	string_len = str.string_len;
	Pstring = new char[string_len];
	return this;
}

bool RSTRING::operator==(const char *str)
{
	if(rstrcmp(Pstring, str) != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool RSTRING::operator==(const RSTRING &str)
{
	if(rstrcmp(Pstring, str.Pstring) != 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

bool RSTRING::operator!=(const char *str)
{
	if(rstrcmp(Pstring, str) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator!=(const RSTRING &str)
{
	if(rstrcmp(Pstring, str.Pstring) != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator>=(const char *str)
{
	u8 result;
	result rstrcmp(Pstring, str);
	if( (result == 1) || (result == 0) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator>=(const RSTRING &str)
{
	u8 result;
	result rstrcmp(Pstring, str.Pstring);
	if( (result == 1) || (result == 0) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator<=(const char *str)
{
	u8 result;
	result rstrcmp(Pstring, str);
	if( (result == -1) || (result == 0) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator<=(const RSTRING &str)
{
	u8 result;
	result rstrcmp(Pstring, str.Pstring);
	if( (result == -1) || (result == 0) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator>(const char *str)
{
	if(rstrcmp(Pstring, str) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator>(const RSTRING &str)
{
	if(rstrcmp(Pstring, str.Pstring) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator<(const char *str)
{
	if(rstrcmp(Pstring, str) == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool RSTRING::operator<(const RSTRING &str)
{
	if(rstrcmp(Pstring, str.Pstring) == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

