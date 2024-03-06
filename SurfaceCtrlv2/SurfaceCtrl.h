#ifndef _SurfaceCtrl_SurfaceCtrlv2_SurfaceCtrl_h_
#define _SurfaceCtrl_SurfaceCtrlv2_SurfaceCtrl_h_
#include <memory>

#include <GLCtrl/GLCtrl.h>

namespace Upp{

class SurfaceCtrl: public GLCtrl
{
	public:
		SurfaceCtrl(void* user_ctx);
		~SurfaceCtrl();
		
		Function <void(SurfaceCtrl& this, void* user_ctx)> WhenBegin;
		Function <void(SurfaceCtrl& this, void* user_ctx)> WhenPaint;
		Function <void(SurfaceCtrl& this, void* user_ctx)> WhenEnd;
	
		void Draw() noexcept;

		virtual void Layout();
		virtual void GLPaint();
		virtual void GLResize(int w, int h); 
		
		virtual bool Key(dword key,int count);
		virtual Image HandleEvent(int event, Point p, int zdelta, dword key);

	private:
		class SurfaceCtrlImpl;
		std::shared_ptr<SurfaceCtrlImpl> pImpl;
};

SurfaceCtrl make_default_surface_ctrl();

}

#endif
