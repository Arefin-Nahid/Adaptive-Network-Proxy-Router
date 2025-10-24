//
// Generated file, do not edit! Created by opp_msgtool 6.2 from Modules/messages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "messages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(DHCPDiscover)

DHCPDiscover::DHCPDiscover(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

DHCPDiscover::DHCPDiscover(const DHCPDiscover& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

DHCPDiscover::~DHCPDiscover()
{
}

DHCPDiscover& DHCPDiscover::operator=(const DHCPDiscover& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DHCPDiscover::copy(const DHCPDiscover& other)
{
    this->clientMac = other.clientMac;
    this->transactionId = other.transactionId;
    this->timestamp = other.timestamp;
}

void DHCPDiscover::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->clientMac);
    doParsimPacking(b,this->transactionId);
    doParsimPacking(b,this->timestamp);
}

void DHCPDiscover::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->clientMac);
    doParsimUnpacking(b,this->transactionId);
    doParsimUnpacking(b,this->timestamp);
}

const char * DHCPDiscover::getClientMac() const
{
    return this->clientMac.c_str();
}

void DHCPDiscover::setClientMac(const char * clientMac)
{
    this->clientMac = clientMac;
}

const char * DHCPDiscover::getTransactionId() const
{
    return this->transactionId.c_str();
}

void DHCPDiscover::setTransactionId(const char * transactionId)
{
    this->transactionId = transactionId;
}

double DHCPDiscover::getTimestamp() const
{
    return this->timestamp;
}

void DHCPDiscover::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class DHCPDiscoverDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientMac,
        FIELD_transactionId,
        FIELD_timestamp,
    };
  public:
    DHCPDiscoverDescriptor();
    virtual ~DHCPDiscoverDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPDiscoverDescriptor)

DHCPDiscoverDescriptor::DHCPDiscoverDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPDiscover)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

DHCPDiscoverDescriptor::~DHCPDiscoverDescriptor()
{
    delete[] propertyNames;
}

bool DHCPDiscoverDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPDiscover *>(obj)!=nullptr;
}

const char **DHCPDiscoverDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPDiscoverDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPDiscoverDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int DHCPDiscoverDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientMac
        FD_ISEDITABLE,    // FIELD_transactionId
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *DHCPDiscoverDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientMac",
        "transactionId",
        "timestamp",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int DHCPDiscoverDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientMac") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "transactionId") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPDiscoverDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_clientMac
        "string",    // FIELD_transactionId
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPDiscoverDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DHCPDiscoverDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int DHCPDiscoverDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPDiscoverDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPDiscover'", field);
    }
}

const char *DHCPDiscoverDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPDiscoverDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: return oppstring2string(pp->getClientMac());
        case FIELD_transactionId: return oppstring2string(pp->getTransactionId());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void DHCPDiscoverDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: pp->setClientMac((value)); break;
        case FIELD_transactionId: pp->setTransactionId((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPDiscover'", field);
    }
}

omnetpp::cValue DHCPDiscoverDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: return pp->getClientMac();
        case FIELD_transactionId: return pp->getTransactionId();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPDiscover' as cValue -- field index out of range?", field);
    }
}

void DHCPDiscoverDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: pp->setClientMac(value.stringValue()); break;
        case FIELD_transactionId: pp->setTransactionId(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPDiscover'", field);
    }
}

const char *DHCPDiscoverDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPDiscoverDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPDiscoverDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPDiscover *pp = omnetpp::fromAnyPtr<DHCPDiscover>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPDiscover'", field);
    }
}

Register_Class(DHCPOffer)

DHCPOffer::DHCPOffer(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

DHCPOffer::DHCPOffer(const DHCPOffer& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

DHCPOffer::~DHCPOffer()
{
}

DHCPOffer& DHCPOffer::operator=(const DHCPOffer& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DHCPOffer::copy(const DHCPOffer& other)
{
    this->serverMac = other.serverMac;
    this->clientMac = other.clientMac;
    this->offeredIP = other.offeredIP;
    this->serverIP = other.serverIP;
    this->leaseTime = other.leaseTime;
    this->transactionId = other.transactionId;
    this->isRogue_ = other.isRogue_;
}

void DHCPOffer::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->serverMac);
    doParsimPacking(b,this->clientMac);
    doParsimPacking(b,this->offeredIP);
    doParsimPacking(b,this->serverIP);
    doParsimPacking(b,this->leaseTime);
    doParsimPacking(b,this->transactionId);
    doParsimPacking(b,this->isRogue_);
}

void DHCPOffer::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->serverMac);
    doParsimUnpacking(b,this->clientMac);
    doParsimUnpacking(b,this->offeredIP);
    doParsimUnpacking(b,this->serverIP);
    doParsimUnpacking(b,this->leaseTime);
    doParsimUnpacking(b,this->transactionId);
    doParsimUnpacking(b,this->isRogue_);
}

const char * DHCPOffer::getServerMac() const
{
    return this->serverMac.c_str();
}

void DHCPOffer::setServerMac(const char * serverMac)
{
    this->serverMac = serverMac;
}

const char * DHCPOffer::getClientMac() const
{
    return this->clientMac.c_str();
}

void DHCPOffer::setClientMac(const char * clientMac)
{
    this->clientMac = clientMac;
}

const char * DHCPOffer::getOfferedIP() const
{
    return this->offeredIP.c_str();
}

void DHCPOffer::setOfferedIP(const char * offeredIP)
{
    this->offeredIP = offeredIP;
}

const char * DHCPOffer::getServerIP() const
{
    return this->serverIP.c_str();
}

void DHCPOffer::setServerIP(const char * serverIP)
{
    this->serverIP = serverIP;
}

double DHCPOffer::getLeaseTime() const
{
    return this->leaseTime;
}

void DHCPOffer::setLeaseTime(double leaseTime)
{
    this->leaseTime = leaseTime;
}

const char * DHCPOffer::getTransactionId() const
{
    return this->transactionId.c_str();
}

void DHCPOffer::setTransactionId(const char * transactionId)
{
    this->transactionId = transactionId;
}

bool DHCPOffer::isRogue() const
{
    return this->isRogue_;
}

void DHCPOffer::setIsRogue(bool isRogue)
{
    this->isRogue_ = isRogue;
}

class DHCPOfferDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_serverMac,
        FIELD_clientMac,
        FIELD_offeredIP,
        FIELD_serverIP,
        FIELD_leaseTime,
        FIELD_transactionId,
        FIELD_isRogue,
    };
  public:
    DHCPOfferDescriptor();
    virtual ~DHCPOfferDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPOfferDescriptor)

DHCPOfferDescriptor::DHCPOfferDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPOffer)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

DHCPOfferDescriptor::~DHCPOfferDescriptor()
{
    delete[] propertyNames;
}

bool DHCPOfferDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPOffer *>(obj)!=nullptr;
}

const char **DHCPOfferDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPOfferDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPOfferDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int DHCPOfferDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_serverMac
        FD_ISEDITABLE,    // FIELD_clientMac
        FD_ISEDITABLE,    // FIELD_offeredIP
        FD_ISEDITABLE,    // FIELD_serverIP
        FD_ISEDITABLE,    // FIELD_leaseTime
        FD_ISEDITABLE,    // FIELD_transactionId
        FD_ISEDITABLE,    // FIELD_isRogue
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *DHCPOfferDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "serverMac",
        "clientMac",
        "offeredIP",
        "serverIP",
        "leaseTime",
        "transactionId",
        "isRogue",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int DHCPOfferDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "serverMac") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "clientMac") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "offeredIP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "serverIP") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "leaseTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "transactionId") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isRogue") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPOfferDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_serverMac
        "string",    // FIELD_clientMac
        "string",    // FIELD_offeredIP
        "string",    // FIELD_serverIP
        "double",    // FIELD_leaseTime
        "string",    // FIELD_transactionId
        "bool",    // FIELD_isRogue
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPOfferDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_leaseTime: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DHCPOfferDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_leaseTime:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int DHCPOfferDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPOfferDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPOffer'", field);
    }
}

const char *DHCPOfferDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPOfferDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: return oppstring2string(pp->getServerMac());
        case FIELD_clientMac: return oppstring2string(pp->getClientMac());
        case FIELD_offeredIP: return oppstring2string(pp->getOfferedIP());
        case FIELD_serverIP: return oppstring2string(pp->getServerIP());
        case FIELD_leaseTime: return double2string(pp->getLeaseTime());
        case FIELD_transactionId: return oppstring2string(pp->getTransactionId());
        case FIELD_isRogue: return bool2string(pp->isRogue());
        default: return "";
    }
}

void DHCPOfferDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: pp->setServerMac((value)); break;
        case FIELD_clientMac: pp->setClientMac((value)); break;
        case FIELD_offeredIP: pp->setOfferedIP((value)); break;
        case FIELD_serverIP: pp->setServerIP((value)); break;
        case FIELD_leaseTime: pp->setLeaseTime(string2double(value)); break;
        case FIELD_transactionId: pp->setTransactionId((value)); break;
        case FIELD_isRogue: pp->setIsRogue(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPOffer'", field);
    }
}

omnetpp::cValue DHCPOfferDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: return pp->getServerMac();
        case FIELD_clientMac: return pp->getClientMac();
        case FIELD_offeredIP: return pp->getOfferedIP();
        case FIELD_serverIP: return pp->getServerIP();
        case FIELD_leaseTime: return pp->getLeaseTime();
        case FIELD_transactionId: return pp->getTransactionId();
        case FIELD_isRogue: return pp->isRogue();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPOffer' as cValue -- field index out of range?", field);
    }
}

void DHCPOfferDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: pp->setServerMac(value.stringValue()); break;
        case FIELD_clientMac: pp->setClientMac(value.stringValue()); break;
        case FIELD_offeredIP: pp->setOfferedIP(value.stringValue()); break;
        case FIELD_serverIP: pp->setServerIP(value.stringValue()); break;
        case FIELD_leaseTime: pp->setLeaseTime(value.doubleValue()); break;
        case FIELD_transactionId: pp->setTransactionId(value.stringValue()); break;
        case FIELD_isRogue: pp->setIsRogue(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPOffer'", field);
    }
}

const char *DHCPOfferDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPOfferDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPOfferDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPOffer *pp = omnetpp::fromAnyPtr<DHCPOffer>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPOffer'", field);
    }
}

Register_Class(DHCPRequest)

DHCPRequest::DHCPRequest(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

DHCPRequest::DHCPRequest(const DHCPRequest& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

DHCPRequest::~DHCPRequest()
{
}

DHCPRequest& DHCPRequest::operator=(const DHCPRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DHCPRequest::copy(const DHCPRequest& other)
{
    this->clientMac = other.clientMac;
    this->requestedIP = other.requestedIP;
    this->serverIP = other.serverIP;
    this->transactionId = other.transactionId;
    this->timestamp = other.timestamp;
}

void DHCPRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->clientMac);
    doParsimPacking(b,this->requestedIP);
    doParsimPacking(b,this->serverIP);
    doParsimPacking(b,this->transactionId);
    doParsimPacking(b,this->timestamp);
}

void DHCPRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->clientMac);
    doParsimUnpacking(b,this->requestedIP);
    doParsimUnpacking(b,this->serverIP);
    doParsimUnpacking(b,this->transactionId);
    doParsimUnpacking(b,this->timestamp);
}

const char * DHCPRequest::getClientMac() const
{
    return this->clientMac.c_str();
}

void DHCPRequest::setClientMac(const char * clientMac)
{
    this->clientMac = clientMac;
}

const char * DHCPRequest::getRequestedIP() const
{
    return this->requestedIP.c_str();
}

void DHCPRequest::setRequestedIP(const char * requestedIP)
{
    this->requestedIP = requestedIP;
}

const char * DHCPRequest::getServerIP() const
{
    return this->serverIP.c_str();
}

void DHCPRequest::setServerIP(const char * serverIP)
{
    this->serverIP = serverIP;
}

const char * DHCPRequest::getTransactionId() const
{
    return this->transactionId.c_str();
}

void DHCPRequest::setTransactionId(const char * transactionId)
{
    this->transactionId = transactionId;
}

double DHCPRequest::getTimestamp() const
{
    return this->timestamp;
}

