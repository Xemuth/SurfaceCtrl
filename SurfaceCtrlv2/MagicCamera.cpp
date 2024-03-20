#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <plugin/glm/glm.hpp>
#include <plugin/glm/gtc/matrix_transform.hpp>
#include <plugin/glm/gtc/type_ptr.hpp>
#include <plugin/glm/gtx/quaternion.hpp>
#include <plugin/glm/ext/quaternion_trigonometric.hpp>
#include <plugin/glm/gtc/constants.hpp>
#include <plugin/glm/gtx/norm.hpp>
#include <plugin/glm/gtx/compatibility.hpp>
#include <plugin/glm/gtx/string_cast.hpp>
#include <plugin/glm/gtx/vector_angle.hpp>
			
namespace
{
	class MagicCamera: public Upp::Camera
	{
		public:
			~MagicCamera();
		     MagicCamera& glm::mat4 GetProjectionMatrix();
			 MagicCamera& glm::mat4 GetViewMatrix();
			
			 MagicCamera& ViewFrom(const glm::vec3& view_from);
			 MagicCamera& LookAt(const glm::vec3& look_at);
			 MagicCamera& FocusAt(Upp::Array<glm::vec3> focus_at);
		
			 MagicCamera& ProcessMouseWheelTranslation(float xoffset,float yoffset); //Move the camera depending on X and Y offset
			 MagicCamera& MouseWheelMouvement(float xoffset,float yoffset); //Rotate arround axis
			 MagicCamera& ProcessMouseScroll(float zdelta, float multiplier = 1.0f); //Zoom or move via MouseWheel depending on OnObject Boolean
			 MagicCamera& ProcessKeyboardMouvement(CameraMovementDirection direction); //Handler for keyboard, Useless in this kind of camera
			 bool ProcessKeyBoard(unsigned long Key,int count); //Handler for keyboard, Useless in this kind of camera
			 
			 MagicCamera& SetCameraRenderMode(CameraType type);
			 
		private:
			
	};
}



namespace Upp
{
	CameraPtr make_magic_camera()
	{
		return std::make_unique<MagicCamera>();
	}

	
	
	
}