//
//  NVDA.h
//  NVDAFramebuffer
//
//  Created by Yifan Lu on 10/23/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#ifndef NVDA_h
#define NVDA_h

#include <IOKit/ndrvsupport/IONDRVFramebuffer.h>

class NVDA : public IONDRVFramebuffer
{
    OSDeclareDefaultStructors(NVDA)
public:
    virtual IOReturn createNVDCNub(UInt32);
private:
    UInt64 data[50];
};

class NVDATesla : public IONDRVFramebuffer
{
    OSDeclareDefaultStructors(NVDATesla)
private:
    UInt64 data[46];
};

#endif /* NVDA_h */
