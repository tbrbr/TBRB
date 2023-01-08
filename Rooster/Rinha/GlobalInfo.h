#pragma once

struct GlobalInfo {
	bool firstIntro = true;
	int cash = 0;
};

struct GlobalInfo globalInfo;

void loadGlobalInfo(struct GlobalInfo &info) {
	std::ifstream file("globalInfo.txt");

	if (file.is_open()) {
		std::string line;

		std::getline(file, line);
		info.firstIntro = std::stoi(line);

		std::getline(file, line);
		info.cash = std::stoi(line);
	}
	else {
		println("Falha ao carregar globalInfo.txt");
	}
	file.close();
}

void saveGlobalInfo(struct GlobalInfo &info) {
	std::ofstream file("globalInfo.txt");

	if (file.is_open()) {
		file << info.firstIntro << std::endl;
		file << info.cash << std::endl;
	}
	else {
		println("Falha ao salvar globalInfo.txt");
	}

	file.close();
}

