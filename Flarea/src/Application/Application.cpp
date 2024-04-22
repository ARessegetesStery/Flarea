#include "flrpch.h"

#include "Application.h"

#include "Event/Event.h"
#include "Platform/Window.h"

#include "Loader/ObjParser/ObjParser.h"

#include "Util/Input.h"

#include <GLAD/glad.h>

namespace FLR {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		FLR_CORE_ASSERT(!instance, "Application already exists!")
		instance = this;
		last_frame_time = 0;
		frame_delta_time = 0;

		running = true;
		window = std::unique_ptr<Window>(Window::createWindow());

		window->setCallbackFunc(BIND_EVENT_FUNC(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		// SP_CORE_LOG_INFO(e.ToString())

		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNC(OnWindowClose));
		Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(OnKeyPressed));
		Dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(OnKeyReleased));
	}

	bool Application::OnWindowClose(WindowClosedEvent& e)
	{
		FLR_CORE_INFO("Window Closed");
		running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		camera.ProcessKeyEvent(&e);
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		camera.ProcessKeyEvent(&e);
		return false;
	}

	void Application::AttachLayer(Layer* lyr)
	{
		layer_stack.AttachLayer(lyr);
	}

	void Application::AttachOverlay(Layer* lyr)
	{
		layer_stack.AttachOverlay(lyr);
	}

	void Application::DetachLayer(Layer* lyr)
	{
		layer_stack.DetachLayer(lyr);
	}

	void Application::DetachOverlay(Layer* lyr)
	{
		layer_stack.DetachOverlay(lyr);
	}

	void Application::MainLoop()
	{
		Entity entity;
		entity.SetPosition(glm::vec3(0.0f, 0.0f, -3.0f);
		this->AddEntity(&entity);
		ObjParser parser(&entity, "Cube");
		parser.Parse();
		entity.Log();

		while (running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			this->UpdateApp();

			for (auto lyr : layer_stack)
			{
				lyr->OnEvent();
			}

			window->OnUpdate();
		}
	}

	void Application::UpdateApp()
	{
		float curFrameTime = static_cast<float>(glfwGetTime());
		this->frame_delta_time = curFrameTime - this->last_frame_time;
		this->last_frame_time = curFrameTime;
		//FLR_CORE_INFO("{0} seonds passed since last frame", frameDeltaTime);
	}
}