#ifndef _SurfaceCtrl_SurfaceCtrlv2_Skybox_h_
#define _SurfaceCtrl_SurfaceCtrlv2_Skybox_h_
#include <memory>


class Skybox {
	public:
		Skybox()
		~Skybox()
		
		Skybox& Show(bool b = true){show = b; return *this;}
		bool IsShown(){return show;}
		bool IsLoaded(){return ID;}
	
		Skybox& Init(const Image& skybox_right,const Image& skybox_left,const Image& skybox_top,const Image& skybox_bottom,const Image& skybox_front,const Image& skybox_back); //Load all image provided as skybox
		Skybox& Clear();
		Skybox& Draw(const glm::mat4& projectionMatrix,const glm::mat4& viewMatrix);
	private:
		
		std::shared
		
		unsigned int ID = 0;
		GLuint VBO, VAO;
		bool show = false;
		
		OpenGLProgram program;
		Skybox& Init(const Vector<Image>& images); //Load this vector of image as Skybox
};

#endif
