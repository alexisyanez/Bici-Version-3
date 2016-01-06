//
// Generated file, do not edit! Created by opp_msgc 4.4 from src/modules/messages/CustomApplPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CustomApplPkt_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(CustomApplPkt);

CustomApplPkt::CustomApplPkt(const char *name, int kind) : ::cPacket(name,kind)
{
    this->destAddr_var = LAddress::L3BROADCAST;
    this->srcAddr_var = LAddress::L3BROADCAST;
    this->xposition_var = 0;
    this->yposition_var = 0;
    this->speed_var = 0;
    this->id_var = 0;
    this->acceleration_var = 0;
    this->leaderAcceleration_var = 0;
    this->leaderSpeed_var = 0;
    this->beaconingEnabled_var = 0;
}

CustomApplPkt::CustomApplPkt(const CustomApplPkt& other) : ::cPacket(other)
{
    copy(other);
}

CustomApplPkt::~CustomApplPkt()
{
}

CustomApplPkt& CustomApplPkt::operator=(const CustomApplPkt& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void CustomApplPkt::copy(const CustomApplPkt& other)
{
    this->destAddr_var = other.destAddr_var;
    this->srcAddr_var = other.srcAddr_var;
    this->xposition_var = other.xposition_var;
    this->yposition_var = other.yposition_var;
    this->speed_var = other.speed_var;
    this->id_var = other.id_var;
    this->acceleration_var = other.acceleration_var;
    this->leaderAcceleration_var = other.leaderAcceleration_var;
    this->leaderSpeed_var = other.leaderSpeed_var;
    this->beaconingEnabled_var = other.beaconingEnabled_var;
}

void CustomApplPkt::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->destAddr_var);
    doPacking(b,this->srcAddr_var);
    doPacking(b,this->xposition_var);
    doPacking(b,this->yposition_var);
    doPacking(b,this->speed_var);
    doPacking(b,this->id_var);
    doPacking(b,this->acceleration_var);
    doPacking(b,this->leaderAcceleration_var);
    doPacking(b,this->leaderSpeed_var);
    doPacking(b,this->beaconingEnabled_var);
}

void CustomApplPkt::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->destAddr_var);
    doUnpacking(b,this->srcAddr_var);
    doUnpacking(b,this->xposition_var);
    doUnpacking(b,this->yposition_var);
    doUnpacking(b,this->speed_var);
    doUnpacking(b,this->id_var);
    doUnpacking(b,this->acceleration_var);
    doUnpacking(b,this->leaderAcceleration_var);
    doUnpacking(b,this->leaderSpeed_var);
    doUnpacking(b,this->beaconingEnabled_var);
}

LAddress::L3Type& CustomApplPkt::getDestAddr()
{
    return destAddr_var;
}

void CustomApplPkt::setDestAddr(const LAddress::L3Type& destAddr)
{
    this->destAddr_var = destAddr;
}

LAddress::L3Type& CustomApplPkt::getSrcAddr()
{
    return srcAddr_var;
}

void CustomApplPkt::setSrcAddr(const LAddress::L3Type& srcAddr)
{
    this->srcAddr_var = srcAddr;
}

double CustomApplPkt::getXposition() const
{
    return xposition_var;
}

void CustomApplPkt::setXposition(double xposition)
{
    this->xposition_var = xposition;
}

double CustomApplPkt::getYposition() const
{
    return yposition_var;
}

void CustomApplPkt::setYposition(double yposition)
{
    this->yposition_var = yposition;
}

double CustomApplPkt::getSpeed() const
{
    return speed_var;
}

void CustomApplPkt::setSpeed(double speed)
{
    this->speed_var = speed;
}

int CustomApplPkt::getId() const
{
    return id_var;
}

void CustomApplPkt::setId(int id)
{
    this->id_var = id;
}

double CustomApplPkt::getAcceleration() const
{
    return acceleration_var;
}

void CustomApplPkt::setAcceleration(double acceleration)
{
    this->acceleration_var = acceleration;
}

