#include "Transform.h"

namespace Upp
{
	Transform::Transform(const Transform& t)
	{
		*this = t;
	}
	
	Transform::Transform(Transform&& t)
	{
		*this = t;
	}
	
	Transform& Transform::operator=(const Transform& t)
	{
		front      = t.front;
		up         = t.up;
		right      = t.right;
		worldFront = t.worldFront;
		worldUp    = t.worldUp;
		worldRight = t.worldRight;
		position   = t.position;
		rotation   = t.rotation;
		scale      = t.scale;
		return *this;
	}
	
	Transform& Transform::operator=(Transform&& t)
	{
		*this = t;
		return *this;
	}
	
	Transform& Transform::SetPosition(float x, float y, float z)
	{
		position = glm::vec3(x, y, z);
		return *this;
	}
	
	Transform& Transform::SetRotation(float Yaw, float Pitch, float Roll)
	{
		rotation = glm::quat(glm::vec3(Pitch, Yaw , Roll)); 
		RecalculateFURW();
		return *this;
	}
	
	Transform& Transform::SetRotation(float angleDegree, const glm::vec3& axis)
	{
		rotation = Transform::GetQuaterion(angleDegree, axis);
		RecalculateFURW();
		return *this;
	}
	
	void Transform::RecalculateFURW()
	{
		front = glm::rotate(glm::inverse(rotation), worldFront);
	    right = glm::rotate(glm::inverse(rotation), worldRight);
	    up = glm::rotate(glm::inverse(rotation), worldUp);
	}
	
	glm::quat Transform::GetQuaterion(float Yaw, float Pitch, float Roll)
	{
		return glm::quat(glm::vec3(Pitch, Yaw , Roll));
	}
	
	glm::quat Transform::GetQuaterion(float angleDegree, const glm::vec3& axis)
	{
		float radHalfAngle = glm::radians(angleDegree) / 2.0f;
		float sinVal = glm::sin(radHalfAngle);
		float cosVal = glm::cos(radHalfAngle);
		float xVal = axis.x * sinVal;
		float yVal = axis.y * sinVal; 
		float zVal = axis.z * sinVal; 
		return glm::quat(cosVal, xVal, yVal, zVal); 
	}
	
	glm::vec3 Transform::ConvertQuatToEuler(const glm::quat& quaterion)
	{
		return glm::eulerAngles(quaterion);
	}
	
	glm::vec3 Transform::TransformVectorByMatrix(const glm::vec3& vector, const glm::mat4& matrix)
	{
		float w = vector[0]* matrix[0][3] + vector[1] * matrix[1][3] + vector[2] * matrix[2][3] + matrix[3][3];
		glm::vec3 ret;
		ret.x = (vector[0]*matrix[0][0]+vector[1]*matrix[1][0]+vector[2]*matrix[2][0]+matrix[3][0])/w;
		ret.y = (vector[0]*matrix[0][1]+vector[1]*matrix[1][1]+vector[2]*matrix[2][1]+matrix[3][1])/w;
		ret.z = (vector[0]*matrix[0][2]+vector[1]*matrix[1][2]+vector[2]*matrix[2][2]+matrix[3][2])/w;
		return ret;
	}
}