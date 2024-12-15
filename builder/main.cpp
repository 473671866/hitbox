#include <iostream>
#include <memory>
#include <fstream>
#include <filesystem>

int main(int arg, char** argv) {
	if (arg < 3) {
		std::cout << "usage: " << " <source> <result>\n";
		return -1;
	}

	//读
	std::filesystem::path file_path(argv[1]);
	if (!std::filesystem::exists(file_path)) {
		std::cerr << "file not exists\n";
		return -2;
	}

	std::ifstream ifs(file_path, std::ios::binary);
	if (ifs.is_open() == false) {
		std::cerr << "open file failed\n";
		return -3;
	}

	auto filesize = std::filesystem::file_size(file_path);
	std::unique_ptr<unsigned char[]> filebuffer(new unsigned char[filesize]);
	ifs.read((char*)filebuffer.get(), filesize);
	if (ifs.fail()) {
		std::cerr << "file read failed\n";
		return -4;
	}

	//写
	std::filesystem::path directory(argv[2]);
	std::filesystem::path header = directory / file_path.replace_extension(".h").filename();
	std::filesystem::path source = directory / file_path.replace_extension(".cpp").filename();

	//头文件
	std::ofstream ofs(header, std::ios::binary);
	if (!ofs.is_open()) {
		std::cerr << "create .h failed\n";
		return -5;
	}
	ofs << "#pragma once\n";
	ofs << "extern unsigned char " << file_path.stem().string() << "[" << filesize << "];" << std::endl;
	ofs.close();

	//源文件
	ofs.open(source, std::ios::binary);
	if (!ofs.is_open()) {
		std::cerr << "create .cpp failed\n";
		return -6;
	}

	ofs << "#include \"" << header.filename().string() << "\"" << std::endl;
	ofs << "unsigned char " << file_path.stem().string() << "[" << filesize << "] = {" << std::endl;
	ofs << "\t";
	for (int i = 0; i < filesize; i++) {
		ofs << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(filebuffer[i]) << ", ";
		if ((i + 1) % 20 == 0) {
			ofs << "\r\n\t";
		}
	}
	ofs << "\r\n};";
	std::cout << "build " << header.filename().string() << " and " << source.filename().string() << " success\n";
	return 0;
}