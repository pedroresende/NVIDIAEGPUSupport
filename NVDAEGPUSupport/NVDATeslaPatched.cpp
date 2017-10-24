//
//  NVDATeslaPatched.cpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/24/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#include "NVDATeslaPatched.h"

OSDefineMetaClassAndStructors(NVDATeslaPatched, NVDATesla)

#define super NVDATesla

bool NVDATeslaPatched::attach(IOService *provider) {
    kprintf("NVDATeslaPatched::attach\n");
    bool ret = super::attach(provider);
    kprintf("NVDATeslaPatched::attach: %d\n", ret);
    if (!ret) {
        ret = IOGraphicsDevice::attach(provider); // bypass AGDC find
        kprintf("NVDATeslaPatched::attach: %d (new)\n", ret);
    }
    return ret;
}
