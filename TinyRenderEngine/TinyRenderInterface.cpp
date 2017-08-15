
#include "stdafx.h"
#include "TinyRenderInterface.h"
#include "TinyRenderEngine.h"

VOID CreateEngineObj(CRenderInterface** pRender)
{
	*pRender = new CTinyRenderEngine;
}