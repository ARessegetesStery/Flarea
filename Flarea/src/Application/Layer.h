#pragma once

namespace FLR {

	class Layer
	{
	public:
		Layer(std::string name);
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();

		virtual void OnUpdate();
		virtual void OnEvent();

		inline std::string GetDebugName() { return m_DebugName; };

	private:
		std::string m_DebugName;
	};

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void AttachLayer(Layer* lyr);
		void AttachOverlay(Layer* lyr);

		void DetachLayer(Layer* lyr);
		void DetachOverlay(Layer* lyr);

		std::vector<Layer*>::iterator begin();
		std::vector<Layer*>::iterator end();

	private:
		std::vector<Layer*> m_Stack;
		std::vector<Layer*>::iterator m_InsertSig;

		std::vector<Layer*> m_PopedStack;
	};

}