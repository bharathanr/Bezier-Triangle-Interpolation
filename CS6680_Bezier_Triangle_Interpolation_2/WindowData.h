//Header containing the definiton of a struct to hold window data

#ifndef WINDOW_DATA_H_
#define WINDOW_DATA_H_

//Standard Includes
#include <string>

namespace BratsGLUtilities
{
	struct WindowData
	{
		int width, height;
		std::string windowTitle;
//Column No:																 80		
		WindowData(std::string windowTitle, int width = 800, int height = 600):
							width(width), height(height), windowTitle(windowTitle)
		{
		}
	};
}

#endif