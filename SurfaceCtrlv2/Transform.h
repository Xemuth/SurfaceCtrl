#ifndef _SurfaceCtrl_SurfaceCtrlv2_Transform_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Transform_h_

namespace Upp
{

	class Transform
	{
		public:
			

		private:
			glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
			
			glm::vec3 WorldFront = glm::vec3(0.0, 0.0, -1.0);
			glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 WorldRight = glm::vec3(1.0f, 0.0f, 0.0f);
			
			glm::vec3 Position = glm::vec3(0.0f);
			glm::quat Rotation = Transform::GetQuaterion(0.0f,glm::vec3(0.0f,0.0f,0.0f));
			glm::vec3 Scale = glm::vec3(1.0f);
	};
	
}

#endif
