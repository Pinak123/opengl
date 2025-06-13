#pragma once
#include <functional>
#include <string>
#include <vector>
namespace test
{
	class Test
	{
	public:
		Test() {};
		virtual ~Test() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};

	};
	class TestMenu : public Test
	{
		public:
		TestMenu(Test *& currentTestPointer) ;
		virtual ~TestMenu();
		void OnUpdate(float deltaTime) override {};
		void OnImGuiRender() override;
		void OnRender() override {};
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
	};

} // namespace test