void DHCPRequest::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class DHCPRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_clientMac,
        FIELD_requestedIP,
        FIELD_serverIP,
        FIELD_transactionId,
        FIELD_timestamp,
    };
  public:
    DHCPRequestDescriptor();
    virtual ~DHCPRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPRequestDescriptor)

DHCPRequestDescriptor::DHCPRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPRequest)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

DHCPRequestDescriptor::~DHCPRequestDescriptor()
{
    delete[] propertyNames;
}

bool DHCPRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPRequest *>(obj)!=nullptr;
}

const char **DHCPRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int DHCPRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_clientMac
        FD_ISEDITABLE,    // FIELD_requestedIP
        FD_ISEDITABLE,    // FIELD_serverIP
        FD_ISEDITABLE,    // FIELD_transactionId
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *DHCPRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "clientMac",
        "requestedIP",
        "serverIP",
        "transactionId",
        "timestamp",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int DHCPRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "clientMac") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "requestedIP") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "serverIP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "transactionId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_clientMac
        "string",    // FIELD_requestedIP
        "string",    // FIELD_serverIP
        "string",    // FIELD_transactionId
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DHCPRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int DHCPRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPRequest'", field);
    }
}

const char *DHCPRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: return oppstring2string(pp->getClientMac());
        case FIELD_requestedIP: return oppstring2string(pp->getRequestedIP());
        case FIELD_serverIP: return oppstring2string(pp->getServerIP());
        case FIELD_transactionId: return oppstring2string(pp->getTransactionId());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void DHCPRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: pp->setClientMac((value)); break;
        case FIELD_requestedIP: pp->setRequestedIP((value)); break;
        case FIELD_serverIP: pp->setServerIP((value)); break;
        case FIELD_transactionId: pp->setTransactionId((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

omnetpp::cValue DHCPRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: return pp->getClientMac();
        case FIELD_requestedIP: return pp->getRequestedIP();
        case FIELD_serverIP: return pp->getServerIP();
        case FIELD_transactionId: return pp->getTransactionId();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPRequest' as cValue -- field index out of range?", field);
    }
}

void DHCPRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_clientMac: pp->setClientMac(value.stringValue()); break;
        case FIELD_requestedIP: pp->setRequestedIP(value.stringValue()); break;
        case FIELD_serverIP: pp->setServerIP(value.stringValue()); break;
        case FIELD_transactionId: pp->setTransactionId(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

const char *DHCPRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPRequest *pp = omnetpp::fromAnyPtr<DHCPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPRequest'", field);
    }
}

Register_Class(DHCPAck)

DHCPAck::DHCPAck(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

DHCPAck::DHCPAck(const DHCPAck& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

DHCPAck::~DHCPAck()
{
}

DHCPAck& DHCPAck::operator=(const DHCPAck& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void DHCPAck::copy(const DHCPAck& other)
{
    this->serverMac = other.serverMac;
    this->clientMac = other.clientMac;
    this->assignedIP = other.assignedIP;
    this->serverIP = other.serverIP;
    this->leaseTime = other.leaseTime;
    this->transactionId = other.transactionId;
    this->isRogue_ = other.isRogue_;
}

void DHCPAck::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->serverMac);
    doParsimPacking(b,this->clientMac);
    doParsimPacking(b,this->assignedIP);
    doParsimPacking(b,this->serverIP);
    doParsimPacking(b,this->leaseTime);
    doParsimPacking(b,this->transactionId);
    doParsimPacking(b,this->isRogue_);
}

void DHCPAck::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->serverMac);
    doParsimUnpacking(b,this->clientMac);
    doParsimUnpacking(b,this->assignedIP);
    doParsimUnpacking(b,this->serverIP);
    doParsimUnpacking(b,this->leaseTime);
    doParsimUnpacking(b,this->transactionId);
    doParsimUnpacking(b,this->isRogue_);
}

const char * DHCPAck::getServerMac() const
{
    return this->serverMac.c_str();
}

void DHCPAck::setServerMac(const char * serverMac)
{
    this->serverMac = serverMac;
}

const char * DHCPAck::getClientMac() const
{
    return this->clientMac.c_str();
}

void DHCPAck::setClientMac(const char * clientMac)
{
    this->clientMac = clientMac;
}

const char * DHCPAck::getAssignedIP() const
{
    return this->assignedIP.c_str();
}

void DHCPAck::setAssignedIP(const char * assignedIP)
{
    this->assignedIP = assignedIP;
}

const char * DHCPAck::getServerIP() const
{
    return this->serverIP.c_str();
}

void DHCPAck::setServerIP(const char * serverIP)
{
    this->serverIP = serverIP;
}

double DHCPAck::getLeaseTime() const
{
    return this->leaseTime;
}

void DHCPAck::setLeaseTime(double leaseTime)
{
    this->leaseTime = leaseTime;
}

const char * DHCPAck::getTransactionId() const
{
    return this->transactionId.c_str();
}

void DHCPAck::setTransactionId(const char * transactionId)
{
    this->transactionId = transactionId;
}

bool DHCPAck::isRogue() const
{
    return this->isRogue_;
}

void DHCPAck::setIsRogue(bool isRogue)
{
    this->isRogue_ = isRogue;
}

class DHCPAckDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_serverMac,
        FIELD_clientMac,
        FIELD_assignedIP,
        FIELD_serverIP,
        FIELD_leaseTime,
        FIELD_transactionId,
        FIELD_isRogue,
    };
  public:
    DHCPAckDescriptor();
    virtual ~DHCPAckDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(DHCPAckDescriptor)

DHCPAckDescriptor::DHCPAckDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(DHCPAck)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

DHCPAckDescriptor::~DHCPAckDescriptor()
{
    delete[] propertyNames;
}

bool DHCPAckDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<DHCPAck *>(obj)!=nullptr;
}

const char **DHCPAckDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *DHCPAckDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int DHCPAckDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int DHCPAckDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_serverMac
        FD_ISEDITABLE,    // FIELD_clientMac
        FD_ISEDITABLE,    // FIELD_assignedIP
        FD_ISEDITABLE,    // FIELD_serverIP
        FD_ISEDITABLE,    // FIELD_leaseTime
        FD_ISEDITABLE,    // FIELD_transactionId
        FD_ISEDITABLE,    // FIELD_isRogue
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *DHCPAckDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "serverMac",
        "clientMac",
        "assignedIP",
        "serverIP",
        "leaseTime",
        "transactionId",
        "isRogue",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int DHCPAckDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "serverMac") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "clientMac") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "assignedIP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "serverIP") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "leaseTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "transactionId") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isRogue") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *DHCPAckDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_serverMac
        "string",    // FIELD_clientMac
        "string",    // FIELD_assignedIP
        "string",    // FIELD_serverIP
        "double",    // FIELD_leaseTime
        "string",    // FIELD_transactionId
        "bool",    // FIELD_isRogue
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **DHCPAckDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_leaseTime: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *DHCPAckDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_leaseTime:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int DHCPAckDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void DHCPAckDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'DHCPAck'", field);
    }
}

const char *DHCPAckDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string DHCPAckDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: return oppstring2string(pp->getServerMac());
        case FIELD_clientMac: return oppstring2string(pp->getClientMac());
        case FIELD_assignedIP: return oppstring2string(pp->getAssignedIP());
        case FIELD_serverIP: return oppstring2string(pp->getServerIP());
        case FIELD_leaseTime: return double2string(pp->getLeaseTime());
        case FIELD_transactionId: return oppstring2string(pp->getTransactionId());
        case FIELD_isRogue: return bool2string(pp->isRogue());
        default: return "";
    }
}

void DHCPAckDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: pp->setServerMac((value)); break;
        case FIELD_clientMac: pp->setClientMac((value)); break;
        case FIELD_assignedIP: pp->setAssignedIP((value)); break;
        case FIELD_serverIP: pp->setServerIP((value)); break;
        case FIELD_leaseTime: pp->setLeaseTime(string2double(value)); break;
        case FIELD_transactionId: pp->setTransactionId((value)); break;
        case FIELD_isRogue: pp->setIsRogue(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPAck'", field);
    }
}

omnetpp::cValue DHCPAckDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: return pp->getServerMac();
        case FIELD_clientMac: return pp->getClientMac();
        case FIELD_assignedIP: return pp->getAssignedIP();
        case FIELD_serverIP: return pp->getServerIP();
        case FIELD_leaseTime: return pp->getLeaseTime();
        case FIELD_transactionId: return pp->getTransactionId();
        case FIELD_isRogue: return pp->isRogue();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'DHCPAck' as cValue -- field index out of range?", field);
    }
}

void DHCPAckDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        case FIELD_serverMac: pp->setServerMac(value.stringValue()); break;
        case FIELD_clientMac: pp->setClientMac(value.stringValue()); break;
        case FIELD_assignedIP: pp->setAssignedIP(value.stringValue()); break;
        case FIELD_serverIP: pp->setServerIP(value.stringValue()); break;
        case FIELD_leaseTime: pp->setLeaseTime(value.doubleValue()); break;
        case FIELD_transactionId: pp->setTransactionId(value.stringValue()); break;
        case FIELD_isRogue: pp->setIsRogue(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPAck'", field);
    }
}

const char *DHCPAckDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr DHCPAckDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void DHCPAckDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    DHCPAck *pp = omnetpp::fromAnyPtr<DHCPAck>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'DHCPAck'", field);
    }
}

Register_Class(HTTPRequest)

HTTPRequest::HTTPRequest(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

HTTPRequest::HTTPRequest(const HTTPRequest& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

HTTPRequest::~HTTPRequest()
{
}

HTTPRequest& HTTPRequest::operator=(const HTTPRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void HTTPRequest::copy(const HTTPRequest& other)
{
    this->method = other.method;
    this->url = other.url;
    this->host = other.host;
    this->userAgent = other.userAgent;
    this->timestamp = other.timestamp;
    this->cacheKey = other.cacheKey;
    this->bypassCache = other.bypassCache;
}

void HTTPRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->method);
    doParsimPacking(b,this->url);
    doParsimPacking(b,this->host);
    doParsimPacking(b,this->userAgent);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->bypassCache);
}

void HTTPRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->method);
    doParsimUnpacking(b,this->url);
    doParsimUnpacking(b,this->host);
    doParsimUnpacking(b,this->userAgent);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->bypassCache);
}

const char * HTTPRequest::getMethod() const
{
    return this->method.c_str();
}

void HTTPRequest::setMethod(const char * method)
{
    this->method = method;
}

const char * HTTPRequest::getUrl() const
{
    return this->url.c_str();
}

void HTTPRequest::setUrl(const char * url)
{
    this->url = url;
}

const char * HTTPRequest::getHost() const
{
    return this->host.c_str();
}

void HTTPRequest::setHost(const char * host)
{
    this->host = host;
}

const char * HTTPRequest::getUserAgent() const
{
    return this->userAgent.c_str();
}

void HTTPRequest::setUserAgent(const char * userAgent)
{
    this->userAgent = userAgent;
}

double HTTPRequest::getTimestamp() const
{
    return this->timestamp;
}

void HTTPRequest::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

const char * HTTPRequest::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void HTTPRequest::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

bool HTTPRequest::getBypassCache() const
{
    return this->bypassCache;
}

void HTTPRequest::setBypassCache(bool bypassCache)
{
    this->bypassCache = bypassCache;
}

class HTTPRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_method,
        FIELD_url,
        FIELD_host,
        FIELD_userAgent,
        FIELD_timestamp,
        FIELD_cacheKey,
        FIELD_bypassCache,
    };
  public:
    HTTPRequestDescriptor();
    virtual ~HTTPRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(HTTPRequestDescriptor)

HTTPRequestDescriptor::HTTPRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(HTTPRequest)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

HTTPRequestDescriptor::~HTTPRequestDescriptor()
{
    delete[] propertyNames;
}

bool HTTPRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HTTPRequest *>(obj)!=nullptr;
}

