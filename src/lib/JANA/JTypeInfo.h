#ifndef _JTypeInfo_h_
#define _JTypeInfo_h_

#include <cxxabi.h>
#include <string>

namespace JTypeInfo {

template<typename T>
std::string demangle(void) {

	/// Return the demangled name (if available) for the type the template
	/// is based. Call it like this:
	///   cout << GetDemangledName<MyType>() << endl;
	int status = -1;
	auto cstr = abi::__cxa_demangle(typeid(T).name(), NULL, NULL, &status);
	std::string type(cstr);
	free(cstr);
	if (status != 0) type = typeid(T).name();
	return type;
}

template<typename T>
const char* builtin_typename() {

	if (typeid(T) == typeid(int) || typeid(T) == typeid(int32_t)) {
		return "int";
	} else if (typeid(T) == typeid(unsigned int) || typeid(T) == typeid(uint32_t)) {
		return "uint";
	} else if (typeid(T) == typeid(long) || typeid(T) == typeid(int64_t)) {
		return "long";
	} else if (typeid(T) == typeid(unsigned long) || typeid(T) == typeid(uint64_t)) {
		return "ulong";
	} else if (typeid(T) == typeid(short) || typeid(T) == typeid(int16_t)) {
		return "short";
	} else if (typeid(T) == typeid(unsigned short) || typeid(T) == typeid(uint16_t)) {
		return "ushort";
	} else if (typeid(T) == typeid(float)) {
		return "float";
	} else if (typeid(T) == typeid(double)) {
		return "double";
	} else if (typeid(T) == typeid(std::string) || typeid(T) == typeid(const char*) || typeid(T) == typeid(char*)) {
		return "string";
	} else {
		return "unknown";
	}
};

} // namespace JTypeInfo
#endif