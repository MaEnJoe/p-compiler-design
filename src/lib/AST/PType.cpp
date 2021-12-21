#include "AST/PType.hpp"

const char *kTypeString[] = {"void", "integer", "real", "boolean", "string"};

PType::PType(PrimitiveTypeEnum type) : type(type) {}

void PType::setDimensions(std::vector<uint64_t> &dims) {
    dimensions = std::move(dims);
}
std::vector<uint64_t> PType::getDimensions() const
{
    return dimensions;
}


const PType::PrimitiveTypeEnum PType::getPrimitiveType() const { return type; }

// logical constness
const char *PType::getPTypeCString() const {
    if (!type_string_is_valid) {
        type_string += kTypeString[static_cast<int>(type)];

        if (dimensions.size() != 0) {
            type_string += " ";

            for (const auto &dim : dimensions) {
                type_string += "[" + std::to_string(dim) + "]";
            }
        }
        type_string_is_valid = true;
    }

    return type_string.c_str();
}

bool PType::operator==(const PType& other) const
{
    if(type != other.type)return false;
    if(dimensions.size() != other.dimensions.size())return false;
    for(size_t i = 0 ; i != dimensions.size() ; i++)
    {
        if(dimensions[i] != other.dimensions[i])return false;
    }
    return true;
}
bool PType::isNumericScalar()const
{
    return ( (type == PType::PrimitiveTypeEnum::kRealType) || (type == PType::PrimitiveTypeEnum::kIntegerType) )
     && (dimensions.size() == 0);
}
bool PType::isStringScalar() const
{
    return ( (type == PType::PrimitiveTypeEnum::kStringType) && (dimensions.size() == 0) );
}
bool PType::isBoolScalar()const
{
    return ( (type == PType::PrimitiveTypeEnum::kBoolType) && (dimensions.size() == 0) );    
}

bool PType::isIntegerScalr() const
{
    return ( (type == PType::PrimitiveTypeEnum::kIntegerType) && (dimensions.size() == 0) );     
}