const char **HTTPRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HTTPRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HTTPRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int HTTPRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_method
        FD_ISEDITABLE,    // FIELD_url
        FD_ISEDITABLE,    // FIELD_host
        FD_ISEDITABLE,    // FIELD_userAgent
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_bypassCache
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *HTTPRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "method",
        "url",
        "host",
        "userAgent",
        "timestamp",
        "cacheKey",
        "bypassCache",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int HTTPRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "method") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "url") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "host") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "userAgent") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "bypassCache") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *HTTPRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_method
        "string",    // FIELD_url
        "string",    // FIELD_host
        "string",    // FIELD_userAgent
        "double",    // FIELD_timestamp
        "string",    // FIELD_cacheKey
        "bool",    // FIELD_bypassCache
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **HTTPRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HTTPRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int HTTPRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HTTPRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HTTPRequest'", field);
    }
}

const char *HTTPRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HTTPRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_method: return oppstring2string(pp->getMethod());
        case FIELD_url: return oppstring2string(pp->getUrl());
        case FIELD_host: return oppstring2string(pp->getHost());
        case FIELD_userAgent: return oppstring2string(pp->getUserAgent());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_bypassCache: return bool2string(pp->getBypassCache());
        default: return "";
    }
}

void HTTPRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_method: pp->setMethod((value)); break;
        case FIELD_url: pp->setUrl((value)); break;
        case FIELD_host: pp->setHost((value)); break;
        case FIELD_userAgent: pp->setUserAgent((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_bypassCache: pp->setBypassCache(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPRequest'", field);
    }
}

omnetpp::cValue HTTPRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_method: return pp->getMethod();
        case FIELD_url: return pp->getUrl();
        case FIELD_host: return pp->getHost();
        case FIELD_userAgent: return pp->getUserAgent();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_bypassCache: return pp->getBypassCache();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HTTPRequest' as cValue -- field index out of range?", field);
    }
}

void HTTPRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        case FIELD_method: pp->setMethod(value.stringValue()); break;
        case FIELD_url: pp->setUrl(value.stringValue()); break;
        case FIELD_host: pp->setHost(value.stringValue()); break;
        case FIELD_userAgent: pp->setUserAgent(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_bypassCache: pp->setBypassCache(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPRequest'", field);
    }
}

const char *HTTPRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr HTTPRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HTTPRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPRequest *pp = omnetpp::fromAnyPtr<HTTPRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPRequest'", field);
    }
}

Register_Class(HTTPResponse)

HTTPResponse::HTTPResponse(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

HTTPResponse::HTTPResponse(const HTTPResponse& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

HTTPResponse::~HTTPResponse()
{
}

HTTPResponse& HTTPResponse::operator=(const HTTPResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void HTTPResponse::copy(const HTTPResponse& other)
{
    this->statusCode = other.statusCode;
    this->contentType = other.contentType;
    this->contentLength = other.contentLength;
    this->etag = other.etag;
    this->lastModified = other.lastModified;
    this->expires = other.expires;
    this->cacheControl = other.cacheControl;
    this->contentHash = other.contentHash;
    this->fromCache = other.fromCache;
    this->responseTime = other.responseTime;
}

void HTTPResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->statusCode);
    doParsimPacking(b,this->contentType);
    doParsimPacking(b,this->contentLength);
    doParsimPacking(b,this->etag);
    doParsimPacking(b,this->lastModified);
    doParsimPacking(b,this->expires);
    doParsimPacking(b,this->cacheControl);
    doParsimPacking(b,this->contentHash);
    doParsimPacking(b,this->fromCache);
    doParsimPacking(b,this->responseTime);
}

void HTTPResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->statusCode);
    doParsimUnpacking(b,this->contentType);
    doParsimUnpacking(b,this->contentLength);
    doParsimUnpacking(b,this->etag);
    doParsimUnpacking(b,this->lastModified);
    doParsimUnpacking(b,this->expires);
    doParsimUnpacking(b,this->cacheControl);
    doParsimUnpacking(b,this->contentHash);
    doParsimUnpacking(b,this->fromCache);
    doParsimUnpacking(b,this->responseTime);
}

int HTTPResponse::getStatusCode() const
{
    return this->statusCode;
}

void HTTPResponse::setStatusCode(int statusCode)
{
    this->statusCode = statusCode;
}

const char * HTTPResponse::getContentType() const
{
    return this->contentType.c_str();
}

void HTTPResponse::setContentType(const char * contentType)
{
    this->contentType = contentType;
}

int HTTPResponse::getContentLength() const
{
    return this->contentLength;
}

void HTTPResponse::setContentLength(int contentLength)
{
    this->contentLength = contentLength;
}

const char * HTTPResponse::getEtag() const
{
    return this->etag.c_str();
}

void HTTPResponse::setEtag(const char * etag)
{
    this->etag = etag;
}

double HTTPResponse::getLastModified() const
{
    return this->lastModified;
}

void HTTPResponse::setLastModified(double lastModified)
{
    this->lastModified = lastModified;
}

double HTTPResponse::getExpires() const
{
    return this->expires;
}

void HTTPResponse::setExpires(double expires)
{
    this->expires = expires;
}

const char * HTTPResponse::getCacheControl() const
{
    return this->cacheControl.c_str();
}

void HTTPResponse::setCacheControl(const char * cacheControl)
{
    this->cacheControl = cacheControl;
}

const char * HTTPResponse::getContentHash() const
{
    return this->contentHash.c_str();
}

void HTTPResponse::setContentHash(const char * contentHash)
{
    this->contentHash = contentHash;
}

bool HTTPResponse::getFromCache() const
{
    return this->fromCache;
}

void HTTPResponse::setFromCache(bool fromCache)
{
    this->fromCache = fromCache;
}

double HTTPResponse::getResponseTime() const
{
    return this->responseTime;
}

void HTTPResponse::setResponseTime(double responseTime)
{
    this->responseTime = responseTime;
}

class HTTPResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_statusCode,
        FIELD_contentType,
        FIELD_contentLength,
        FIELD_etag,
        FIELD_lastModified,
        FIELD_expires,
        FIELD_cacheControl,
        FIELD_contentHash,
        FIELD_fromCache,
        FIELD_responseTime,
    };
  public:
    HTTPResponseDescriptor();
    virtual ~HTTPResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(HTTPResponseDescriptor)

HTTPResponseDescriptor::HTTPResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(HTTPResponse)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

HTTPResponseDescriptor::~HTTPResponseDescriptor()
{
    delete[] propertyNames;
}

bool HTTPResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<HTTPResponse *>(obj)!=nullptr;
}

const char **HTTPResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *HTTPResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int HTTPResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 10+base->getFieldCount() : 10;
}

unsigned int HTTPResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_statusCode
        FD_ISEDITABLE,    // FIELD_contentType
        FD_ISEDITABLE,    // FIELD_contentLength
        FD_ISEDITABLE,    // FIELD_etag
        FD_ISEDITABLE,    // FIELD_lastModified
        FD_ISEDITABLE,    // FIELD_expires
        FD_ISEDITABLE,    // FIELD_cacheControl
        FD_ISEDITABLE,    // FIELD_contentHash
        FD_ISEDITABLE,    // FIELD_fromCache
        FD_ISEDITABLE,    // FIELD_responseTime
    };
    return (field >= 0 && field < 10) ? fieldTypeFlags[field] : 0;
}

const char *HTTPResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "statusCode",
        "contentType",
        "contentLength",
        "etag",
        "lastModified",
        "expires",
        "cacheControl",
        "contentHash",
        "fromCache",
        "responseTime",
    };
    return (field >= 0 && field < 10) ? fieldNames[field] : nullptr;
}

int HTTPResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "statusCode") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "contentType") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "contentLength") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "etag") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "lastModified") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "expires") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "cacheControl") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "contentHash") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "fromCache") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "responseTime") == 0) return baseIndex + 9;
    return base ? base->findField(fieldName) : -1;
}

const char *HTTPResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_statusCode
        "string",    // FIELD_contentType
        "int",    // FIELD_contentLength
        "string",    // FIELD_etag
        "double",    // FIELD_lastModified
        "double",    // FIELD_expires
        "string",    // FIELD_cacheControl
        "string",    // FIELD_contentHash
        "bool",    // FIELD_fromCache
        "double",    // FIELD_responseTime
    };
    return (field >= 0 && field < 10) ? fieldTypeStrings[field] : nullptr;
}

const char **HTTPResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lastModified: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_expires: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_responseTime: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *HTTPResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_lastModified:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_expires:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_responseTime:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int HTTPResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void HTTPResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'HTTPResponse'", field);
    }
}

const char *HTTPResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string HTTPResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: return long2string(pp->getStatusCode());
        case FIELD_contentType: return oppstring2string(pp->getContentType());
        case FIELD_contentLength: return long2string(pp->getContentLength());
        case FIELD_etag: return oppstring2string(pp->getEtag());
        case FIELD_lastModified: return double2string(pp->getLastModified());
        case FIELD_expires: return double2string(pp->getExpires());
        case FIELD_cacheControl: return oppstring2string(pp->getCacheControl());
        case FIELD_contentHash: return oppstring2string(pp->getContentHash());
        case FIELD_fromCache: return bool2string(pp->getFromCache());
        case FIELD_responseTime: return double2string(pp->getResponseTime());
        default: return "";
    }
}

void HTTPResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: pp->setStatusCode(string2long(value)); break;
        case FIELD_contentType: pp->setContentType((value)); break;
        case FIELD_contentLength: pp->setContentLength(string2long(value)); break;
        case FIELD_etag: pp->setEtag((value)); break;
        case FIELD_lastModified: pp->setLastModified(string2double(value)); break;
        case FIELD_expires: pp->setExpires(string2double(value)); break;
        case FIELD_cacheControl: pp->setCacheControl((value)); break;
        case FIELD_contentHash: pp->setContentHash((value)); break;
        case FIELD_fromCache: pp->setFromCache(string2bool(value)); break;
        case FIELD_responseTime: pp->setResponseTime(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPResponse'", field);
    }
}

omnetpp::cValue HTTPResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: return pp->getStatusCode();
        case FIELD_contentType: return pp->getContentType();
        case FIELD_contentLength: return pp->getContentLength();
        case FIELD_etag: return pp->getEtag();
        case FIELD_lastModified: return pp->getLastModified();
        case FIELD_expires: return pp->getExpires();
        case FIELD_cacheControl: return pp->getCacheControl();
        case FIELD_contentHash: return pp->getContentHash();
        case FIELD_fromCache: return pp->getFromCache();
        case FIELD_responseTime: return pp->getResponseTime();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'HTTPResponse' as cValue -- field index out of range?", field);
    }
}

void HTTPResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        case FIELD_statusCode: pp->setStatusCode(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_contentType: pp->setContentType(value.stringValue()); break;
        case FIELD_contentLength: pp->setContentLength(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_etag: pp->setEtag(value.stringValue()); break;
        case FIELD_lastModified: pp->setLastModified(value.doubleValue()); break;
        case FIELD_expires: pp->setExpires(value.doubleValue()); break;
        case FIELD_cacheControl: pp->setCacheControl(value.stringValue()); break;
        case FIELD_contentHash: pp->setContentHash(value.stringValue()); break;
        case FIELD_fromCache: pp->setFromCache(value.boolValue()); break;
        case FIELD_responseTime: pp->setResponseTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPResponse'", field);
    }
}

const char *HTTPResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr HTTPResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void HTTPResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    HTTPResponse *pp = omnetpp::fromAnyPtr<HTTPResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'HTTPResponse'", field);
    }
}

Register_Class(CacheQuery)

CacheQuery::CacheQuery(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CacheQuery::CacheQuery(const CacheQuery& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CacheQuery::~CacheQuery()
{
}

CacheQuery& CacheQuery::operator=(const CacheQuery& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CacheQuery::copy(const CacheQuery& other)
{
    this->cacheKey = other.cacheKey;
    this->url = other.url;
    this->timestamp = other.timestamp;
    this->forceRefresh = other.forceRefresh;
}

void CacheQuery::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->url);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->forceRefresh);
}

void CacheQuery::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->url);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->forceRefresh);
}

const char * CacheQuery::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void CacheQuery::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

const char * CacheQuery::getUrl() const
{
    return this->url.c_str();
}

void CacheQuery::setUrl(const char * url)
{
    this->url = url;
}

