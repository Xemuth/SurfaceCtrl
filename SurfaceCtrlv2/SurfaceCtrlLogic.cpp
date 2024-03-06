#include "SurfaceCtrlLogic.h"

#include "Object3D.h"
#include "Camera.h"

namespace Upp{
	
	class SurfaceCtrlLogic::SurfaceCtrlLogicImpl{
		public:
						
	
	};
			
	SurfaceCtrlLogic::SurfaceCtrlLogic(CameraPtr camera)
	{
		pImpl = std::make_shared<SurfaceCtrlLogic::SurfaceCtrlLogicImpl>();
	}
		
	SurfaceCtrlLogic::~SurfaceCtrlLogic();


	void SurfaceCtrlLogic::Draw() noexcept;

	Upp::Vector<Object3D>& SurfaceCtrlLogic::Objects() noexcept;
	
	Camera& SurfaceCtrlLogic::Camera() noexcept;
	
	
	virtual bool SurfaceCtrlLogic::Key(dword key,int count);
	virtual Image SurfaceCtrlLogic::HandleEvent(int event, Point p, int zdelta, dword)
	{
		
	}

}