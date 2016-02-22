#ifdef HART_COMMAND_H
#define HART_COMMAND_H

#include "hart_type.h"

namespace hart
{
    class HartCommand : public IHartType
   {
 	public:
		virtual	size_t size() const = 0;
		//virtual typename TypeIterator begin() const = 0;
		//virtual typename TypeIterator end() const = 0;
        // hart_data_t data() = 0;
		virtual uint8_t operator[](int i) = 0;
		virtual std::string serialize() = 0;
		virtual util::Status deserialize(std::string value) = 0;
    private:
        std::vector<hart::IHartType*> m_type_list;
    }
};
#endif