double CacheQuery::getTimestamp() const
{
    return this->timestamp;
}

void CacheQuery::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

bool CacheQuery::getForceRefresh() const
{
    return this->forceRefresh;
}

void CacheQuery::setForceRefresh(bool forceRefresh)
{
    this->forceRefresh = forceRefresh;
}

class CacheQueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_url,
        FIELD_timestamp,
        FIELD_forceRefresh,
    };
  public:
    CacheQueryDescriptor();
    virtual ~CacheQueryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CacheQueryDescriptor)

CacheQueryDescriptor::CacheQueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CacheQuery)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CacheQueryDescriptor::~CacheQueryDescriptor()
{
    delete[] propertyNames;
}

bool CacheQueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CacheQuery *>(obj)!=nullptr;
}

const char **CacheQueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CacheQueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CacheQueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int CacheQueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_url
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_forceRefresh
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *CacheQueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "url",
        "timestamp",
        "forceRefresh",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int CacheQueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "url") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "forceRefresh") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *CacheQueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "string",    // FIELD_url
        "double",    // FIELD_timestamp
        "bool",    // FIELD_forceRefresh
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **CacheQueryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CacheQueryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int CacheQueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CacheQueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CacheQuery'", field);
    }
}

const char *CacheQueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CacheQueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_url: return oppstring2string(pp->getUrl());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_forceRefresh: return bool2string(pp->getForceRefresh());
        default: return "";
    }
}

void CacheQueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_url: pp->setUrl((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_forceRefresh: pp->setForceRefresh(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheQuery'", field);
    }
}

omnetpp::cValue CacheQueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_url: return pp->getUrl();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_forceRefresh: return pp->getForceRefresh();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CacheQuery' as cValue -- field index out of range?", field);
    }
}

void CacheQueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_url: pp->setUrl(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_forceRefresh: pp->setForceRefresh(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheQuery'", field);
    }
}

const char *CacheQueryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CacheQueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CacheQueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheQuery *pp = omnetpp::fromAnyPtr<CacheQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheQuery'", field);
    }
}

Register_Class(CacheResponse)

CacheResponse::CacheResponse(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CacheResponse::CacheResponse(const CacheResponse& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CacheResponse::~CacheResponse()
{
}

CacheResponse& CacheResponse::operator=(const CacheResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CacheResponse::copy(const CacheResponse& other)
{
    this->cacheKey = other.cacheKey;
    this->hit = other.hit;
    this->contentHash = other.contentHash;
    this->ttl = other.ttl;
    this->size = other.size;
    this->timestamp = other.timestamp;
}

void CacheResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->hit);
    doParsimPacking(b,this->contentHash);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->timestamp);
}

void CacheResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->hit);
    doParsimUnpacking(b,this->contentHash);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->timestamp);
}

const char * CacheResponse::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void CacheResponse::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

bool CacheResponse::getHit() const
{
    return this->hit;
}

void CacheResponse::setHit(bool hit)
{
    this->hit = hit;
}

const char * CacheResponse::getContentHash() const
{
    return this->contentHash.c_str();
}

void CacheResponse::setContentHash(const char * contentHash)
{
    this->contentHash = contentHash;
}

double CacheResponse::getTtl() const
{
    return this->ttl;
}

void CacheResponse::setTtl(double ttl)
{
    this->ttl = ttl;
}

double CacheResponse::getSize() const
{
    return this->size;
}

void CacheResponse::setSize(double size)
{
    this->size = size;
}

double CacheResponse::getTimestamp() const
{
    return this->timestamp;
}

void CacheResponse::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class CacheResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_hit,
        FIELD_contentHash,
        FIELD_ttl,
        FIELD_size,
        FIELD_timestamp,
    };
  public:
    CacheResponseDescriptor();
    virtual ~CacheResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CacheResponseDescriptor)

CacheResponseDescriptor::CacheResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CacheResponse)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CacheResponseDescriptor::~CacheResponseDescriptor()
{
    delete[] propertyNames;
}

bool CacheResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CacheResponse *>(obj)!=nullptr;
}

const char **CacheResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CacheResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CacheResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int CacheResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_hit
        FD_ISEDITABLE,    // FIELD_contentHash
        FD_ISEDITABLE,    // FIELD_ttl
        FD_ISEDITABLE,    // FIELD_size
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *CacheResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "hit",
        "contentHash",
        "ttl",
        "size",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int CacheResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "hit") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "contentHash") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "size") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *CacheResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "bool",    // FIELD_hit
        "string",    // FIELD_contentHash
        "double",    // FIELD_ttl
        "double",    // FIELD_size
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **CacheResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ttl: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_size: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CacheResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ttl:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_size:
            if (!strcmp(propertyName, "unit")) return "bytes";
            return nullptr;
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int CacheResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CacheResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CacheResponse'", field);
    }
}

const char *CacheResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CacheResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_hit: return bool2string(pp->getHit());
        case FIELD_contentHash: return oppstring2string(pp->getContentHash());
        case FIELD_ttl: return double2string(pp->getTtl());
        case FIELD_size: return double2string(pp->getSize());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void CacheResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_hit: pp->setHit(string2bool(value)); break;
        case FIELD_contentHash: pp->setContentHash((value)); break;
        case FIELD_ttl: pp->setTtl(string2double(value)); break;
        case FIELD_size: pp->setSize(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheResponse'", field);
    }
}

omnetpp::cValue CacheResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_hit: return pp->getHit();
        case FIELD_contentHash: return pp->getContentHash();
        case FIELD_ttl: return pp->getTtl();
        case FIELD_size: return pp->getSize();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CacheResponse' as cValue -- field index out of range?", field);
    }
}

void CacheResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_hit: pp->setHit(value.boolValue()); break;
        case FIELD_contentHash: pp->setContentHash(value.stringValue()); break;
        case FIELD_ttl: pp->setTtl(value.doubleValue()); break;
        case FIELD_size: pp->setSize(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheResponse'", field);
    }
}

const char *CacheResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CacheResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CacheResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheResponse *pp = omnetpp::fromAnyPtr<CacheResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheResponse'", field);
    }
}

Register_Class(CacheStore)

CacheStore::CacheStore(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CacheStore::CacheStore(const CacheStore& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CacheStore::~CacheStore()
{
}

CacheStore& CacheStore::operator=(const CacheStore& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CacheStore::copy(const CacheStore& other)
{
    this->cacheKey = other.cacheKey;
    this->contentHash = other.contentHash;
    this->ttl = other.ttl;
    this->size = other.size;
    this->url = other.url;
    this->timestamp = other.timestamp;
    this->priority = other.priority;
}

void CacheStore::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->contentHash);
    doParsimPacking(b,this->ttl);
    doParsimPacking(b,this->size);
    doParsimPacking(b,this->url);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->priority);
}

void CacheStore::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->contentHash);
    doParsimUnpacking(b,this->ttl);
    doParsimUnpacking(b,this->size);
    doParsimUnpacking(b,this->url);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->priority);
}

const char * CacheStore::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void CacheStore::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

const char * CacheStore::getContentHash() const
{
    return this->contentHash.c_str();
}

void CacheStore::setContentHash(const char * contentHash)
{
    this->contentHash = contentHash;
}

double CacheStore::getTtl() const
{
    return this->ttl;
}

void CacheStore::setTtl(double ttl)
{
    this->ttl = ttl;
}

double CacheStore::getSize() const
{
    return this->size;
}

void CacheStore::setSize(double size)
{
    this->size = size;
}

const char * CacheStore::getUrl() const
{
    return this->url.c_str();
}

void CacheStore::setUrl(const char * url)
{
    this->url = url;
}

double CacheStore::getTimestamp() const
{
    return this->timestamp;
}

void CacheStore::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

int CacheStore::getPriority() const
{
    return this->priority;
}

void CacheStore::setPriority(int priority)
{
    this->priority = priority;
}

class CacheStoreDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_contentHash,
        FIELD_ttl,
        FIELD_size,
        FIELD_url,
        FIELD_timestamp,
        FIELD_priority,
    };
  public:
    CacheStoreDescriptor();
    virtual ~CacheStoreDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CacheStoreDescriptor)

CacheStoreDescriptor::CacheStoreDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CacheStore)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CacheStoreDescriptor::~CacheStoreDescriptor()
{
    delete[] propertyNames;
}

bool CacheStoreDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CacheStore *>(obj)!=nullptr;
}

const char **CacheStoreDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CacheStoreDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CacheStoreDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int CacheStoreDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_contentHash
        FD_ISEDITABLE,    // FIELD_ttl
        FD_ISEDITABLE,    // FIELD_size
        FD_ISEDITABLE,    // FIELD_url
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_priority
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *CacheStoreDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "contentHash",
        "ttl",
        "size",
        "url",
        "timestamp",
        "priority",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int CacheStoreDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "contentHash") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ttl") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "size") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "url") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *CacheStoreDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "string",    // FIELD_contentHash
        "double",    // FIELD_ttl
        "double",    // FIELD_size
        "string",    // FIELD_url
        "double",    // FIELD_timestamp
        "int",    // FIELD_priority
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **CacheStoreDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ttl: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_size: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CacheStoreDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_ttl:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_size:
            if (!strcmp(propertyName, "unit")) return "bytes";
            return nullptr;
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int CacheStoreDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CacheStoreDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CacheStore'", field);
    }
}

const char *CacheStoreDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CacheStoreDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_contentHash: return oppstring2string(pp->getContentHash());
        case FIELD_ttl: return double2string(pp->getTtl());
        case FIELD_size: return double2string(pp->getSize());
        case FIELD_url: return oppstring2string(pp->getUrl());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_priority: return long2string(pp->getPriority());
        default: return "";
    }
}

void CacheStoreDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_contentHash: pp->setContentHash((value)); break;
        case FIELD_ttl: pp->setTtl(string2double(value)); break;
        case FIELD_size: pp->setSize(string2double(value)); break;
        case FIELD_url: pp->setUrl((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_priority: pp->setPriority(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheStore'", field);
    }
}

omnetpp::cValue CacheStoreDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_contentHash: return pp->getContentHash();
        case FIELD_ttl: return pp->getTtl();
        case FIELD_size: return pp->getSize();
        case FIELD_url: return pp->getUrl();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_priority: return pp->getPriority();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CacheStore' as cValue -- field index out of range?", field);
    }
}

void CacheStoreDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_contentHash: pp->setContentHash(value.stringValue()); break;
        case FIELD_ttl: pp->setTtl(value.doubleValue()); break;
        case FIELD_size: pp->setSize(value.doubleValue()); break;
        case FIELD_url: pp->setUrl(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheStore'", field);
    }
}

const char *CacheStoreDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CacheStoreDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CacheStoreDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheStore *pp = omnetpp::fromAnyPtr<CacheStore>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheStore'", field);
    }
}

Register_Class(CacheEvict)

CacheEvict::CacheEvict(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CacheEvict::CacheEvict(const CacheEvict& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CacheEvict::~CacheEvict()
{
}

CacheEvict& CacheEvict::operator=(const CacheEvict& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CacheEvict::copy(const CacheEvict& other)
{
    this->cacheKey = other.cacheKey;
    this->reason = other.reason;
    this->timestamp = other.timestamp;
}

void CacheEvict::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->reason);
    doParsimPacking(b,this->timestamp);
}

void CacheEvict::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->reason);
    doParsimUnpacking(b,this->timestamp);
}

const char * CacheEvict::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void CacheEvict::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

const char * CacheEvict::getReason() const
{
    return this->reason.c_str();
}

void CacheEvict::setReason(const char * reason)
{
    this->reason = reason;
}

double CacheEvict::getTimestamp() const
{
    return this->timestamp;
}

void CacheEvict::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class CacheEvictDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_reason,
        FIELD_timestamp,
    };
  public:
    CacheEvictDescriptor();
    virtual ~CacheEvictDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CacheEvictDescriptor)

CacheEvictDescriptor::CacheEvictDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CacheEvict)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CacheEvictDescriptor::~CacheEvictDescriptor()
{
    delete[] propertyNames;
}

bool CacheEvictDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CacheEvict *>(obj)!=nullptr;
}

