#include "pch.h"
#include "RealCamera.h"

#include <Platform/Pylon/Pylon_Camera.h>

namespace PreViewer {

	// ----------- Create View Camera -----------
	RealCamera* RealCamera::Create()
	{
		switch (s_CameraAPI)
		{
			case CameraAPI::Pylon:
				return new PylonCamera();
				break;
		}
		return nullptr;
	}

}