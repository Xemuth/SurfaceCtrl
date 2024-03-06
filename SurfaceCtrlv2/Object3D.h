#ifndef _SurfaceCtrl_SurfaceCtrlv2_Object3D_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Object3D_h_

#include <memory>

namespace Upp
{

	class Object3D: public Upp::Moveable<Object3D> {
		public:		
			Object3D();
			Object3D(Object3D&& obj);
			Object3D& operator=(Object3D&& obj);
			Object3D(const Object3D& obj);
			Object3D& operator=(const Object3D& obj);
			~Object3D();
			
			
			size_t GetID();
		
		private:
			class Object3DImpl;
			std::shared_ptr<Object3DImpl> pImpl;
	};
	
	
}




#endif
