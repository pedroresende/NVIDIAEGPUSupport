//
//  NVDAPatched.hpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/23/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#ifndef NVDAPatched_h
#define NVDAPatched_h

#include "NVDA.h"

class NVDAPatched : public NVDA
{
    OSDeclareDefaultStructors(NVDAPatched)
public:
    virtual bool attach(IOService *provider) override;
};

#endif /* NVDAPatched_h */
