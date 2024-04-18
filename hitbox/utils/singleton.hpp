#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include<mutex>
template <class cls>
class singleton
{
protected:
	singleton() {}

public:
	virtual ~singleton() {}

	template<typename ...args>
	static cls* instance(args&& ...params)
	{
		static std::once_flag flag = {};
		static cls* instance = nullptr;
		if (!instance) {
			std::call_once(flag, [&]() {
				if constexpr (sizeof...(params) > 0) {
					instance = new cls(params...);
				}
				else {
					instance = new cls();
				}
				});
		}
		return instance;
	}
};

#endif // SINGLETON_HPP