#include "MainApp.h"
#include "MiniGames/MainScreen.h"

int main()
{
	std::shared_ptr<MainApp> app = std::make_shared<MainApp>();
	app->onCreate();
	app->setLayer(new MainScreen);
	app->onUpdate();
	app->onDelete();

	return 0;
}