const char **CacheEvictDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CacheEvictDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CacheEvictDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int CacheEvictDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_reason
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *CacheEvictDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "reason",
        "timestamp",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int CacheEvictDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "reason") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *CacheEvictDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "string",    // FIELD_reason
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **CacheEvictDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *CacheEvictDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int CacheEvictDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CacheEvictDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CacheEvict'", field);
    }
}

const char *CacheEvictDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CacheEvictDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_reason: return oppstring2string(pp->getReason());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void CacheEvictDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_reason: pp->setReason((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheEvict'", field);
    }
}

omnetpp::cValue CacheEvictDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_reason: return pp->getReason();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CacheEvict' as cValue -- field index out of range?", field);
    }
}

void CacheEvictDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_reason: pp->setReason(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheEvict'", field);
    }
}

const char *CacheEvictDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CacheEvictDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CacheEvictDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CacheEvict *pp = omnetpp::fromAnyPtr<CacheEvict>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CacheEvict'", field);
    }
}

Register_Class(TTLUpdate)

TTLUpdate::TTLUpdate(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TTLUpdate::TTLUpdate(const TTLUpdate& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TTLUpdate::~TTLUpdate()
{
}

TTLUpdate& TTLUpdate::operator=(const TTLUpdate& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TTLUpdate::copy(const TTLUpdate& other)
{
    this->cacheKey = other.cacheKey;
    this->newTTL = other.newTTL;
    this->hitRate = other.hitRate;
    this->accessFrequency = other.accessFrequency;
    this->timestamp = other.timestamp;
}

void TTLUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->newTTL);
    doParsimPacking(b,this->hitRate);
    doParsimPacking(b,this->accessFrequency);
    doParsimPacking(b,this->timestamp);
}

void TTLUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->newTTL);
    doParsimUnpacking(b,this->hitRate);
    doParsimUnpacking(b,this->accessFrequency);
    doParsimUnpacking(b,this->timestamp);
}

const char * TTLUpdate::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void TTLUpdate::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

double TTLUpdate::getNewTTL() const
{
    return this->newTTL;
}

void TTLUpdate::setNewTTL(double newTTL)
{
    this->newTTL = newTTL;
}

double TTLUpdate::getHitRate() const
{
    return this->hitRate;
}

void TTLUpdate::setHitRate(double hitRate)
{
    this->hitRate = hitRate;
}

double TTLUpdate::getAccessFrequency() const
{
    return this->accessFrequency;
}

void TTLUpdate::setAccessFrequency(double accessFrequency)
{
    this->accessFrequency = accessFrequency;
}

double TTLUpdate::getTimestamp() const
{
    return this->timestamp;
}

void TTLUpdate::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class TTLUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_newTTL,
        FIELD_hitRate,
        FIELD_accessFrequency,
        FIELD_timestamp,
    };
  public:
    TTLUpdateDescriptor();
    virtual ~TTLUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TTLUpdateDescriptor)

TTLUpdateDescriptor::TTLUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TTLUpdate)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TTLUpdateDescriptor::~TTLUpdateDescriptor()
{
    delete[] propertyNames;
}

bool TTLUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TTLUpdate *>(obj)!=nullptr;
}

const char **TTLUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TTLUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TTLUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int TTLUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_newTTL
        FD_ISEDITABLE,    // FIELD_hitRate
        FD_ISEDITABLE,    // FIELD_accessFrequency
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TTLUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "newTTL",
        "hitRate",
        "accessFrequency",
        "timestamp",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TTLUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "newTTL") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hitRate") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "accessFrequency") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *TTLUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "double",    // FIELD_newTTL
        "double",    // FIELD_hitRate
        "double",    // FIELD_accessFrequency
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TTLUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_newTTL: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TTLUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_newTTL:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int TTLUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TTLUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TTLUpdate'", field);
    }
}

const char *TTLUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TTLUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_newTTL: return double2string(pp->getNewTTL());
        case FIELD_hitRate: return double2string(pp->getHitRate());
        case FIELD_accessFrequency: return double2string(pp->getAccessFrequency());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void TTLUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_newTTL: pp->setNewTTL(string2double(value)); break;
        case FIELD_hitRate: pp->setHitRate(string2double(value)); break;
        case FIELD_accessFrequency: pp->setAccessFrequency(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLUpdate'", field);
    }
}

omnetpp::cValue TTLUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_newTTL: return pp->getNewTTL();
        case FIELD_hitRate: return pp->getHitRate();
        case FIELD_accessFrequency: return pp->getAccessFrequency();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TTLUpdate' as cValue -- field index out of range?", field);
    }
}

void TTLUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_newTTL: pp->setNewTTL(value.doubleValue()); break;
        case FIELD_hitRate: pp->setHitRate(value.doubleValue()); break;
        case FIELD_accessFrequency: pp->setAccessFrequency(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLUpdate'", field);
    }
}

const char *TTLUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TTLUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TTLUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLUpdate *pp = omnetpp::fromAnyPtr<TTLUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLUpdate'", field);
    }
}

Register_Class(TTLQuery)

TTLQuery::TTLQuery(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

TTLQuery::TTLQuery(const TTLQuery& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

TTLQuery::~TTLQuery()
{
}

TTLQuery& TTLQuery::operator=(const TTLQuery& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void TTLQuery::copy(const TTLQuery& other)
{
    this->cacheKey = other.cacheKey;
    this->currentTTL = other.currentTTL;
    this->hitCount = other.hitCount;
    this->missCount = other.missCount;
    this->timestamp = other.timestamp;
}

void TTLQuery::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheKey);
    doParsimPacking(b,this->currentTTL);
    doParsimPacking(b,this->hitCount);
    doParsimPacking(b,this->missCount);
    doParsimPacking(b,this->timestamp);
}

void TTLQuery::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheKey);
    doParsimUnpacking(b,this->currentTTL);
    doParsimUnpacking(b,this->hitCount);
    doParsimUnpacking(b,this->missCount);
    doParsimUnpacking(b,this->timestamp);
}

const char * TTLQuery::getCacheKey() const
{
    return this->cacheKey.c_str();
}

void TTLQuery::setCacheKey(const char * cacheKey)
{
    this->cacheKey = cacheKey;
}

double TTLQuery::getCurrentTTL() const
{
    return this->currentTTL;
}

void TTLQuery::setCurrentTTL(double currentTTL)
{
    this->currentTTL = currentTTL;
}

double TTLQuery::getHitCount() const
{
    return this->hitCount;
}

void TTLQuery::setHitCount(double hitCount)
{
    this->hitCount = hitCount;
}

double TTLQuery::getMissCount() const
{
    return this->missCount;
}

void TTLQuery::setMissCount(double missCount)
{
    this->missCount = missCount;
}

double TTLQuery::getTimestamp() const
{
    return this->timestamp;
}

void TTLQuery::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class TTLQueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheKey,
        FIELD_currentTTL,
        FIELD_hitCount,
        FIELD_missCount,
        FIELD_timestamp,
    };
  public:
    TTLQueryDescriptor();
    virtual ~TTLQueryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(TTLQueryDescriptor)

TTLQueryDescriptor::TTLQueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(TTLQuery)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

TTLQueryDescriptor::~TTLQueryDescriptor()
{
    delete[] propertyNames;
}

bool TTLQueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<TTLQuery *>(obj)!=nullptr;
}

const char **TTLQueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *TTLQueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int TTLQueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int TTLQueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheKey
        FD_ISEDITABLE,    // FIELD_currentTTL
        FD_ISEDITABLE,    // FIELD_hitCount
        FD_ISEDITABLE,    // FIELD_missCount
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *TTLQueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheKey",
        "currentTTL",
        "hitCount",
        "missCount",
        "timestamp",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int TTLQueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "currentTTL") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hitCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "missCount") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *TTLQueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_cacheKey
        "double",    // FIELD_currentTTL
        "double",    // FIELD_hitCount
        "double",    // FIELD_missCount
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **TTLQueryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_currentTTL: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *TTLQueryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_currentTTL:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int TTLQueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void TTLQueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'TTLQuery'", field);
    }
}

const char *TTLQueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string TTLQueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return oppstring2string(pp->getCacheKey());
        case FIELD_currentTTL: return double2string(pp->getCurrentTTL());
        case FIELD_hitCount: return double2string(pp->getHitCount());
        case FIELD_missCount: return double2string(pp->getMissCount());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void TTLQueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey((value)); break;
        case FIELD_currentTTL: pp->setCurrentTTL(string2double(value)); break;
        case FIELD_hitCount: pp->setHitCount(string2double(value)); break;
        case FIELD_missCount: pp->setMissCount(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLQuery'", field);
    }
}

omnetpp::cValue TTLQueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: return pp->getCacheKey();
        case FIELD_currentTTL: return pp->getCurrentTTL();
        case FIELD_hitCount: return pp->getHitCount();
        case FIELD_missCount: return pp->getMissCount();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'TTLQuery' as cValue -- field index out of range?", field);
    }
}

void TTLQueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        case FIELD_cacheKey: pp->setCacheKey(value.stringValue()); break;
        case FIELD_currentTTL: pp->setCurrentTTL(value.doubleValue()); break;
        case FIELD_hitCount: pp->setHitCount(value.doubleValue()); break;
        case FIELD_missCount: pp->setMissCount(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLQuery'", field);
    }
}

const char *TTLQueryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr TTLQueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void TTLQueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    TTLQuery *pp = omnetpp::fromAnyPtr<TTLQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'TTLQuery'", field);
    }
}

Register_Class(RouteUpdate)

RouteUpdate::RouteUpdate(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RouteUpdate::RouteUpdate(const RouteUpdate& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RouteUpdate::~RouteUpdate()
{
}

RouteUpdate& RouteUpdate::operator=(const RouteUpdate& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RouteUpdate::copy(const RouteUpdate& other)
{
    this->destination = other.destination;
    this->nextHop = other.nextHop;
    this->hopCount = other.hopCount;
    this->cost = other.cost;
    this->timestamp = other.timestamp;
    this->isLearned_ = other.isLearned_;
}

void RouteUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->nextHop);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->cost);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->isLearned_);
}

void RouteUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->nextHop);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->cost);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->isLearned_);
}

const char * RouteUpdate::getDestination() const
{
    return this->destination.c_str();
}

void RouteUpdate::setDestination(const char * destination)
{
    this->destination = destination;
}

const char * RouteUpdate::getNextHop() const
{
    return this->nextHop.c_str();
}

void RouteUpdate::setNextHop(const char * nextHop)
{
    this->nextHop = nextHop;
}

int RouteUpdate::getHopCount() const
{
    return this->hopCount;
}

void RouteUpdate::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

double RouteUpdate::getCost() const
{
    return this->cost;
}

void RouteUpdate::setCost(double cost)
{
    this->cost = cost;
}

double RouteUpdate::getTimestamp() const
{
    return this->timestamp;
}

void RouteUpdate::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

bool RouteUpdate::isLearned() const
{
    return this->isLearned_;
}

void RouteUpdate::setIsLearned(bool isLearned)
{
    this->isLearned_ = isLearned;
}

class RouteUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destination,
        FIELD_nextHop,
        FIELD_hopCount,
        FIELD_cost,
        FIELD_timestamp,
        FIELD_isLearned,
    };
  public:
    RouteUpdateDescriptor();
    virtual ~RouteUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RouteUpdateDescriptor)

RouteUpdateDescriptor::RouteUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RouteUpdate)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RouteUpdateDescriptor::~RouteUpdateDescriptor()
{
    delete[] propertyNames;
}

bool RouteUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RouteUpdate *>(obj)!=nullptr;
}

const char **RouteUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RouteUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RouteUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int RouteUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_nextHop
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_cost
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_isLearned
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *RouteUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destination",
        "nextHop",
        "hopCount",
        "cost",
        "timestamp",
        "isLearned",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int RouteUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destination") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nextHop") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "cost") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "isLearned") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *RouteUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_destination
        "string",    // FIELD_nextHop
        "int",    // FIELD_hopCount
        "double",    // FIELD_cost
        "double",    // FIELD_timestamp
        "bool",    // FIELD_isLearned
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **RouteUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RouteUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int RouteUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RouteUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RouteUpdate'", field);
    }
}

