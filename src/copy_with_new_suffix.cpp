#include <sdw.h>

int UMain(int argc, UChar* argv[])
{
	if (argc != 4)
	{
		return 1;
	}
	UString sFileNameSrc = argv[1];
	UString sSuffixOld = argv[2];
	if (!EndWith(sFileNameSrc, sSuffixOld))
	{
		return 1;
	}
	UString sSuffixNew = argv[3];
	UString sFileNameDest = sFileNameSrc;
	sFileNameDest.replace(sFileNameSrc.size() - sSuffixOld.size(), sSuffixOld.size(), sSuffixNew);
	FILE* fpSrc = UFopen(sFileNameSrc.c_str(), USTR("rb"), false);
	if (fpSrc == nullptr)
	{
		return 1;
	}
	Fseek(fpSrc, 0, SEEK_END);
	n64 nFileSize = Ftell(fpSrc);
	FILE* fpDest = UFopen(sFileNameDest.c_str(), USTR("wb"), false);
	if (fpDest == nullptr)
	{
		fclose(fpSrc);
		return 1;
	}
	CopyFile(fpDest, fpSrc, 0, nFileSize);
	fclose(fpDest);
	fclose(fpSrc);
	return 0;
}
