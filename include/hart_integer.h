#ifndef HART_INTEGER_H
#define HART_INTEGER_H

#include <vector>

#include "hart_type.h"

namespace hart
{
	class HartInteger : public IHartType
	{
	public:
		static constexpr const char* STRING = "int";

		HartInteger();
		HartInteger(int v);

		size_t size() const override;
		uint8_t operator[](int i) override;
		std::string serialize() override;
        util::Status deserialize(std::string value) override;

		// Implicit conversion to int
		int value() const; 
		// bool operator==(const int& v);
		// void operator=(int v);
        // operator int() const;

	private:
        std::vector<uint8_t> m_data;
		const size_t m_size = 4;

        int toInt() const;
        void fromInt(int v);
	};
};
#endif
