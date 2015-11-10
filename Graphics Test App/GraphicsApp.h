#ifndef _GRAPHICSAPP_H_
#define _GRAPHICSAPP_H_

#include "../Source/Core/Application/DefaultGameApp.h"

class GraphicsApp : public recon::IDefaultGameApp
{
public:
	GraphicsApp(const std::string& appName);
	virtual ~GraphicsApp() override;

protected:
	virtual bool Init() override;
	virtual void RunSingleLoop() override;
	virtual void Shutdown() override;
};

#endif // _GRAPHICSAPP_H_