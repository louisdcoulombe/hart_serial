#ifndef HART_COMMAND_H
#define HART_COMMAND_H

#include "hart_type.h"

namespace hart
{
    class HartCommand : public IHartType
   {
 	public:
        HartCommand();
		virtual	size_t size() const override;
		virtual uint8_t operator[](int i) override;
		virtual std::string serialize() override;
		virtual util::Status deserialize(std::string value) override;

        util::Status add_type(IHartType* t);
    private:
        size_t m_data_size;
        std::vector<hart::IHartType*> m_type_list;
    };
};
#endif

