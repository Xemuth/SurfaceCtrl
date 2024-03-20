#include "Camera.h"

#include "Transform.h"
			
namespace
{
	class MagicCamera: public Upp::Camera
	{
		public:
			MagicCamera() = default;
			~MagicCamera() = default;
			
			MagicCamera(const MagicCamera&) = delete;
			MagicCamera(MagicCamera&&) = delete;
			
			MagicCamera& operator=(const MagicCamera&) = delete;
			MagicCamera& operator=(MagicCamera&&) = delete;
			
			glm::mat4 GetProjectionMatrix();
			glm::mat4 GetViewMatrix();
			
			MagicCamera& ViewFrom(const glm::vec3& view_from);
			MagicCamera& LookAt(const glm::vec3& look_at);
			MagicCamera& FocusAt(const Upp::Array<glm::vec3>& focus_at);
			
			MagicCamera& ProcessMouseWheelTranslation(float xoffset,float yoffset); //Move the camera depending on X and Y offset
			MagicCamera& MouseWheelMouvement(float xoffset,float yoffset); //Rotate arround axis
			MagicCamera& ProcessMouseScroll(float zdelta, float multiplier = 1.0f); //Zoom or move via MouseWheel depending on OnObject Boolean
			MagicCamera& ProcessKeyboardMouvement(Upp::CameraMovementDirection direction); //Handler for keyboard, Useless in this kind of camera
			bool ProcessKeyBoard(unsigned long Key, int count); //Handler for keyboard, Useless in this kind of camera
			
			MagicCamera& SetCameraRenderMode(Upp::CameraType type);
			 
		private:
			Upp::CameraType type = Upp::CameraType::PERSPECTIVE;
			Upp::Transform transform;
	};
	
	glm::mat4 MagicCamera::GetProjectionMatrix()
	{
	}
	
	glm::mat4 MagicCamera::GetViewMatrix()
	{
	}
	
	MagicCamera& MagicCamera::ViewFrom(const glm::vec3& view_from)
	{
	}
	
	MagicCamera& MagicCamera::LookAt(const glm::vec3& look_at)
	{
	}
	
	MagicCamera& MagicCamera::FocusAt(const Upp::Array<glm::vec3>& focus_at)
	{
	}
	
	MagicCamera& MagicCamera::ProcessMouseWheelTranslation(float xoffset,float yoffset)
	{
	}
	
	MagicCamera& MagicCamera::MouseWheelMouvement(float xoffset,float yoffset)
	{
	}
	
	MagicCamera& MagicCamera::ProcessMouseScroll(float zdelta, float multiplier)
	{
	}
	
	MagicCamera& MagicCamera::ProcessKeyboardMouvement(Upp::CameraMovementDirection direction)
	{
	}
	
	bool MagicCamera::ProcessKeyBoard(unsigned long Key,int count)
	{
	}
	
	MagicCamera& MagicCamera::SetCameraRenderMode(Upp::CameraType type)
	{
	}
}

namespace Upp
{
	CameraPtr make_magic_camera()
	{
		return std::make_unique<MagicCamera>();
	}	
}