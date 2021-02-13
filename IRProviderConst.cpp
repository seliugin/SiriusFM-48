#include "IRProviderConst.h"
#include <cstdio>


namespace SiriusFM
{
	IRProvider<IRModeE::Const>::IRProvider(char const* a_file)
	{
		m_IRs[ int(CcyE::N)] = {0};
		FILE* fp = fopen(a_file, "r");

		if (a_file == nullptr || *a_file =='\0')
			return;
		
		char buff[255];
		while (fgets(buff, 255, (FILE*)fp) != nullptr)
		{
			buff[3] = '\0';
			int code = int(str2CcyE(buff));
			double rate = std::atof(buff+4);
			m_IRs[code] = rate;
		}
		
		fclose(fp);
	}
}



