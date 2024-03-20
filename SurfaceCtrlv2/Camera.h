#ifndef _SurfaceCtrl_SurfaceCtrlv2_Camera_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Camera_h_
#include <memory>

namespace Upp
{
	enum class CameraType {PERSPECTIVE = 0, ORTHOGRAPHIC = 1};
	enum class CameraMovementDirection {FORWARD = 0, BACKWARD = 1, LEFT = 2, RIGHT = 3};
	
	class Camera
	{
		public:
			virtual ~Camera();
			
			virtual Camera& glm::mat4 GetProjectionMatrix() = 0;
			virtual Camera& glm::mat4 GetViewMatrix() = 0;
			
			virtual Camera& ViewFrom(const glm::vec3& view_from) = 0;
			virtual Camera& LookAt(const glm::vec3& look_at) = 0;
			virtual Camera& FocusAt(const Upp::Array<glm::vec3>& focus_at) = 0;
		
			virtual Camera& ProcessMouseWheelTranslation(float xoffset,float yoffset) = 0; //Move the camera depending on X and Y offset
			virtual Camera& MouseWheelMouvement(float xoffset,float yoffset) = 0; //Rotate arround axis
			virtual Camera& ProcessMouseScroll(float zdelta, float multiplier = 1.0f) = 0; //Zoom or move via MouseWheel depending on OnObject Boolean
			virtual Camera& ProcessKeyboardMouvement(CameraMovementDirection direction) = 0; //Handler for keyboard, Useless in this kind of camera
			virtual bool ProcessKeyBoard(unsigned long Key,int count) = 0; //Handler for keyboard, Useless in this kind of camera
	
			virtual Camera& SetCameraRenderMode(CameraType type) = 0;
	};
	
	
	using CameraPtr = std::unique_ptr<Camera>;
	
	CameraPtr make_uogl_camera();
	CameraPtr make_magic_camera();
}

	

#endif
