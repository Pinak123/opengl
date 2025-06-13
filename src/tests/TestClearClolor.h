#pragma once

#include "Test.h"

namespace test {
	class TestClearColor : public Test
	{
		public:
			TestClearColor();

			~TestClearColor();
			void OnUpdate(float deltaTime) override;
			void OnRender() override;
			void OnImGuiRender() override;
			private:
				float m_ClearColor[4] = { 0.2f, 0.3f, 0.8f, 1.0f };
				float m_Time = 0.0f;
				float m_Increment = 0.05f;
	};
}