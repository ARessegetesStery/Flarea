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
#include "Shader.h"

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
		bool OnMouseMoved(MouseMovedEvent& e);

		void AttachLayer(Layer* lyr);
		void AttachOverlay(Layer* lyr);
		void DetachLayer(Layer* lyr);
		void DetachOverlay(Layer* lyr);

		void LoadEntities();

		void LoadAssets();
		void MainLoop();

		void UpdateApp();
		void Render();

		inline void AddEntity(Entity* ent) { entities.push_back(ent); }

	private:
		bool running;
		float last_frame_time;
		float frame_delta_time;
		std::unique_ptr<Window> window;

		std::deque<Entity> entity_pool;
		std::vector<float> raw_vertices;

		static Application* instance;
		Shader shader;

		string vs, fs;

		size_t trig_count = 0;
		unsigned int buffer_object = 0;

		Camera camera;
		std::vector<Entity*> entities;

		LayerStack layer_stack;
	};

	inline Application* createApp() { return new Application; }

}