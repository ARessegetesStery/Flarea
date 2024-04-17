#include "flrpch.h"

#include "Application.h"

#include "Event/Event.h"
#include "Platform/Window.h"

#include "Loader/ObjParser/ObjParser.h"

#include "Input.h"

#include <GLAD/glad.h>

namespace FLR {

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FLR_CORE_ASSERT(!s_Instance, "Application already exists!")
		s_Instance = this;
		lastFrameTime = 0;
		frameDeltaTime = 0;

		m_Running = true;
		m_Window = std::unique_ptr<Window>(Window::createWindow());

		m_Window->setCallbackFunc(BIND_EVENT_FUNC(onEvent));
	}

	Application::~Application()
	{
	}

	void Application::onEvent(Event& e)
	{
		// SP_CORE_LOG_INFO(e.ToString())

		EventDispatcher Dispatcher(e);
		Dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FUNC(onWindowClose));
		Dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(onKeyPressed));
		Dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(onKeyReleased));
	}

	bool Application::onWindowClose(WindowClosedEvent& e)
	{
		FLR_CORE_INFO("Window Closed");
		m_Running = false;
		return true;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		return true;
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		return false;
	}

	void Application::attachLayer(Layer* lyr)
	{
		m_LayerStack.attachLayer(lyr);
	}

	void Application::attachOverlay(Layer* lyr)
	{
		m_LayerStack.attachOverlay(lyr);
	}

	void Application::detachLayer(Layer* lyr)
	{
		m_LayerStack.detachLayer(lyr);
	}

	void Application::detachOverlay(Layer* lyr)
	{
		m_LayerStack.detachOverlay(lyr);
	}

	void Application::tick()
	{
		Entity entity;
		ObjParser parser(&entity, "Cube");

		while (m_Running)
		{
			glClearColor(0.4f, 0.2f, 0.6f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			this->updateApp();

			for (auto lyr : m_LayerStack)
			{
				lyr->onEvent();
			}

			m_Window->onUpdate();
		}
	}

	void Application::updateApp()
	{
		float curFrameTime = static_cast<float>(glfwGetTime());
		this->frameDeltaTime = curFrameTime - this->lastFrameTime;
		this->lastFrameTime = curFrameTime;
		//FLR_CORE_INFO("{0} seonds passed since last frame", frameDeltaTime);
	}
}