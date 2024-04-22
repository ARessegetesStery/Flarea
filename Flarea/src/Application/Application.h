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

		void OnEvent(Event& e);
		bool OnWindowClose(WindowClosedEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		void AttachLayer(Layer* lyr);
		void AttachOverlay(Layer* lyr);
		void DetachLayer(Layer* lyr);
		void DetachOverlay(Layer* lyr);

		void MainLoop();

		void UpdateApp();

	private:
		bool running;
		float last_frame_time;
		float frame_delta_time;
		std::unique_ptr<Window> window;

		static Application* instance;

		Camera camera;

		LayerStack layer_stack;
	};

	inline Application* createApp() { return new Application; }

}