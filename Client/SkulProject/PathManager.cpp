#include "global_include.h"
#include "PathManager.h"

wchar_t PathManager::_contentPath[255] = { L'\0' };

void PathManager::Initialize()
{
	// .exe ���Ϸ� ������ ��� .exe ������ �ִ� ��ΰ� ���´�.
	// visual studio �� F5(����� ���) Ȥ�� ctrl + F5(����� ���� �ʰ� ����)�� ������ ��� ������Ʈ ��ΰ� ����
	//	- �� ������ ������Ʈ ���� -> ����� -> �۾� ���丮�� �׷��� �����Ǿ� �ֱ� ������
	//	- ����� <$(SolutionDir)Output\\bin\\> �̰ŷ� �ٲ� ����
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
