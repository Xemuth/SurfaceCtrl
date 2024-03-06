#ifndef _SurfaceCtrl_SurfaceCtrlv2_SurfaceCtrlLogic_h_
#define _SurfaceCtrl_SurfaceCtrlv2_SurfaceCtrlLogic_h_
#include <memory>
#include <Core/Core.h>

#include "Object3D.h"
#include "Camera.h"



/* 
	SurfaceCtrLogic will hold all 3D Items + camera logic + Shaders and renderer
*/

class SurfaceCtrlLogic
{
	public:
		
		SurfaceCtrlLogic(CameraPtr camera);
		~SurfaceCtrlLogic();
		
		void Draw() noexcept;
	
		Upp::Vector<Object3D>& Objects() noexcept;
		
		Camera& Camera() noexcept;
		
		
		virtual bool Key(dword key,int count);
		virtual Image HandleEvent(int event, Point p, int zdelta, dword);
	
	private:
		class SurfaceCtrlLogicImpl;
		std::shared_ptr<SurfaceCtrlLogicImpl> pImpl;
};


#endif
