//Header containing the definiton of a struct to hold window data

#ifndef WINDOW_DATA_H_
#define WINDOW_DATA_H_

//Standard Includes
#include <string>

namespace BratsGLUtilities
{
	struct WindowData
	{
		int xRes, yRes;
		std::string windowTitle;
//Column No:																 80		
		WindowData(int xRes = 800, int yRes = 600, std::string windowTitle):
							xRes(xRes), yRes(yRes), windowTitle(windowTitle)
		{
		}
	};
}

#endif