double CustomApplPkt::getLeaderAcceleration() const
{
    return leaderAcceleration_var;
}

void CustomApplPkt::setLeaderAcceleration(double leaderAcceleration)
{
    this->leaderAcceleration_var = leaderAcceleration;
}

double CustomApplPkt::getLeaderSpeed() const
{
    return leaderSpeed_var;
}

void CustomApplPkt::setLeaderSpeed(double leaderSpeed)
{
    this->leaderSpeed_var = leaderSpeed;
}

bool CustomApplPkt::getBeaconingEnabled() const
{
    return beaconingEnabled_var;
}

void CustomApplPkt::setBeaconingEnabled(bool beaconingEnabled)
{
    this->beaconingEnabled_var = beaconingEnabled;
}

class CustomApplPktDescriptor : public cClassDescriptor
{
  public:
    CustomApplPktDescriptor();
    virtual ~CustomApplPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CustomApplPktDescriptor);

CustomApplPktDescriptor::CustomApplPktDescriptor() : cClassDescriptor("CustomApplPkt", "cPacket")
{
}

CustomApplPktDescriptor::~CustomApplPktDescriptor()
{
}

bool CustomApplPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CustomApplPkt *>(obj)!=NULL;
}

const char *CustomApplPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CustomApplPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int CustomApplPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *CustomApplPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destAddr",
        "srcAddr",
        "xposition",
        "yposition",
        "speed",
        "id",
        "acceleration",
        "leaderAcceleration",
        "leaderSpeed",
        "beaconingEnabled",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int CustomApplPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+1;
    if (fieldName[0]=='x' && strcmp(fieldName, "xposition")==0) return base+2;
    if (fieldName[0]=='y' && strcmp(fieldName, "yposition")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "speed")==0) return base+4;
    if (fieldName[0]=='i' && strcmp(fieldName, "id")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "acceleration")==0) return base+6;
    if (fieldName[0]=='l' && strcmp(fieldName, "leaderAcceleration")==0) return base+7;
    if (fieldName[0]=='l' && strcmp(fieldName, "leaderSpeed")==0) return base+8;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconingEnabled")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CustomApplPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "LAddress::L3Type",
        "LAddress::L3Type",
        "double",
        "double",
        "double",
        "int",
        "double",
        "double",
        "double",
        "bool",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *CustomApplPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CustomApplPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CustomApplPkt *pp = (CustomApplPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CustomApplPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CustomApplPkt *pp = (CustomApplPkt *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestAddr(); return out.str();}
        case 1: {std::stringstream out; out << pp->getSrcAddr(); return out.str();}
        case 2: return double2string(pp->getXposition());
        case 3: return double2string(pp->getYposition());
        case 4: return double2string(pp->getSpeed());
        case 5: return long2string(pp->getId());
        case 6: return double2string(pp->getAcceleration());
        case 7: return double2string(pp->getLeaderAcceleration());
        case 8: return double2string(pp->getLeaderSpeed());
        case 9: return bool2string(pp->getBeaconingEnabled());
        default: return "";
    }
}

bool CustomApplPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CustomApplPkt *pp = (CustomApplPkt *)object; (void)pp;
    switch (field) {
        case 2: pp->setXposition(string2double(value)); return true;
        case 3: pp->setYposition(string2double(value)); return true;
        case 4: pp->setSpeed(string2double(value)); return true;
        case 5: pp->setId(string2long(value)); return true;
        case 6: pp->setAcceleration(string2double(value)); return true;
        case 7: pp->setLeaderAcceleration(string2double(value)); return true;
        case 8: pp->setLeaderSpeed(string2double(value)); return true;
        case 9: pp->setBeaconingEnabled(string2bool(value)); return true;
        default: return false;
    }
}

const char *CustomApplPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        "LAddress::L3Type",
        "LAddress::L3Type",
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<10) ? fieldStructNames[field] : NULL;
}

void *CustomApplPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CustomApplPkt *pp = (CustomApplPkt *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestAddr()); break;
        case 1: return (void *)(&pp->getSrcAddr()); break;
        default: return NULL;
    }
}


