#include "MiniginPCH.h"
#include "imgui_trashTheCache.h"
#include <chrono>

void TrashTheCache::ShowTrashTheCacheWindow()
{
	//ImGui::Text("Works");
	if (ImGui::CollapsingHeader("Exercise 2")) 
	{
		static ImGui::PlotConfig config;
		if (ImGui::Button("Trash the cache")) 
		{
			std::vector<float> v = CalculateTrashTheCacheInt(5,config);
		}
		ImGui::Plot("", config);
	}
	if (ImGui::CollapsingHeader("Exercise 3"))
	{
		static bool graph1;
		static bool graph2;
		static ImGui::PlotConfig config;
		static int sampleSize = 5;
		ImGui::InputInt("# samples", &sampleSize);
		if (ImGui::Button("Trash the cache with GameObject3D"))
		{
			std::vector<float> v = CalculateTrashTheCacheObject(sampleSize, config);
			graph1 = true;
		}
		ImGui::Plot("", config);
		static ImGui::PlotConfig config2;
		static int sampleSize2 = 5;
		ImGui::InputInt("# samples", &sampleSize2);
		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
		{
			std::vector<float> v = CalculateTrashTheCacheObjectPointer(sampleSize2, config2);
			graph2 = true;
		}
		ImGui::Plot("", config2);
		static ImGui::PlotConfig config3;
		if (graph1 == true && graph2 == true) 
		{
			static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0) };
			static const float* y_data[] = { config.values.ys,config2.values.ys };
			ImGui::Text("Combined:");
			config3.values.count = config2.values.count;
			config3.values.ys_list = y_data;
			config3.values.ys_count = 2;
			config3.values.colors = colors;
			config3.scale.min = 0;
			config3.scale.max = config.scale.max;
			config3.tooltip.show = false;
			config3.tooltip.format = "x=%.2f, y=%.2f";
			config3.grid_x.show = true;
			config3.grid_y.show = true;
			config3.frame_size = ImVec2(300, 150);
			config3.line_thickness = 2.f;
			ImGui::Plot("", config3);
		}
	}
}

float GetAverage(std::vector<float> v)
{
	float amount{};

	for (int i{}; i < v.size(); i++)
	{
		amount += v.at(i);
	}
	return amount / v.size();
}

struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	Transform transform;
	int ID;
};


class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

std::vector<float> TrashTheCache::CalculateTrashTheCacheInt(int numberSamples,ImGui::PlotConfig& conf)
{

	int stepsize{ 1 };
	int size{ 67108864 };
	int* intBuffer = new int[size] {};

	static std::vector<float> timings(10, 0);
	int count{};
	for (int j{}; j < numberSamples; j++) {
		while (stepsize != 1024)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i{}; i < size; i += stepsize)
			{
				intBuffer[i] *= 2;

			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			timings.at(count) += (elapsedTime/100.f);
			count++;
			stepsize *= 2;
		}
		count = 0;
		stepsize = 1;
	}
	delete[] intBuffer;
	intBuffer = nullptr; 
	//std::transform(timings.begin(), timings.end(), timings.begin(), [](float& c) { return c / 3; });
	std::for_each(timings.begin(), timings.end(), [](float& c) { c /= 3; });


	conf.values.ys = timings.data();
	conf.values.count = int(timings.size());
	conf.scale.min = 0;
	conf.scale.max = *std::max_element(timings.begin(),timings.end());
	conf.tooltip.show = false;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(300, 150);
	conf.line_thickness = 2.f;
	return timings;

}

std::vector<float> TrashTheCache::CalculateTrashTheCacheObject(int numberSamples, ImGui::PlotConfig& conf)
{
	/*int stepsize{ 1 };
	int size{ 67108864 };

	std::vector<GameObject3D> objectBuffer(size);
	std::vector<float> averages;
	static std::vector<float> timings;

	while (stepsize != 1024)
	{
		for (int j{}; j < numberSamples; j++) {
			auto start = std::chrono::high_resolution_clock::now();

		
			for (int i{}; i < objectBuffer.size(); i += stepsize)
			{
				objectBuffer[i].ID *= 2;

			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			averages.push_back(float(elapsedTime));
		}
		timings.push_back(GetAverage(averages) / 1000.f);
		averages.clear();
		stepsize *= 2;
	}*/

	int stepsize{ 1 };
	int size{ 67108864 };

	std::vector<GameObject3D> objectBuffer(size);

	std::vector<float> timings(10, 0);
	int count{};
	for (int j{}; j < numberSamples; j++) {
		while (stepsize != 1024)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i{}; i < size; i += stepsize)
			{
				objectBuffer[i].ID *= 2;

			}

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			timings.at(count) += elapsedTime / 1000.f;
			count++;
			stepsize *= 2;
		}
		count = 0;
		stepsize = 1;
	}
	//std::transform(timings.begin(), timings.end(), timings.begin(), [](float& c) { return c / 3; });
	std::for_each(timings.begin(), timings.end(), [](float& c) { c /= 3; });

	conf.values.ys = timings.data();
	conf.values.count = int(timings.size());
	conf.values.color = ImColor(0, 255, 0);
	conf.scale.min = 0;
	conf.scale.max = *std::max_element(timings.begin(), timings.end());
	conf.tooltip.show = false;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(300, 150);
	conf.line_thickness = 2.f;
	return timings;
}

std::vector<float> TrashTheCache::CalculateTrashTheCacheObjectPointer(int numberSamples, ImGui::PlotConfig& conf)
{
	int stepsize{ 1 };
	int size{ 67108864 };

	std::vector<GameObject3DAlt> objectBuffer(size);
	std::vector<float> averages;
	static std::vector<float> timings;

	while (stepsize != 1024)
	{
		for (int j{}; j < numberSamples; j++) {
			auto start = std::chrono::high_resolution_clock::now();


			for (int i{}; i < objectBuffer.size(); i += stepsize)
			{
				objectBuffer[i].ID *= 2;

			}
			auto end = std::chrono::high_resolution_clock::now();
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			averages.push_back(float(elapsedTime));
		}
		timings.push_back(GetAverage(averages) / 1000.f);
		averages.clear();
		stepsize *= 2;
	}

	conf.values.ys = timings.data();
	conf.values.count = int(timings.size());
	conf.values.color = ImColor(255, 0, 0);
	conf.scale.min = 0;
	conf.scale.max = *std::max_element(timings.begin(), timings.end());
	conf.tooltip.show = false;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(300, 150);
	conf.line_thickness = 2.f;

	return timings;
}

