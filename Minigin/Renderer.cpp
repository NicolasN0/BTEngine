#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include "imgui_trashTheCache.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window,SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	//TrashTheCache::ShowTrashTheCacheWindow();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}

}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

//todo place all 3 in other file
//long long GetAverage(std::vector<long long> v)
//{
//	long long amount{};
//
//	for (int i{}; i < v.size(); i++)
//	{
//		amount += v.at(i);
//	}
//	return amount / v.size();
//}
//
//struct Transform
//{
//	float matrix[16] = {
//		1,0,0,0,
//		0,1,0,0,
//		0,0,1,0,
//		0,0,0,1 };
//};
//
//class GameObject3D
//{
//public:
//	Transform transform;
//	int ID;
//};
//
//
//class GameObject3DAlt
//{
//public:
//	Transform* transform;
//	int ID;
//};
//
//std::vector<long long> dae::Renderer::CalculateTrashTheCacheInt(int numberSamples)
//{
//	int stepsize{ 1 };
//	int size{ 67108864 };
//	int* intBuffer = new int[size] {};
//
//	std::vector<long long> averages;
//	std::vector<long long> timings;
//
//	while (stepsize != 1024)
//	{
//		for (int j{}; j < 3; j++) {
//			auto start = std::chrono::high_resolution_clock::now();
//
//			for (int i{}; i < size; i += stepsize)
//			{
//				intBuffer[i] *= 2;
//
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//			averages.push_back(elapsedTime);
//		}
//		timings.push_back(GetAverage(averages));
//		averages.clear();
//		stepsize *= 2;
//	}
//	return timings;
//
//}
//
//std::vector<long long> dae::Renderer::CalculateTrashTheCacheObject(int numberSamples)
//{
//	int stepsize{ 1 };
//	int size{ 67108864 };
//
//	std::vector<GameObject3D> objectBuffer(64 * 1024 * 1024);
//	std::vector<long long> averages;
//	std::vector<long long> timings;
//
//	while (stepsize != 1024)
//	{
//		for (int j{}; j < 3; j++) {
//			auto start = std::chrono::high_resolution_clock::now();
//
//		
//			for (int i{}; i < objectBuffer.size(); i += stepsize)
//			{
//				objectBuffer[i].ID *= 2;
//
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//			averages.push_back(elapsedTime);
//		}
//		timings.push_back(GetAverage(averages));
//		averages.clear();
//		stepsize *= 2;
//	}
//	return timings;
//}
//
//std::vector<long long> dae::Renderer::CalculateTrashTheCacheObjectPointer(int numberSamples)
//{
//	int stepsize{ 1 };
//	int size{ 67108864 };
//
//	std::vector<GameObject3DAlt> objectBuffer(64 * 1024 * 1024);
//	std::vector<long long> averages;
//	std::vector<long long> timings;
//
//	while (stepsize != 1024)
//	{
//		for (int j{}; j < 3; j++) {
//			auto start = std::chrono::high_resolution_clock::now();
//
//
//			for (int i{}; i < objectBuffer.size(); i += stepsize)
//			{
//				objectBuffer[i].ID *= 2;
//
//			}
//			auto end = std::chrono::high_resolution_clock::now();
//			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
//			averages.push_back(elapsedTime);
//		}
//		timings.push_back(GetAverage(averages));
//		averages.clear();
//		stepsize *= 2;
//	}
//	return timings;
//}

