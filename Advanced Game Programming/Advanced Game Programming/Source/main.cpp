#include <iostream>
#include <memory>
#include "Engine.h"

int main(int argc, char *argv[]) {
	std::string path = "...";

	std::unique_ptr<Engine> engine = std::make_unique<Engine>();

	while (engine->run()) {}

	return 0;
}