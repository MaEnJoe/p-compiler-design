#ifndef __AST_PTYPE_H
#define __AST_PTYPE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

class PType;

typedef std::shared_ptr<const PType> PTypeSharedPtr;

class PType {
  public:
    enum class PrimitiveTypeEnum : uint8_t {
        kVoidType,
        kIntegerType,
        kRealType,
        kBoolType,
        kStringType
    };

    PType(PrimitiveTypeEnum type);
    ~PType() = default;

    void setDimensions(std::vector<uint64_t> &dims);
    std::vector<uint64_t> getDimensions() const;
    const PrimitiveTypeEnum getPrimitiveType() const;
    const char *getPTypeCString() const;
    
    bool operator==(const PType&) const;
    bool isNumericScalar()const;
    bool isStringScalar() const;
    bool isBoolScalar()const;
    bool isIntegerScalr() const;

  private:
    PrimitiveTypeEnum type;
    std::vector<uint64_t> dimensions;
    mutable std::string type_string;
    mutable bool type_string_is_valid = false;
};

#endif
