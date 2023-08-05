#ifndef RSTRING_H
#define RSTRING_H

#include <data_types.h>

namespace rstring
{
	#define STR_END '\0'

	u32 rstrlen(const char *str1);
	u32 rstrnlen(const char *str, u32 max_len);
	s8 rstrncmp(const char *str1, const char *str2, u32 size);
	s8 rstrcmp(const char *str1, const char *str2);
	char * rstrchr(const char *str);
	char * rstrrchr(const char *str, const char &ch);
	char * rstrcpy(char *str1, const char *str2);
	char * rstrncpy(char *str1, const char *str2, u32 size);
	s8 rstrcasecmp(const char *str1, const char *str2);

	class RSTRING
	{
		public:
			RSTRING()
			{
				Pstring = 0;
				string_len = 0;
			}
			RSTRING(u32 size);
			RSTRING(const char *str);
			RSTRING(const RSTRING &str, bool deep = 1);

			/*-------string operations----------------------------------*/
			u32 rstrlen() { return string_len; }
			u32 rstrnlen(u32 max_len);

			s8 rstrcmp(const char *str);
			s8 rstrcmp(const RSTRING &str);

			s8 rstrncmp(const char *str, u32 size);
			s8 rstrncmp(const RSTRING &str, u32 size);

			RSTRING * rstrcpy(const char *str);
			RSTRING * rstrcpy(const RSTRING &str);

			RSTRING * rstrncpy(const char *str, u32 size);
			RSTRING * rstrncpy(const RSTRING &str, u32 size);

			s8 rstrcasecmp(const char *str);
			s8 rstrcasecmp(const RSTRING &str);

			/*-------operators-----------------------------------------*/
			char operator[](u32 index);

			RSTRING * operator=(const char *str);
			RSTRING * operator=(const RSTRING &str);

			bool operator==(const char *str);
			bool operator==(const RSTRING &str);

			bool operator!=(const char *str);
			bool operator!=(const RSTRING &str);

			bool operator>=(const char *str);
			bool operator>=(const RSTRING &str);

			bool operator<=(const char *str);
			bool operator<=(const RSTRING &str);

			bool operator>(const char *str);
			bool operator>(const RSTRING &str);

			bool operator<(const char *str);
			bool operator<(const RSTRING &str);

		private:
			char *Pstring;
			u32 string_len;
	};
}

#endif
