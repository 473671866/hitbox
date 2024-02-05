#include "searcher.h"

unsigned char searcher::hex(unsigned char* ch) {
	unsigned char temps[2] = { 0 };
	for (int i = 0; i < 2; i++) {
		if (ch[i] >= '0' && ch[i] <= '9') {
			temps[i] = (ch[i] - '0');
		}
		else if (ch[i] >= 'A' && ch[i] <= 'F') {
			temps[i] = (ch[i] - 'A') + 0xA;
		}
		else if (ch[i] >= 'a' && ch[i] <= 'f') {
			temps[i] = (ch[i] - 'a') + 0xA;
		}
	}
	return ((temps[0] << 4) & 0xf0) | (temps[1] & 0xf);
}

int searcher::initialize(unsigned char* hex, unsigned char* ch) {
	int i = 0;
	for (; *ch != '\0'; i++) {
		if (*ch == '*' || *ch == '?') {
			hex[i] = *ch;
			ch++;
			continue;
		}

		hex[i] = this->hex(ch);
		ch += 2;
	}
	return i;
}
unsigned __int64 searcher::compare(unsigned char* hex, unsigned __int64 length, unsigned __int64 start, unsigned __int64 end) {
	unsigned __int64 result = 0;
	unsigned __int64 j = 0;
	unsigned __int8* temp = nullptr;

	for (unsigned __int64 address = start; address <= end; address++) {
		temp = (unsigned char*)address;
		for (j = 0; j < length; j++) {
			if (hex[j] == '*' || hex[j] == '?') {
				continue;
			}

			if (temp[j] != hex[j]) {
				break;
			}

			if (j == (length - 1)) {
				result = address;
				break;
			}
		}
	}
	return result;
}