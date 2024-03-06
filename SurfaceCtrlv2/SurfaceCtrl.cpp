#include "SurfaceCtrl.h"
#include "SurfaceCtrlLogic.h"

#include <plugin/jpg/jpg.h>
#include <PdfDraw/PdfDraw.h>
#define IMAGECLASS SurfaceCtrlImg
#define IMAGEFILE <SurfaceCtrl/SurfaceCtrl.iml>
#include <Draw/iml.h>

namespace 
{
	static const Upp::Ctrl::PlacementConstants BUTTON_ROTATION      = Upp::Ctrl::MIDDLE;
	static const Upp::Ctrl::PlacementConstants BUTTON_DRAG          = Upp::Ctrl::LEFT;
	static const Upp::Ctrl::PlacementConstants BUTTON_MENU          = Upp::Ctrl::RIGHT;
	static const Upp::CtrlCoreFlags  		   TRANSLATION_MODIFIER = Upp::CtrlCoreFlags::K_SHIFT;
	
	class CameraFlags
	{
		public:
			bool RotationEnable	     = false;
			bool DragEnable          = false;
			bool MenuEnable          = false;
			bool TranslationModifier = false;
	};
}


namespace Upp
{
	
	class Upp::SurfaceCtrl::SurfaceCtrlImpl
	{
		public:
			// Resolution
			float sizeW = 800.0f;
			float sizeH = 600.0f;
			
			SurfaceCtrlLogic logic;
			CameraFlags	     flags;
			
				
			
			void* user_ctx = nullptr;
	};
	
	
	SurfaceCtrl::SurfaceCtrl(void* user_ctx)
	{
		pImpl = std::make_shared<SurfaceCtrlImpl>();
		pImpl->user_ctx = user_ctx;
	}
	SurfaceCtrl::~SurfaceCtrl(){}
			
	void SurfaceCtrl::Draw() noexcept 
	{
		// TODO
	}
	
	void SurfaceCtrl::Layout()
	{
		GLResize(GetSize().cx,GetSize().cy);
	}
	
	void SurfaceCtrl::GLPaint()
	{
		// TODO
	}
	
	void SurfaceCtrl::GLResize(int w, int h)
	{
		if(w != 0) pImpl->sizeW = float(w);
		if(h != 0) pImpl->sizeH = float(h);
		glViewport(0, 0, int(pImpl->sizeW), int(pImpl->sizeH));
		
		// Camera viewport / screen size should be adjusted here
		
		Refresh();
	}
	
	bool SurfaceCtrl::Key(dword key,int count)
	{
		auto& logic = pImpl->logic;
		if(key == K_DELETE)
		{
			logic.DeleteSelected();
		} 
		else if(key == K_ESCAPE)
		{ 
			logic.ClearSelected();
		} 
		else if(key & K_CTRL && key & K_A)
		{
			logic.ClearSelected();
			logic.SelectAll();
		} 
		else if (key == K_CTRL_F)
		{
			// Zoom to Fit
			//ZoomToFit();
		}
			
		else if (key == K_CTRL_ADD || key == (K_CTRL|K_PLUS))
		{
			// ProcessZoom(Point(0,0),120);
			// Zoom Camera
		}
			
		else if (key == K_CTRL_SUBTRACT || key == (K_CTRL|K_MINUS))
		{
			//ProcessZoom(Point(0,0),-120);
			// Dezoom Camera
		}
			
		else if (key == K_CTRL_C)
		{
			ExecuteGL(THISFN(SaveToClipboard), true);
		}
			
		else if (key == K_CTRL_S)
		{
			ExecuteGL(THISFN(SaveToFile), true);	
		}
		else
		{
			return false;
		}
			
		Refresh();
		return true;
	}
	
	Image SurfaceCtrl::HandleEvent(int event, Point p, int zdelta, dword key)
	{
		auto& logic = pImpl->logic;
		auto& flags = pImpl->flags;
		
		if ((event & Ctrl::ACTION) == Ctrl::MOUSEWHEEL)
		{
			logic.Camera()->Zoom(p, zdelta);
		} 
		else if ((event & Ctrl::ACTION) == Ctrl::MOUSELEAVE)
		{
			flags.RotationEnable = false;
			flags.DragEnable = false;
		} 
		else if ((event & Ctrl::BUTTON) == BUTTON_ROTATION && (event & Ctrl::ACTION) == Ctrl::DOWN)
		{
			flags.RotationEnable = true;
			logic.StartRotation(p);
		}else if ((event & Ctrl::BUTTON) == BUTTON_DRAG && (event & Ctrl::ACTION) == Ctrl::DOWN && !flags.TranslationModifier)
		{
			SetFocus();
			flags.DragEnable = true;
			logic.Drag(p);
		}
		else if ((event & Ctrl::BUTTON) == BUTTON_ROTATION && (event & Ctrl::ACTION) == Ctrl::UP)
		{
			flags.RotationEnable = false;
			flags.TranslationModifier = false;
		}
		else if ((event & Ctrl::BUTTON) == BUTTON_DRAG && (event & Ctrl::ACTION) == Ctrl::UP)
		{
			flags.DragEnable = false;
		}
		else if((event & Ctrl::ACTION) == Ctrl::MOUSEMOVE) 
		{
			flags.TranslationModifier = key & TRANSLATION_MODIFIER;			
			if (flags.RotationEnable && flags.TranslationModifier)
			{
				logic.StartTranslation(p);
			}
			else if (flags.RotationEnable && !flags.TranslationModifier)
			{
				logic.StartRotation(p);
			}
			else if (flags.DragEnable)
			{
				logic.Move(p);	
			}
		}		
		Refresh();
		
		Image returnImage = SurfaceCtrlImg::PreciseCursor();
		if(event == CURSORIMAGE && GetMouseMiddle() && flags.RotationEnable && flags.TranslationModifier) returnImage = SurfaceCtrlImg::TranslationArrow();
		else if(event == CURSORIMAGE && GetMouseMiddle() && flags.RotationEnable) returnImage = SurfaceCtrlImg::RotationArrow();
		else if(event == CURSORIMAGE && GetMouseLeft() && flags.DragEnable) returnImage = SurfaceCtrlImg::HandGrab();
		return returnImage;
	}
}


