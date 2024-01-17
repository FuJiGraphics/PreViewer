#pragma once

enum class RendererAPI
{
	None,
	DirectX,
	Pylon,
	Max,
};

static RendererAPI renderAPI = RendererAPI::Pylon;