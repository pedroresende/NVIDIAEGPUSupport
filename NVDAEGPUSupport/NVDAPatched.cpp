//
//  NVDAPatched.cpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/23/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#include "NVDAPatched.h"

OSDefineMetaClassAndStructors(NVDAPatched, NVDA)

#define super NVDA

bool NVDAPatched::attach(IOService *provider) {
    kprintf("NVDAPatched::attach\n");
    bool ret = super::attach(provider);
    kprintf("NVDAPatched::attach: %d\n", ret);
    if (!ret) {
        ret = IOGraphicsDevice::attach(provider); // bypass AGDC find
        kprintf("NVDAPatched::attach: %d (new)\n", ret);
    }
    return ret;
}
