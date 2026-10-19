#include "ShaderProgram.h"
#include "colors.h"
#include "MdlRenderer.h"

class Model;
class GLFWwindow;

class Renderer {
public:
	MdlRenderer* mdlRenderer = NULL;
	EntRenderOpts renderOpts;

	Renderer(std::string fpath, int width, int height, bool legacy_renderer, bool headless);

	bool load_model(std::string modl);

	void unload_model();

	void change_animation(int idx);

	void reset_view();

	void resize_view(int width, int height);

	void render_loop();

	void create_image(string outPath);

	// Renders frames [startFrame, endFrame] (0-255, like pev.frame) of a sequence side by side into one PNG,
	// at most maxFrames evenly spaced ones, and prints {"frames","fps","w","h"} as JSON. Returns a process exit code.
	int create_strip(string outPath, int sequence, float startFrame, float endFrame, int maxFrames);

	int fitSequence = -1; // sequence whose bounds place the camera (-1 = the one rendered)
	float fitMargin = 1.0f; // >1 zooms out from that fit

	void setup_render();

	void render();

private:
	string fpath;
	Model* m_model;
	bool legacy_renderer;
	bool headless;
	bool valid;
	uint8_t* mesa3d_buffer;

	GLFWwindow* window;
	ShaderProgram* mdlShader = NULL;
	ShaderProgram* mdlWireShader = NULL;
	ShaderProgram* colorShader = NULL;
	int windowWidth;
	int windowHeight;
	float fov = 75.0f;
	float zNear = 1.0f;
	float zFar = 262144.0f;

	mat4x4 model = mat4x4();
	mat4x4 view = mat4x4();
	mat4x4 projection = mat4x4();
	mat4x4 modelView = mat4x4();
	mat4x4 modelViewProjection = mat4x4();

	vec3 cameraOrigin = vec3();
	vec3 cameraRight = vec3(1, 0, 0);

	vec3 modelAngles = vec3(0, -90, 0);
	vec3 modelOrigin = vec3(0, 0, 0);

	bool create_window(int width, int height);
	bool create_headless_context(int width, int height);
	void init_gl();
	void compile_shaders();
	void get_model_fit_offsets(vec3 modelOrigin, vec3 modelAngles, float& depthOffset, float& heightOffset);
	void drawBoxOutline(vec3 center, vec3 mins, vec3 maxs, COLOR4 color);
};