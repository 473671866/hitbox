#pragma once
class memory
{
public:
	static bool probe(void* address, unsigned long long size, unsigned __int32 alignment);

	template<typename parameter>
	static parameter read(parameter address) {
		parameter result;
		__try {
			result = **(parameter**)(&address);
		}
		__except (1) {
			result = 0;
		}
		return result;
	}

	static bool hook(void** vtbl, void* handler, void* original, int index);
};
