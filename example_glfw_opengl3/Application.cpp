#include "application.h"


// Initialize the static pointer to the application
std::shared_ptr<Application> Application::_staticInstance = nullptr;

Application::Application() 
{
}

Application::~Application()
{
}

void Application::ClearAll()
{
	
}

void Application::Draw()
{
	
	glViewport(0, 0, _windowWidth, _windowHeight);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	

}

void Application::DrawUI()
{

	static float f = 0.0f;
	static int counter = 0;

	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
	

	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		counter++;
	ImGui::SameLine();
	ImGui::Text("counter = %d", counter);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	ImGui::Render();

}


void Application::Init()
{
}




void Application::Update()
{
	
}





int Application::Run(int argc, char ** argv)
{
	// Initialize glfw (exit if any error occur)
	if (!glfwInit())
	{
		return -1;
	}

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Get the static pointer to the instance of the application
	std::shared_ptr<Application> app = Application::GetInstance();

	// Create a windowed mode window and its OpenGL context (exit if any error occur)
	app->_window = glfwCreateWindow((int)app->_windowWidth, (int)app->_windowHeight, "Neural Material IMGUI DEMO", NULL, NULL);
	if (!app->_window)
	{
		glfwTerminate();
		return -1;
	}

	// Set the error callback
	glfwSetErrorCallback(ErrorCallback);

	// Make the window's context current
	glfwMakeContextCurrent(app->_window);
	glfwSwapInterval(1); // Enable vsync
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set the window's callback functions
	glfwSetInputMode(app->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Setup Dear ImGui binding
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;


	// Init ImGui for glfw and OpenGL 3
	// NOTE: Indicate not to install the callbacks; otherwise, the already defined glfw callbacks will be useless
	ImGui_ImplGlfw_InitForOpenGL(app->_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup style
	ImGui::StyleColorsDark();

	// Init the application objects
	app->Init();

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(app->_window))
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Update
		app->Update();

		// Draw the application content
		

		// Draw the user interface
		app->DrawUI();

		app->Draw();

		glfwMakeContextCurrent(app->_window);
		// Swap front and back buffers
		glfwSwapBuffers(app->_window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Close the program
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(app->_window);
	glfwTerminate();
	return 0;
}



std::shared_ptr<Application> Application::GetInstance()
{
	// Instantiate the application if it hasn't
	if (_staticInstance == nullptr)
	{
		_staticInstance = std::shared_ptr<Application>(new Application());
	}

	// Return the static pointer to the instance of the application
	return _staticInstance;
}

void Application::ErrorCallback(int error, const char * description)
{
	std::cout << "Error: (" << error << ", " << description << ")" << std::endl;
}