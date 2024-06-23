#include "aurorapch.h"
#include "ImGuiLayer.h"

namespace Aurora
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::onAttach()
    {
        Layer::onAttach();
    }

    void ImGuiLayer::onDetach()
    {
        Layer::onDetach();
    }

    void ImGuiLayer::onUpdate()
    {
        Layer::onUpdate();
    }

    void ImGuiLayer::onEvent(Event& event)
    {
        Layer::onEvent(event);
    }
}
