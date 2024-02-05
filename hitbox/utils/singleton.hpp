#pragma once

template <class _Ty> class singleton
{
protected:
	singleton() {}

public:
	virtual ~singleton() {}

	template<typename ...Args> static _Ty* instance(Args&& ...args)
	{
		static _Ty instance(args...);
		return &instance;
	}
};