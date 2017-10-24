//
//  IONVDRVFramebufferPatched.hpp
//  NVDAEGPUSupport
//
//  Created by Yifan Lu on 10/23/17.
//  Copyright © 2017 Yifan Lu. All rights reserved.
//

#ifndef IONVDRVFramebufferPatched_h
#define IONVDRVFramebufferPatched_h

#include <IOKit/ndrvsupport/IONDRVFramebuffer.h>

class IONDRVFramebufferPatched : public IONDRVFramebuffer
{
    OSDeclareDefaultStructors(IONDRVFramebufferPatched)
public:
    virtual bool attach(IOService *provider) override;
};

#endif /* IONVDRVFramebufferPatched_h */
