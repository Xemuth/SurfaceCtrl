#ifndef _SurfaceCtrl_SurfaceCtrlv2_Transform_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Transform_h_

#include <memory>

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

namespace Upp
{

	class Transform
	{
		public:
			Transform() = default;
			Transform(const Transform& t);
			Transform(Transform&& t);
			Transform& operator=(const Transform& t);			
			Transform& operator=(Transform&& t);
			~Transform() = default;
						
			Transform& SetPosition(float x, float y, float z);
			Transform& SetRotation(float Yaw, float Pitch, float Roll);
			Transform& SetRotation(float angleDegree, const glm::vec3& axis);
			
			static glm::quat GetQuaterion(float Yaw, float Pitch, float Roll);
			static glm::quat GetQuaterion(float angleDegree, const glm::vec3& axis);
			static glm::vec3 ConvertQuatToEuler(const glm::quat& quaterion);
			static glm::vec3 TransformVectorByMatrix(const glm::vec3& vector, const glm::mat4& matrix);
						
			glm::vec3 front      = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 up         = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 right      = glm::vec3(1.0f, 0.0f, 0.0f);
			
			glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, -1.0f);
			glm::vec3 worldUp    = glm::vec3(0.0f, 1.0f, 0.0f);
			glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);
			
			glm::vec3 position   = glm::vec3(0.0f, 0.0f, 0.0f);
			glm::quat rotation   = GetQuaterion(0.0f, glm::vec3(0.0f,0.0f,0.0f));
			glm::vec3 scale      = glm::vec3(1.0f, 1.0f, 1.0f);
		
		private:
			void RecalculateFURW();
	};
	
}

#endif
