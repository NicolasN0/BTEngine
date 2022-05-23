#pragma once
#include "imgui.h"
#include "imgui_plot.h"
namespace TrashTheCache
{
	

	void ShowTrashTheCacheWindow();
	std::vector<float> CalculateTrashTheCacheInt(int numberSamples, ImGui::PlotConfig& conf);
	std::vector<float> CalculateTrashTheCacheObject(int numberSamples, ImGui::PlotConfig& conf);
	std::vector<float> CalculateTrashTheCacheObjectPointer(int numberSamples, ImGui::PlotConfig& conf);
};