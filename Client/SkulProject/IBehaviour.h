#pragma once

#include <Windows.h>

class IBehaviour
{
public:
	virtual ~IBehaviour() { };

public:
	virtual void		Initialize() { }
	virtual void		FixedUpdate() { }
	virtual void		Update() { }
	virtual void		LateUpdate() { }
	virtual void		Render(HDC hdc) { }
	virtual void		Release() { }
};