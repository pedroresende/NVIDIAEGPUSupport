//
//  NVDATeslaPatched.hpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/24/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#ifndef NVDATeslaPatched_h
#define NVDATeslaPatched_h

#include "NVDA.h"

class NVDATeslaPatched : public NVDATesla
{
    OSDeclareDefaultStructors(NVDATeslaPatched)
public:
    virtual bool attach(IOService *provider) override;
};

#endif /* NVDATeslaPatched_h */
