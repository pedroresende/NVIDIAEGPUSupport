#!/bin/bash

TMP="/tmp"
CURDIR="$(dirname "$0")"
OUTPKG="${CURDIR}/NVDAEGPUSupport.pkg"
PROJECT="${CURDIR}/../NVDAEGPUSupport.xcodeproj"
SCHEME="NVDAEGPUSupport"
TMP_ACHIVE="${TMP}/build.xcarchive"

if [[ ! -x /usr/bin/xcodebuild ]]; then
    echo "ERROR: Install Xcode Tools from Apple before using this script." >&2
    exit 1
fi

echo "Building project..."
xcodebuild -project ${PROJECT} -scheme ${SCHEME} archive -archivePath ${TMP_ACHIVE}

PLIST="${TMP}/build.plist"
ROOT_PATH="${TMP_ACHIVE}/Products/"
INSTALL_PKG_NAME="NVDAEGPUSupportDriver.pkg"
TMP_PKG="${TMP}/${INSTALL_PKG_NAME}"
echo "Building package..."
pkgbuild --analyze --root "${ROOT_PATH}" "${PLIST}"
pkgbuild --root "${ROOT_PATH}" --scripts "${CURDIR}/scripts" --component-plist "${PLIST}" "${TMP_PKG}"

echo "Building distribution..."
PACKAGE_DIST="${CURDIR}/package.dist"
#productbuild --product "${CURDIR}/product.plist" --package "${TMP_PKG}" --synthesize "${TMP_DIST}"

productbuild --distribution "${PACKAGE_DIST}" --package-path "${TMP}" --resources "${CURDIR}/res" "${OUTPKG}"
