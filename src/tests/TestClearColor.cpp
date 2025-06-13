#include "TestClearClolor.h"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_opengl3_loader.h>
namespace test
{
	TestClearColor::TestClearColor()
		: m_ClearColor(0.2f, 0.3f, 0.3f, 1.0f) // Default clear color
	{
	}
	TestClearColor::~TestClearColor()
	{
	}
	void TestClearColor::OnUpdate(float deltaTime)
	{
		// Update logic if needed
	}
	void TestClearColor::OnRender()
	{
		// Clear the screen with the specified color
		glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		
	}
	void TestClearColor::OnImGuiRender()
	{
		// ImGui rendering logic if needed
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}	

}