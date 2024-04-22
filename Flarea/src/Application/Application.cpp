#include "flrpch.h"

#include "Application.h"

#include "Event/Event.h"
#include "Platform/Window.h"

#include "Loader/ObjParser/ObjParser.h"

#include "Util/Input.h"

#include <GLAD/glad.h>

#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace FLR {

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
		Dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(OnMouseMoved));
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
		camera.ProcessEvent(&e);
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		camera.ProcessEvent(&e);
		return false;
	}

	bool Application::OnMouseMoved(MouseMovedEvent& e)
	{
		FLR_CORE_INFO(e.ToString());
		camera.ProcessEvent(&e);
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

	void Application::LoadEntities()
	{
		for (auto& ent : entities)
			this->trig_count = ent->GetMesh().LoadInto(raw_vertices);

		unsigned int VBO, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, raw_vertices.size() * sizeof(float), &raw_vertices.front(), GL_STATIC_DRAW);

		FLR_CORE_INFO(">>> {0}", raw_vertices.size());

		this->buffer_object = VAO;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		FLR_CORE_INFO("raw_vertices.size: {0}", raw_vertices.size());

		shader.Set("resources/shader/test.vs", "resources/shader/test.fs");

		// TODO Load Texture

		shader.use();
	}

	void Application::Render()
	{
		shader.use();

		glm::mat4 projection = glm::perspective(glm::radians(this->camera.fov), (float)this->window->getWidth() / (float)this->window->getHeight(), 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		glm::mat4 view = glm::lookAt(this->camera.camera_pos, this->camera.camera_pos + this->camera.camera_front, this->camera.camera_up);
		shader.setMat4("view", view);

		glBindVertexArray(this->buffer_object);

		for (auto ent : entities)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, ent->GetPosition());

			model = glm::rotate(model, ent->GetRotation(), glm::vec3(1.0f, 0.3f, 0.5f));
			shader.setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}

	void Application::MainLoop()
	{
		Entity entity;
		entity.SetPosition(glm::vec3(0.0f, 0.0f, -3.0f));
		entity.SetRotation(0.0f);
		this->AddEntity(&entity);
		ObjParser parser(&entity, "Cube");
		parser.Parse();
		entity.Log();

		this->LoadEntities();

		while (running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			this->UpdateApp();

			this->Render();

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