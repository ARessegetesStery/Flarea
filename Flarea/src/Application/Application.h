#pragma once

#include "flrpch.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Application/Layer.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Geometry/Geometry.h"

#include "Camera.h"

namespace FLR {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void onEvent(Event& e);
		bool onWindowClose(WindowClosedEvent& e);

		bool onKeyPressed(KeyPressedEvent& e);
		bool onKeyReleased(KeyReleasedEvent& e);

		void attachLayer(Layer* lyr);
		void attachOverlay(Layer* lyr);
		void detachLayer(Layer* lyr);
		void detachOverlay(Layer* lyr);

		void tick();

		void updateApp();

	private:
		bool m_Running;
		float lastFrameTime;
		float frameDeltaTime;
		std::unique_ptr<Window> m_Window;

		static Application* s_Instance;

		Camera camera;

		LayerStack m_LayerStack;
	};

	inline Application* createApp() { return new Application; }

}