const char *RouteUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RouteUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return oppstring2string(pp->getDestination());
        case FIELD_nextHop: return oppstring2string(pp->getNextHop());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_cost: return double2string(pp->getCost());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_isLearned: return bool2string(pp->isLearned());
        default: return "";
    }
}

void RouteUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination((value)); break;
        case FIELD_nextHop: pp->setNextHop((value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        case FIELD_cost: pp->setCost(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_isLearned: pp->setIsLearned(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteUpdate'", field);
    }
}

omnetpp::cValue RouteUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return pp->getDestination();
        case FIELD_nextHop: return pp->getNextHop();
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_cost: return pp->getCost();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_isLearned: return pp->isLearned();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RouteUpdate' as cValue -- field index out of range?", field);
    }
}

void RouteUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination(value.stringValue()); break;
        case FIELD_nextHop: pp->setNextHop(value.stringValue()); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_cost: pp->setCost(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_isLearned: pp->setIsLearned(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteUpdate'", field);
    }
}

const char *RouteUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RouteUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RouteUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteUpdate *pp = omnetpp::fromAnyPtr<RouteUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteUpdate'", field);
    }
}

Register_Class(RouteQuery)

RouteQuery::RouteQuery(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RouteQuery::RouteQuery(const RouteQuery& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RouteQuery::~RouteQuery()
{
}

RouteQuery& RouteQuery::operator=(const RouteQuery& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RouteQuery::copy(const RouteQuery& other)
{
    this->destination = other.destination;
    this->timestamp = other.timestamp;
}

void RouteQuery::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->timestamp);
}

void RouteQuery::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->timestamp);
}

const char * RouteQuery::getDestination() const
{
    return this->destination.c_str();
}

void RouteQuery::setDestination(const char * destination)
{
    this->destination = destination;
}

double RouteQuery::getTimestamp() const
{
    return this->timestamp;
}

void RouteQuery::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class RouteQueryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destination,
        FIELD_timestamp,
    };
  public:
    RouteQueryDescriptor();
    virtual ~RouteQueryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RouteQueryDescriptor)

RouteQueryDescriptor::RouteQueryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RouteQuery)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RouteQueryDescriptor::~RouteQueryDescriptor()
{
    delete[] propertyNames;
}

bool RouteQueryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RouteQuery *>(obj)!=nullptr;
}

const char **RouteQueryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RouteQueryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RouteQueryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RouteQueryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RouteQueryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destination",
        "timestamp",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RouteQueryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destination") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RouteQueryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_destination
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RouteQueryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RouteQueryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int RouteQueryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RouteQueryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RouteQuery'", field);
    }
}

const char *RouteQueryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RouteQueryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return oppstring2string(pp->getDestination());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void RouteQueryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteQuery'", field);
    }
}

omnetpp::cValue RouteQueryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return pp->getDestination();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RouteQuery' as cValue -- field index out of range?", field);
    }
}

void RouteQueryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteQuery'", field);
    }
}

const char *RouteQueryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RouteQueryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RouteQueryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteQuery *pp = omnetpp::fromAnyPtr<RouteQuery>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteQuery'", field);
    }
}

Register_Class(RouteResponse)

RouteResponse::RouteResponse(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

RouteResponse::RouteResponse(const RouteResponse& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

RouteResponse::~RouteResponse()
{
}

RouteResponse& RouteResponse::operator=(const RouteResponse& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void RouteResponse::copy(const RouteResponse& other)
{
    this->destination = other.destination;
    this->nextHop = other.nextHop;
    this->hopCount = other.hopCount;
    this->cost = other.cost;
    this->found = other.found;
    this->timestamp = other.timestamp;
}

void RouteResponse::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->nextHop);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->cost);
    doParsimPacking(b,this->found);
    doParsimPacking(b,this->timestamp);
}

void RouteResponse::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->nextHop);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->cost);
    doParsimUnpacking(b,this->found);
    doParsimUnpacking(b,this->timestamp);
}

const char * RouteResponse::getDestination() const
{
    return this->destination.c_str();
}

void RouteResponse::setDestination(const char * destination)
{
    this->destination = destination;
}

const char * RouteResponse::getNextHop() const
{
    return this->nextHop.c_str();
}

void RouteResponse::setNextHop(const char * nextHop)
{
    this->nextHop = nextHop;
}

int RouteResponse::getHopCount() const
{
    return this->hopCount;
}

void RouteResponse::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

double RouteResponse::getCost() const
{
    return this->cost;
}

void RouteResponse::setCost(double cost)
{
    this->cost = cost;
}

bool RouteResponse::getFound() const
{
    return this->found;
}

void RouteResponse::setFound(bool found)
{
    this->found = found;
}

double RouteResponse::getTimestamp() const
{
    return this->timestamp;
}

void RouteResponse::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class RouteResponseDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destination,
        FIELD_nextHop,
        FIELD_hopCount,
        FIELD_cost,
        FIELD_found,
        FIELD_timestamp,
    };
  public:
    RouteResponseDescriptor();
    virtual ~RouteResponseDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RouteResponseDescriptor)

RouteResponseDescriptor::RouteResponseDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RouteResponse)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

RouteResponseDescriptor::~RouteResponseDescriptor()
{
    delete[] propertyNames;
}

bool RouteResponseDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RouteResponse *>(obj)!=nullptr;
}

const char **RouteResponseDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RouteResponseDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RouteResponseDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int RouteResponseDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_nextHop
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_cost
        FD_ISEDITABLE,    // FIELD_found
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *RouteResponseDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destination",
        "nextHop",
        "hopCount",
        "cost",
        "found",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int RouteResponseDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destination") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "nextHop") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "cost") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "found") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *RouteResponseDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_destination
        "string",    // FIELD_nextHop
        "int",    // FIELD_hopCount
        "double",    // FIELD_cost
        "bool",    // FIELD_found
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **RouteResponseDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *RouteResponseDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int RouteResponseDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RouteResponseDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RouteResponse'", field);
    }
}

const char *RouteResponseDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RouteResponseDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return oppstring2string(pp->getDestination());
        case FIELD_nextHop: return oppstring2string(pp->getNextHop());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_cost: return double2string(pp->getCost());
        case FIELD_found: return bool2string(pp->getFound());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void RouteResponseDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination((value)); break;
        case FIELD_nextHop: pp->setNextHop((value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        case FIELD_cost: pp->setCost(string2double(value)); break;
        case FIELD_found: pp->setFound(string2bool(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteResponse'", field);
    }
}

omnetpp::cValue RouteResponseDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return pp->getDestination();
        case FIELD_nextHop: return pp->getNextHop();
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_cost: return pp->getCost();
        case FIELD_found: return pp->getFound();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RouteResponse' as cValue -- field index out of range?", field);
    }
}

void RouteResponseDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination(value.stringValue()); break;
        case FIELD_nextHop: pp->setNextHop(value.stringValue()); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_cost: pp->setCost(value.doubleValue()); break;
        case FIELD_found: pp->setFound(value.boolValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteResponse'", field);
    }
}

const char *RouteResponseDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RouteResponseDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RouteResponseDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RouteResponse *pp = omnetpp::fromAnyPtr<RouteResponse>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RouteResponse'", field);
    }
}

Register_Class(PoisonAttempt)

PoisonAttempt::PoisonAttempt(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

PoisonAttempt::PoisonAttempt(const PoisonAttempt& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PoisonAttempt::~PoisonAttempt()
{
}

PoisonAttempt& PoisonAttempt::operator=(const PoisonAttempt& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PoisonAttempt::copy(const PoisonAttempt& other)
{
    this->targetCacheKey = other.targetCacheKey;
    this->maliciousContent = other.maliciousContent;
    this->attackerId = other.attackerId;
    this->timestamp = other.timestamp;
    this->successRate = other.successRate;
}

void PoisonAttempt::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->targetCacheKey);
    doParsimPacking(b,this->maliciousContent);
    doParsimPacking(b,this->attackerId);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->successRate);
}

void PoisonAttempt::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->targetCacheKey);
    doParsimUnpacking(b,this->maliciousContent);
    doParsimUnpacking(b,this->attackerId);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->successRate);
}

const char * PoisonAttempt::getTargetCacheKey() const
{
    return this->targetCacheKey.c_str();
}

void PoisonAttempt::setTargetCacheKey(const char * targetCacheKey)
{
    this->targetCacheKey = targetCacheKey;
}

const char * PoisonAttempt::getMaliciousContent() const
{
    return this->maliciousContent.c_str();
}

void PoisonAttempt::setMaliciousContent(const char * maliciousContent)
{
    this->maliciousContent = maliciousContent;
}

const char * PoisonAttempt::getAttackerId() const
{
    return this->attackerId.c_str();
}

void PoisonAttempt::setAttackerId(const char * attackerId)
{
    this->attackerId = attackerId;
}

double PoisonAttempt::getTimestamp() const
{
    return this->timestamp;
}

void PoisonAttempt::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

double PoisonAttempt::getSuccessRate() const
{
    return this->successRate;
}

void PoisonAttempt::setSuccessRate(double successRate)
{
    this->successRate = successRate;
}

class PoisonAttemptDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_targetCacheKey,
        FIELD_maliciousContent,
        FIELD_attackerId,
        FIELD_timestamp,
        FIELD_successRate,
    };
  public:
    PoisonAttemptDescriptor();
    virtual ~PoisonAttemptDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PoisonAttemptDescriptor)

PoisonAttemptDescriptor::PoisonAttemptDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PoisonAttempt)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

PoisonAttemptDescriptor::~PoisonAttemptDescriptor()
{
    delete[] propertyNames;
}

bool PoisonAttemptDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PoisonAttempt *>(obj)!=nullptr;
}

const char **PoisonAttemptDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PoisonAttemptDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PoisonAttemptDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int PoisonAttemptDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_targetCacheKey
        FD_ISEDITABLE,    // FIELD_maliciousContent
        FD_ISEDITABLE,    // FIELD_attackerId
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_successRate
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *PoisonAttemptDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "targetCacheKey",
        "maliciousContent",
        "attackerId",
        "timestamp",
        "successRate",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int PoisonAttemptDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "targetCacheKey") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "maliciousContent") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "attackerId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "successRate") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *PoisonAttemptDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_targetCacheKey
        "string",    // FIELD_maliciousContent
        "string",    // FIELD_attackerId
        "double",    // FIELD_timestamp
        "double",    // FIELD_successRate
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **PoisonAttemptDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PoisonAttemptDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int PoisonAttemptDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PoisonAttemptDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PoisonAttempt'", field);
    }
}

const char *PoisonAttemptDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PoisonAttemptDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        case FIELD_targetCacheKey: return oppstring2string(pp->getTargetCacheKey());
        case FIELD_maliciousContent: return oppstring2string(pp->getMaliciousContent());
        case FIELD_attackerId: return oppstring2string(pp->getAttackerId());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_successRate: return double2string(pp->getSuccessRate());
        default: return "";
    }
}

void PoisonAttemptDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        case FIELD_targetCacheKey: pp->setTargetCacheKey((value)); break;
        case FIELD_maliciousContent: pp->setMaliciousContent((value)); break;
        case FIELD_attackerId: pp->setAttackerId((value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_successRate: pp->setSuccessRate(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoisonAttempt'", field);
    }
}

omnetpp::cValue PoisonAttemptDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        case FIELD_targetCacheKey: return pp->getTargetCacheKey();
        case FIELD_maliciousContent: return pp->getMaliciousContent();
        case FIELD_attackerId: return pp->getAttackerId();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_successRate: return pp->getSuccessRate();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PoisonAttempt' as cValue -- field index out of range?", field);
    }
}

void PoisonAttemptDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        case FIELD_targetCacheKey: pp->setTargetCacheKey(value.stringValue()); break;
        case FIELD_maliciousContent: pp->setMaliciousContent(value.stringValue()); break;
        case FIELD_attackerId: pp->setAttackerId(value.stringValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_successRate: pp->setSuccessRate(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoisonAttempt'", field);
    }
}

const char *PoisonAttemptDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PoisonAttemptDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PoisonAttemptDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PoisonAttempt *pp = omnetpp::fromAnyPtr<PoisonAttempt>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PoisonAttempt'", field);
    }
}

