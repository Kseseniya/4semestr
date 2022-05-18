#include "tui.h"
#include "gui.h"
#include "game.h"
#include "humanc.h"
#include "botc.h"
#include "nearestc.h"
#include <cstring>
#include <memory>

int main(int argc, char **argv) {
	std::unique_ptr<View> ui{View::get(argc > 1 ? argv[1] : "tui")};
	ui->draw();
	Game game{};
	HumanC huc{game};
	BotC bot{game};
	NearestC bot1{game};
	ui->runloop();
}