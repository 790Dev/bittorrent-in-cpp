#include "BencodePrinter.h"

#include <iostream>
#include <variant>

void BencodePrinter::print(
    const BencodeValue& value,
    int indent
){
    std::visit(
        [&](auto&& arg)
        {
            using T =
                std::decay_t<decltype(arg)>;

            if constexpr (
                std::is_same_v<T,std::string>
            )
            {
                std::cout << arg;
            }

            else if constexpr (
                std::is_same_v<T,long long>
            )
            {
                std::cout << arg;
            }

            else if constexpr (
                std::is_same_v<T,BencodeList>
            )
            {
                std::cout << "[\n";

                for(const auto& item : arg)
                {
                    for(int i=0;i<indent+2;i++)
                        std::cout << ' ';

                    print(item,indent+2);

                    std::cout << '\n';
                }

                for(int i=0;i<indent;i++)
                    std::cout << ' ';

                std::cout << "]";
            }

            else if constexpr (
                std::is_same_v<T,BencodeDict>
            )
            {
                std::cout << "{\n";

                for(const auto& [key,val] : arg)
                {
                    for(int i=0;i<indent+2;i++)
                        std::cout << ' ';

                    std::cout
                        << key
                        << " : ";

                    print(val,indent+2);

                    std::cout << '\n';
                }

                for(int i=0;i<indent;i++)
                    std::cout << ' ';

                std::cout << "}";
            }
        },
        value.value
    );
}