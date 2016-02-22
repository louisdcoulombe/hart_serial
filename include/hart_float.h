#ifndef HART_FLOAT_H
#define HART_FLOAT_H

#include <vector>

#include "hart_type.h"

namespace hart
{
	class HartFloat : public IHartType
	{
	public:
		static constexpr const char* STRING = "float";

		HartFloat();
		HartFloat(float v);

		size_t size() const override;
		uint8_t operator[](int i) override;
		std::string serialize() override;
        util::Status deserialize(std::string value) override;

		// Implicit conversion to int
		float value() const; 
		// bool operator==(const int& v);
		// void operator=(int v);
        // operator int() const;

	private:
        std::vector<uint8_t> m_data;
		const size_t m_size = 4;

        float toFloat() const;
        void fromFloat(float v);
	};
};
#endif
