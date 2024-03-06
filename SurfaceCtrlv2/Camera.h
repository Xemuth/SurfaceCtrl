#ifndef _SurfaceCtrl_SurfaceCtrlv2_Camera_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Camera_h_
#include <memory>

namespace Upp
{
	class Camera
	{
		
	};
	
	
	using CameraPtr = std::unique_ptr<Camera>
	
	CameraPtr make_uogl_camera();
	CameraPtr make_magic_camera();
	

}

	

#endif
