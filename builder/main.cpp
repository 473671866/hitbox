#include <iostream>
#include <fstream>
#include <filesystem>
#include "scope_exit.hpp"

int main(int arg, char** argv) {
	if (arg < 3) {
		return -1;
	}

	//读
	std::filesystem::path file_path(argv[1]);
	if (!std::filesystem::exists(file_path)) {
		std::cerr << "文件不存在\n";
		system("pause");
		return -2;
	}

	std::ifstream istream(file_path, std::ios::binary);
	auto istream_close = std::make_scope_exit([&]() { istream.close(); });
	if (istream.is_open() == false) {
		std::cerr << "打开文件失败\n";
		system("pause");
		return -3;
	}

	auto filesize = std::filesystem::file_size(file_path);
	unsigned char* filebuffer = new unsigned char[filesize];
	auto delete_buffer = std::make_scope_exit([&]() { delete[] filebuffer; });
	istream.read((char*)filebuffer, filesize);
	if (istream.fail()) {
		std::cerr << "读取文件失败\n";
		system("pause");
		return -4;
	}

	//写
	std::filesystem::path directory(argv[2]);
	std::filesystem::path header = directory / file_path.replace_extension(".h").filename();
	std::filesystem::path source = directory / file_path.replace_extension(".cpp").filename();

	//头文件
	std::ofstream ostream(header, std::ios::binary);
	if (!ostream.is_open()) {
		std::cerr << "创建文件失败\n";
		system("pause");
		return -5;
	}
	ostream << "#pragma once\n";
	ostream << "extern unsigned char " << file_path.stem().string() << "[" << filesize << "];" << std::endl;
	ostream.close();

	//源文件
	ostream.open(source, std::ios::binary);
	if (!ostream.is_open()) {
		std::cerr << "创建文件失败\n";
		system("pause");
		return -6;
	}

	ostream << "#include \"" << header.filename().string() << "\"" << std::endl;
	ostream << "unsigned char " << file_path.stem().string() << "[" << filesize << "] = {" << std::endl;
	ostream << "\t";
	for (int i = 0; i < filesize; i++) {
		ostream << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(filebuffer[i]) << ", ";
		if ((i + 1) % 20 == 0) {
			ostream << "\r\n\t";
		}
	}
	ostream << "\r\n};";
	ostream.close();

	return 0;
}