Register_Class(SecurityAlert)

SecurityAlert::SecurityAlert(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SecurityAlert::SecurityAlert(const SecurityAlert& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SecurityAlert::~SecurityAlert()
{
}

SecurityAlert& SecurityAlert::operator=(const SecurityAlert& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SecurityAlert::copy(const SecurityAlert& other)
{
    this->alertType = other.alertType;
    this->source = other.source;
    this->target = other.target;
    this->severity = other.severity;
    this->timestamp = other.timestamp;
    this->description = other.description;
}

void SecurityAlert::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->alertType);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->target);
    doParsimPacking(b,this->severity);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->description);
}

void SecurityAlert::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->alertType);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->target);
    doParsimUnpacking(b,this->severity);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->description);
}

const char * SecurityAlert::getAlertType() const
{
    return this->alertType.c_str();
}

void SecurityAlert::setAlertType(const char * alertType)
{
    this->alertType = alertType;
}

const char * SecurityAlert::getSource() const
{
    return this->source.c_str();
}

void SecurityAlert::setSource(const char * source)
{
    this->source = source;
}

const char * SecurityAlert::getTarget() const
{
    return this->target.c_str();
}

void SecurityAlert::setTarget(const char * target)
{
    this->target = target;
}

double SecurityAlert::getSeverity() const
{
    return this->severity;
}

void SecurityAlert::setSeverity(double severity)
{
    this->severity = severity;
}

double SecurityAlert::getTimestamp() const
{
    return this->timestamp;
}

void SecurityAlert::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

const char * SecurityAlert::getDescription() const
{
    return this->description.c_str();
}

void SecurityAlert::setDescription(const char * description)
{
    this->description = description;
}

class SecurityAlertDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_alertType,
        FIELD_source,
        FIELD_target,
        FIELD_severity,
        FIELD_timestamp,
        FIELD_description,
    };
  public:
    SecurityAlertDescriptor();
    virtual ~SecurityAlertDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SecurityAlertDescriptor)

SecurityAlertDescriptor::SecurityAlertDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SecurityAlert)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SecurityAlertDescriptor::~SecurityAlertDescriptor()
{
    delete[] propertyNames;
}

bool SecurityAlertDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SecurityAlert *>(obj)!=nullptr;
}

const char **SecurityAlertDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SecurityAlertDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SecurityAlertDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int SecurityAlertDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_alertType
        FD_ISEDITABLE,    // FIELD_source
        FD_ISEDITABLE,    // FIELD_target
        FD_ISEDITABLE,    // FIELD_severity
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_description
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *SecurityAlertDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "alertType",
        "source",
        "target",
        "severity",
        "timestamp",
        "description",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int SecurityAlertDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "alertType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "source") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "target") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "severity") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "description") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *SecurityAlertDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_alertType
        "string",    // FIELD_source
        "string",    // FIELD_target
        "double",    // FIELD_severity
        "double",    // FIELD_timestamp
        "string",    // FIELD_description
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **SecurityAlertDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *SecurityAlertDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int SecurityAlertDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SecurityAlertDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SecurityAlert'", field);
    }
}

const char *SecurityAlertDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SecurityAlertDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        case FIELD_alertType: return oppstring2string(pp->getAlertType());
        case FIELD_source: return oppstring2string(pp->getSource());
        case FIELD_target: return oppstring2string(pp->getTarget());
        case FIELD_severity: return double2string(pp->getSeverity());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_description: return oppstring2string(pp->getDescription());
        default: return "";
    }
}

void SecurityAlertDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        case FIELD_alertType: pp->setAlertType((value)); break;
        case FIELD_source: pp->setSource((value)); break;
        case FIELD_target: pp->setTarget((value)); break;
        case FIELD_severity: pp->setSeverity(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_description: pp->setDescription((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecurityAlert'", field);
    }
}

omnetpp::cValue SecurityAlertDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        case FIELD_alertType: return pp->getAlertType();
        case FIELD_source: return pp->getSource();
        case FIELD_target: return pp->getTarget();
        case FIELD_severity: return pp->getSeverity();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_description: return pp->getDescription();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SecurityAlert' as cValue -- field index out of range?", field);
    }
}

void SecurityAlertDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        case FIELD_alertType: pp->setAlertType(value.stringValue()); break;
        case FIELD_source: pp->setSource(value.stringValue()); break;
        case FIELD_target: pp->setTarget(value.stringValue()); break;
        case FIELD_severity: pp->setSeverity(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_description: pp->setDescription(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecurityAlert'", field);
    }
}

const char *SecurityAlertDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SecurityAlertDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SecurityAlertDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SecurityAlert *pp = omnetpp::fromAnyPtr<SecurityAlert>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecurityAlert'", field);
    }
}

Register_Class(ThreatDetection)

ThreatDetection::ThreatDetection(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ThreatDetection::ThreatDetection(const ThreatDetection& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ThreatDetection::~ThreatDetection()
{
}

ThreatDetection& ThreatDetection::operator=(const ThreatDetection& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ThreatDetection::copy(const ThreatDetection& other)
{
    this->threatType = other.threatType;
    this->sourceIP = other.sourceIP;
    this->targetIP = other.targetIP;
    this->confidence = other.confidence;
    this->timestamp = other.timestamp;
    this->mitigation = other.mitigation;
}

void ThreatDetection::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->threatType);
    doParsimPacking(b,this->sourceIP);
    doParsimPacking(b,this->targetIP);
    doParsimPacking(b,this->confidence);
    doParsimPacking(b,this->timestamp);
    doParsimPacking(b,this->mitigation);
}

void ThreatDetection::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->threatType);
    doParsimUnpacking(b,this->sourceIP);
    doParsimUnpacking(b,this->targetIP);
    doParsimUnpacking(b,this->confidence);
    doParsimUnpacking(b,this->timestamp);
    doParsimUnpacking(b,this->mitigation);
}

const char * ThreatDetection::getThreatType() const
{
    return this->threatType.c_str();
}

void ThreatDetection::setThreatType(const char * threatType)
{
    this->threatType = threatType;
}

const char * ThreatDetection::getSourceIP() const
{
    return this->sourceIP.c_str();
}

void ThreatDetection::setSourceIP(const char * sourceIP)
{
    this->sourceIP = sourceIP;
}

const char * ThreatDetection::getTargetIP() const
{
    return this->targetIP.c_str();
}

void ThreatDetection::setTargetIP(const char * targetIP)
{
    this->targetIP = targetIP;
}

double ThreatDetection::getConfidence() const
{
    return this->confidence;
}

void ThreatDetection::setConfidence(double confidence)
{
    this->confidence = confidence;
}

double ThreatDetection::getTimestamp() const
{
    return this->timestamp;
}

void ThreatDetection::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

const char * ThreatDetection::getMitigation() const
{
    return this->mitigation.c_str();
}

void ThreatDetection::setMitigation(const char * mitigation)
{
    this->mitigation = mitigation;
}

class ThreatDetectionDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_threatType,
        FIELD_sourceIP,
        FIELD_targetIP,
        FIELD_confidence,
        FIELD_timestamp,
        FIELD_mitigation,
    };
  public:
    ThreatDetectionDescriptor();
    virtual ~ThreatDetectionDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ThreatDetectionDescriptor)

ThreatDetectionDescriptor::ThreatDetectionDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ThreatDetection)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ThreatDetectionDescriptor::~ThreatDetectionDescriptor()
{
    delete[] propertyNames;
}

bool ThreatDetectionDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ThreatDetection *>(obj)!=nullptr;
}

const char **ThreatDetectionDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ThreatDetectionDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ThreatDetectionDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int ThreatDetectionDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_threatType
        FD_ISEDITABLE,    // FIELD_sourceIP
        FD_ISEDITABLE,    // FIELD_targetIP
        FD_ISEDITABLE,    // FIELD_confidence
        FD_ISEDITABLE,    // FIELD_timestamp
        FD_ISEDITABLE,    // FIELD_mitigation
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *ThreatDetectionDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "threatType",
        "sourceIP",
        "targetIP",
        "confidence",
        "timestamp",
        "mitigation",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int ThreatDetectionDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "threatType") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sourceIP") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "targetIP") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "confidence") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "mitigation") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *ThreatDetectionDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_threatType
        "string",    // FIELD_sourceIP
        "string",    // FIELD_targetIP
        "double",    // FIELD_confidence
        "double",    // FIELD_timestamp
        "string",    // FIELD_mitigation
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **ThreatDetectionDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *ThreatDetectionDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int ThreatDetectionDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ThreatDetectionDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ThreatDetection'", field);
    }
}

const char *ThreatDetectionDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ThreatDetectionDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        case FIELD_threatType: return oppstring2string(pp->getThreatType());
        case FIELD_sourceIP: return oppstring2string(pp->getSourceIP());
        case FIELD_targetIP: return oppstring2string(pp->getTargetIP());
        case FIELD_confidence: return double2string(pp->getConfidence());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        case FIELD_mitigation: return oppstring2string(pp->getMitigation());
        default: return "";
    }
}

void ThreatDetectionDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        case FIELD_threatType: pp->setThreatType((value)); break;
        case FIELD_sourceIP: pp->setSourceIP((value)); break;
        case FIELD_targetIP: pp->setTargetIP((value)); break;
        case FIELD_confidence: pp->setConfidence(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        case FIELD_mitigation: pp->setMitigation((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ThreatDetection'", field);
    }
}

omnetpp::cValue ThreatDetectionDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        case FIELD_threatType: return pp->getThreatType();
        case FIELD_sourceIP: return pp->getSourceIP();
        case FIELD_targetIP: return pp->getTargetIP();
        case FIELD_confidence: return pp->getConfidence();
        case FIELD_timestamp: return pp->getTimestamp();
        case FIELD_mitigation: return pp->getMitigation();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ThreatDetection' as cValue -- field index out of range?", field);
    }
}

void ThreatDetectionDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        case FIELD_threatType: pp->setThreatType(value.stringValue()); break;
        case FIELD_sourceIP: pp->setSourceIP(value.stringValue()); break;
        case FIELD_targetIP: pp->setTargetIP(value.stringValue()); break;
        case FIELD_confidence: pp->setConfidence(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        case FIELD_mitigation: pp->setMitigation(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ThreatDetection'", field);
    }
}

const char *ThreatDetectionDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ThreatDetectionDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ThreatDetectionDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ThreatDetection *pp = omnetpp::fromAnyPtr<ThreatDetection>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ThreatDetection'", field);
    }
}

Register_Class(NetworkStats)

NetworkStats::NetworkStats(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

NetworkStats::NetworkStats(const NetworkStats& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

NetworkStats::~NetworkStats()
{
}

NetworkStats& NetworkStats::operator=(const NetworkStats& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void NetworkStats::copy(const NetworkStats& other)
{
    this->cacheHitRate = other.cacheHitRate;
    this->averageLatency = other.averageLatency;
    this->throughput = other.throughput;
    this->activeConnections = other.activeConnections;
    this->dhcpSuccessRate = other.dhcpSuccessRate;
    this->securityThreats = other.securityThreats;
    this->timestamp = other.timestamp;
}

void NetworkStats::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->cacheHitRate);
    doParsimPacking(b,this->averageLatency);
    doParsimPacking(b,this->throughput);
    doParsimPacking(b,this->activeConnections);
    doParsimPacking(b,this->dhcpSuccessRate);
    doParsimPacking(b,this->securityThreats);
    doParsimPacking(b,this->timestamp);
}

void NetworkStats::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->cacheHitRate);
    doParsimUnpacking(b,this->averageLatency);
    doParsimUnpacking(b,this->throughput);
    doParsimUnpacking(b,this->activeConnections);
    doParsimUnpacking(b,this->dhcpSuccessRate);
    doParsimUnpacking(b,this->securityThreats);
    doParsimUnpacking(b,this->timestamp);
}

double NetworkStats::getCacheHitRate() const
{
    return this->cacheHitRate;
}

void NetworkStats::setCacheHitRate(double cacheHitRate)
{
    this->cacheHitRate = cacheHitRate;
}

double NetworkStats::getAverageLatency() const
{
    return this->averageLatency;
}

