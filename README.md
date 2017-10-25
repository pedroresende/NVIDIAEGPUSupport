NVDAEGPUSupport
===============
This driver will allow your NVIDIA Web Drivers to work on High Sierra for eGPUs.

## Installation

1. Download and install [NVIDIA Quadro & GeForce Web Drivers](http://www.nvidia.com/Download/index.aspx) (you do not have to modify any plists!)
2. Disable [System Integrity Protection](https://developer.apple.com/library/content/documentation/Security/Conceptual/System_Integrity_Protection_Guide/ConfiguringSystemIntegrityProtection/ConfiguringSystemIntegrityProtection.html) (optionally just enable unsigned drivers with `csrutil enable --without kext`)
3. Install this package

## Uninstallation

Just delete `/Library/Extensions/NVDAEGPUSupport.kext`. No other files are created/modified by the installer.

## Patches

### IOFramebuffer `attach()` bypass

In High Sierra, Apple added support for eGPU to IOFramebuffer. By "added", I mean of course break existing support in the typical Apple manner. The offending code can be found in `IOGraphics-517.17/IOGraphicsFamily/IOFramebuffer.cpp`:

```c
bool IOFramebuffer::attach(IOService *provider)
{
    IOFB_START(attach,0,0,0);
    bool foundAGDC = false;
    bool tunnelled = (NULL != provider->getProperty(kIOPCITunnelledKey, gIOServicePlane,
            kIORegistryIterateRecursively | kIORegistryIterateParents));
    bool status = false;

    if (tunnelled) do {
        IOService *pci = provider;
        while ((NULL == OSDynamicCast(IOPCIDevice, pci)) &&
               (NULL != (pci = pci->getProvider())))
        {
            // Searching for device.
        }

        if (!pci) break;

        OSIterator *descendantIter = IORegistryIterator::iterateOver(
            pci, gIOServicePlane, kIORegistryIterateRecursively);
        IORegistryEntry *descendant;
        while ((descendant = OSDynamicCast(IORegistryEntry, descendantIter->getNextObject())))
        {
            if (descendant->metaCast("AppleGraphicsDeviceControl"))
            {
                foundAGDC = true;
                break;
            }
        }
        OSSafeReleaseNULL(descendantIter);
    } while (false);

    if (!tunnelled || foundAGDC) {
        status = super::attach(provider);
    }

    IOFB_END(attach,status,0,0);
    return status;
}
```

The idea here is that the framebuffer should wait for the graphics controller to be set up first. However, NVIDIA's drivers wait for the framebuffer to be set up first before setting up the controller, so there is a resource wait deadlock.

The "fix" here is to bypass this check and we need to do it in two places. `IONDRVFramebuffer` is used to set up a IOKit nub for each display port. `NVDA` is used to attach a driver to each nub. Both extend from `IOFramebuffer` and therefore needs to have the `attach()` method patched.

It is not immediately obvious if this causes any problems, and more research is needed here. I suspect this logic was used to fix some AMD specific race condition with eGPU attachment that is not applicable to NVIDIA drivers (the setup order is different).

### Adding `IOPCITunnelCompatible` key

The old way of doing this is to modify the Info.plist of the relevant driver. But that breaks the signature and also won't survive updates so it seems like too hacky of a solution to me. Instead, I use a little known feature of IOKit which is exporting a personality implemented in another kext. In this case, I copy-pasted the personality from `NVDAStartupWeb.kext` and added the `IOPCITunnelCompatible` key locally but pointed the `CFBundleIdentifier` to NVIDIA's bundle.

### Implementing GPUWrangler?

I'm not sure if this is needed or not, but in High Sierra, there is this new IOResource called `AppleGPUWrangler` that acts like `IODisplayWrangler` (which handles display plugging/unplugging and stuff) but for GPUs. The logic seems simple enough: extend `AppleGraphicsDeviceControl` and implement a couple of methods which return some vendor specific information. I've tried this and didn't get any different result so I suspect it's not really important if you're not hot-plugging eGPUs (which I don't think works anyways).
