#pragma once

#define offsetes(structure, member) ((long long)&((structure*)0)->member) // 64λϵͳ

#define probe(cls, mbr, returned)			\
	if(cls == nullptr){						\
		return returned;					\
	}										\
											\
	if (cls->mbr == nullptr) {				\
		return returned;					\
	}										\