void NetworkStats::setAverageLatency(double averageLatency)
{
    this->averageLatency = averageLatency;
}

double NetworkStats::getThroughput() const
{
    return this->throughput;
}

void NetworkStats::setThroughput(double throughput)
{
    this->throughput = throughput;
}

int NetworkStats::getActiveConnections() const
{
    return this->activeConnections;
}

void NetworkStats::setActiveConnections(int activeConnections)
{
    this->activeConnections = activeConnections;
}

double NetworkStats::getDhcpSuccessRate() const
{
    return this->dhcpSuccessRate;
}

void NetworkStats::setDhcpSuccessRate(double dhcpSuccessRate)
{
    this->dhcpSuccessRate = dhcpSuccessRate;
}

double NetworkStats::getSecurityThreats() const
{
    return this->securityThreats;
}

void NetworkStats::setSecurityThreats(double securityThreats)
{
    this->securityThreats = securityThreats;
}

double NetworkStats::getTimestamp() const
{
    return this->timestamp;
}

void NetworkStats::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class NetworkStatsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_cacheHitRate,
        FIELD_averageLatency,
        FIELD_throughput,
        FIELD_activeConnections,
        FIELD_dhcpSuccessRate,
        FIELD_securityThreats,
        FIELD_timestamp,
    };
  public:
    NetworkStatsDescriptor();
    virtual ~NetworkStatsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(NetworkStatsDescriptor)

NetworkStatsDescriptor::NetworkStatsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(NetworkStats)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

NetworkStatsDescriptor::~NetworkStatsDescriptor()
{
    delete[] propertyNames;
}

bool NetworkStatsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<NetworkStats *>(obj)!=nullptr;
}

const char **NetworkStatsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *NetworkStatsDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int NetworkStatsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int NetworkStatsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_cacheHitRate
        FD_ISEDITABLE,    // FIELD_averageLatency
        FD_ISEDITABLE,    // FIELD_throughput
        FD_ISEDITABLE,    // FIELD_activeConnections
        FD_ISEDITABLE,    // FIELD_dhcpSuccessRate
        FD_ISEDITABLE,    // FIELD_securityThreats
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *NetworkStatsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "cacheHitRate",
        "averageLatency",
        "throughput",
        "activeConnections",
        "dhcpSuccessRate",
        "securityThreats",
        "timestamp",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int NetworkStatsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "cacheHitRate") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "averageLatency") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "throughput") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "activeConnections") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "dhcpSuccessRate") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "securityThreats") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *NetworkStatsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "double",    // FIELD_cacheHitRate
        "double",    // FIELD_averageLatency
        "double",    // FIELD_throughput
        "int",    // FIELD_activeConnections
        "double",    // FIELD_dhcpSuccessRate
        "double",    // FIELD_securityThreats
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **NetworkStatsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_averageLatency: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_throughput: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *NetworkStatsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_averageLatency:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        case FIELD_throughput:
            if (!strcmp(propertyName, "unit")) return "bps";
            return nullptr;
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int NetworkStatsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void NetworkStatsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'NetworkStats'", field);
    }
}

const char *NetworkStatsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string NetworkStatsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        case FIELD_cacheHitRate: return double2string(pp->getCacheHitRate());
        case FIELD_averageLatency: return double2string(pp->getAverageLatency());
        case FIELD_throughput: return double2string(pp->getThroughput());
        case FIELD_activeConnections: return long2string(pp->getActiveConnections());
        case FIELD_dhcpSuccessRate: return double2string(pp->getDhcpSuccessRate());
        case FIELD_securityThreats: return double2string(pp->getSecurityThreats());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void NetworkStatsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        case FIELD_cacheHitRate: pp->setCacheHitRate(string2double(value)); break;
        case FIELD_averageLatency: pp->setAverageLatency(string2double(value)); break;
        case FIELD_throughput: pp->setThroughput(string2double(value)); break;
        case FIELD_activeConnections: pp->setActiveConnections(string2long(value)); break;
        case FIELD_dhcpSuccessRate: pp->setDhcpSuccessRate(string2double(value)); break;
        case FIELD_securityThreats: pp->setSecurityThreats(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkStats'", field);
    }
}

omnetpp::cValue NetworkStatsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        case FIELD_cacheHitRate: return pp->getCacheHitRate();
        case FIELD_averageLatency: return pp->getAverageLatency();
        case FIELD_throughput: return pp->getThroughput();
        case FIELD_activeConnections: return pp->getActiveConnections();
        case FIELD_dhcpSuccessRate: return pp->getDhcpSuccessRate();
        case FIELD_securityThreats: return pp->getSecurityThreats();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'NetworkStats' as cValue -- field index out of range?", field);
    }
}

void NetworkStatsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        case FIELD_cacheHitRate: pp->setCacheHitRate(value.doubleValue()); break;
        case FIELD_averageLatency: pp->setAverageLatency(value.doubleValue()); break;
        case FIELD_throughput: pp->setThroughput(value.doubleValue()); break;
        case FIELD_activeConnections: pp->setActiveConnections(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dhcpSuccessRate: pp->setDhcpSuccessRate(value.doubleValue()); break;
        case FIELD_securityThreats: pp->setSecurityThreats(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkStats'", field);
    }
}

const char *NetworkStatsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr NetworkStatsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void NetworkStatsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    NetworkStats *pp = omnetpp::fromAnyPtr<NetworkStats>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'NetworkStats'", field);
    }
}

Register_Class(PerformanceMetrics)

PerformanceMetrics::PerformanceMetrics(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

PerformanceMetrics::PerformanceMetrics(const PerformanceMetrics& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

PerformanceMetrics::~PerformanceMetrics()
{
}

PerformanceMetrics& PerformanceMetrics::operator=(const PerformanceMetrics& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void PerformanceMetrics::copy(const PerformanceMetrics& other)
{
    this->componentId = other.componentId;
    this->cpuUsage = other.cpuUsage;
    this->memoryUsage = other.memoryUsage;
    this->diskUsage = other.diskUsage;
    this->networkUsage = other.networkUsage;
    this->timestamp = other.timestamp;
}

void PerformanceMetrics::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->componentId);
    doParsimPacking(b,this->cpuUsage);
    doParsimPacking(b,this->memoryUsage);
    doParsimPacking(b,this->diskUsage);
    doParsimPacking(b,this->networkUsage);
    doParsimPacking(b,this->timestamp);
}

void PerformanceMetrics::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->componentId);
    doParsimUnpacking(b,this->cpuUsage);
    doParsimUnpacking(b,this->memoryUsage);
    doParsimUnpacking(b,this->diskUsage);
    doParsimUnpacking(b,this->networkUsage);
    doParsimUnpacking(b,this->timestamp);
}

const char * PerformanceMetrics::getComponentId() const
{
    return this->componentId.c_str();
}

void PerformanceMetrics::setComponentId(const char * componentId)
{
    this->componentId = componentId;
}

double PerformanceMetrics::getCpuUsage() const
{
    return this->cpuUsage;
}

void PerformanceMetrics::setCpuUsage(double cpuUsage)
{
    this->cpuUsage = cpuUsage;
}

double PerformanceMetrics::getMemoryUsage() const
{
    return this->memoryUsage;
}

void PerformanceMetrics::setMemoryUsage(double memoryUsage)
{
    this->memoryUsage = memoryUsage;
}

double PerformanceMetrics::getDiskUsage() const
{
    return this->diskUsage;
}

void PerformanceMetrics::setDiskUsage(double diskUsage)
{
    this->diskUsage = diskUsage;
}

double PerformanceMetrics::getNetworkUsage() const
{
    return this->networkUsage;
}

void PerformanceMetrics::setNetworkUsage(double networkUsage)
{
    this->networkUsage = networkUsage;
}

double PerformanceMetrics::getTimestamp() const
{
    return this->timestamp;
}

void PerformanceMetrics::setTimestamp(double timestamp)
{
    this->timestamp = timestamp;
}

class PerformanceMetricsDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_componentId,
        FIELD_cpuUsage,
        FIELD_memoryUsage,
        FIELD_diskUsage,
        FIELD_networkUsage,
        FIELD_timestamp,
    };
  public:
    PerformanceMetricsDescriptor();
    virtual ~PerformanceMetricsDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PerformanceMetricsDescriptor)

PerformanceMetricsDescriptor::PerformanceMetricsDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PerformanceMetrics)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

PerformanceMetricsDescriptor::~PerformanceMetricsDescriptor()
{
    delete[] propertyNames;
}

bool PerformanceMetricsDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PerformanceMetrics *>(obj)!=nullptr;
}

const char **PerformanceMetricsDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PerformanceMetricsDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PerformanceMetricsDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int PerformanceMetricsDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_componentId
        FD_ISEDITABLE,    // FIELD_cpuUsage
        FD_ISEDITABLE,    // FIELD_memoryUsage
        FD_ISEDITABLE,    // FIELD_diskUsage
        FD_ISEDITABLE,    // FIELD_networkUsage
        FD_ISEDITABLE,    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *PerformanceMetricsDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "componentId",
        "cpuUsage",
        "memoryUsage",
        "diskUsage",
        "networkUsage",
        "timestamp",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int PerformanceMetricsDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "componentId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "cpuUsage") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "memoryUsage") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "diskUsage") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "networkUsage") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "timestamp") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *PerformanceMetricsDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_componentId
        "double",    // FIELD_cpuUsage
        "double",    // FIELD_memoryUsage
        "double",    // FIELD_diskUsage
        "double",    // FIELD_networkUsage
        "double",    // FIELD_timestamp
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **PerformanceMetricsDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp: {
            static const char *names[] = { "unit",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *PerformanceMetricsDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_timestamp:
            if (!strcmp(propertyName, "unit")) return "s";
            return nullptr;
        default: return nullptr;
    }
}

int PerformanceMetricsDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PerformanceMetricsDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PerformanceMetrics'", field);
    }
}

const char *PerformanceMetricsDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PerformanceMetricsDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        case FIELD_componentId: return oppstring2string(pp->getComponentId());
        case FIELD_cpuUsage: return double2string(pp->getCpuUsage());
        case FIELD_memoryUsage: return double2string(pp->getMemoryUsage());
        case FIELD_diskUsage: return double2string(pp->getDiskUsage());
        case FIELD_networkUsage: return double2string(pp->getNetworkUsage());
        case FIELD_timestamp: return double2string(pp->getTimestamp());
        default: return "";
    }
}

void PerformanceMetricsDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        case FIELD_componentId: pp->setComponentId((value)); break;
        case FIELD_cpuUsage: pp->setCpuUsage(string2double(value)); break;
        case FIELD_memoryUsage: pp->setMemoryUsage(string2double(value)); break;
        case FIELD_diskUsage: pp->setDiskUsage(string2double(value)); break;
        case FIELD_networkUsage: pp->setNetworkUsage(string2double(value)); break;
        case FIELD_timestamp: pp->setTimestamp(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PerformanceMetrics'", field);
    }
}

omnetpp::cValue PerformanceMetricsDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        case FIELD_componentId: return pp->getComponentId();
        case FIELD_cpuUsage: return pp->getCpuUsage();
        case FIELD_memoryUsage: return pp->getMemoryUsage();
        case FIELD_diskUsage: return pp->getDiskUsage();
        case FIELD_networkUsage: return pp->getNetworkUsage();
        case FIELD_timestamp: return pp->getTimestamp();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PerformanceMetrics' as cValue -- field index out of range?", field);
    }
}

void PerformanceMetricsDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        case FIELD_componentId: pp->setComponentId(value.stringValue()); break;
        case FIELD_cpuUsage: pp->setCpuUsage(value.doubleValue()); break;
        case FIELD_memoryUsage: pp->setMemoryUsage(value.doubleValue()); break;
        case FIELD_diskUsage: pp->setDiskUsage(value.doubleValue()); break;
        case FIELD_networkUsage: pp->setNetworkUsage(value.doubleValue()); break;
        case FIELD_timestamp: pp->setTimestamp(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PerformanceMetrics'", field);
    }
}

const char *PerformanceMetricsDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PerformanceMetricsDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PerformanceMetricsDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PerformanceMetrics *pp = omnetpp::fromAnyPtr<PerformanceMetrics>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PerformanceMetrics'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

