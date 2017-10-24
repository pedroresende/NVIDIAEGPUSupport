//
//  IONVDRVFramebufferPatched.cpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/23/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#include <IOKit/IOLib.h>
#include "IONDRVFramebufferPatched.h"

OSDefineMetaClassAndStructors(IONDRVFramebufferPatched, IONDRVFramebuffer)

#define super IONDRVFramebuffer

bool IONDRVFramebufferPatched::attach(IOService *provider) {
    kprintf("IONDRVFramebufferPatched::attach\n");
    bool ret = super::attach(provider);
    kprintf("IONDRVFramebufferPatched::attach: %d\n", ret);
    if (!ret) {
        ret = IOGraphicsDevice::attach(provider); // bypass AGDC find
        kprintf("IONDRVFramebufferPatched::attach: %d (new)\n", ret);
    }
    return ret;
}
