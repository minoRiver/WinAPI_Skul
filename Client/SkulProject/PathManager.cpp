#include "global_include.h"
#include "PathManager.h"

wchar_t PathManager::_contentPath[255] = { L'\0' };

void PathManager::Initialize()
{
	// .exe 파일로 실행할 경우 .exe 파일이 있는 경로가 나온다.
	// visual studio 로 F5(디버깅 모드) 혹은 ctrl + F5(디버그 하지 않고 시작)로 시작할 경우 프로젝트 경로가 나옴
	//	- 그 이유는 프로젝트 세팅 -> 디버깅 -> 작업 디렉토리가 그렇게 설정되어 있기 때문에
	//	- 현재는 <$(SolutionDir)Output\\bin\\> 이거로 바꿔 줬음
	GetCurrentDirectory(255, _contentPath);

	size_t length = wcslen(_contentPath);
	for (int i = (int)length - 1; i >= 0; --i)
	{
		if ('\\' == _contentPath[i])
		{
			_contentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(_contentPath, 255, L"\\bin\\content\\");
}
