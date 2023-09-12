/*
 * SetupAPI stubs
 *
 * Copyright 2000 James Hatheway
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "setupapi_private.h"

/***********************************************************************
 *		pSetupRegistryDelnode(SETUPAPI.@)
 */
BOOL WINAPI pSetupRegistryDelnode(DWORD x, DWORD y)
{
    FIXME("%08x %08x: stub\n", x, y);
    return FALSE;
}

/***********************************************************************
 *      SetupPromptReboot(SETUPAPI.@)
 */
INT WINAPI SetupPromptReboot( HSPFILEQ file_queue, HWND owner, BOOL scan_only )
{
    FIXME("%p, %p, %d\n", file_queue, owner, scan_only);
    return 0;
}

/***********************************************************************
 *      SetupAddToSourceListA (SETUPAPI.@)
 */
BOOL WINAPI SetupAddToSourceListA(DWORD flags, PCSTR source)
{
    FIXME("0x%08lx %s: stub\n", flags, debugstr_a(source));
    return TRUE;
}

/***********************************************************************
 *      SetupAddToSourceListW (SETUPAPI.@)
 */
BOOL WINAPI SetupAddToSourceListW(DWORD flags, PCWSTR source)
{
    FIXME("0x%08lx %s: stub\n", flags, debugstr_w(source));
    return TRUE;
}

/***********************************************************************
 *      SetupSetSourceListA (SETUPAPI.@)
 */
BOOL WINAPI SetupSetSourceListA(DWORD flags, PCSTR *list, UINT count)
{
    FIXME("0x%08x %p %d\n", flags, list, count);
    return FALSE;
}

/***********************************************************************
 *      SetupSetSourceListW (SETUPAPI.@)
 */
BOOL WINAPI SetupSetSourceListW(DWORD flags, PCWSTR *list, UINT count)
{
    FIXME("0x%08x %p %d\n", flags, list, count);
    return FALSE;
}


/***********************************************************************
 *      SetupDiRemoveDevice(SETUPAPI.@)
 */
BOOL WINAPI
SetupDiRemoveDevice(
    IN HDEVINFO DeviceInfoSet,
    IN PSP_DEVINFO_DATA DeviceInfoData)
{
    FIXME ("Stub %p %p\n", DeviceInfoSet, DeviceInfoData);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}


/***********************************************************************
 *      SetupDiUnremoveDevice(SETUPAPI.@)
 */
BOOL WINAPI
SetupDiUnremoveDevice(
    IN HDEVINFO DeviceInfoSet,
    IN PSP_DEVINFO_DATA DeviceInfoData)
{
    FIXME ("Stub %p %p\n", DeviceInfoSet, DeviceInfoData);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}


/***********************************************************************
 *              SetupDiRemoveDeviceInterface (SETUPAPI.@)
 */
BOOL WINAPI SetupDiRemoveDeviceInterface(HDEVINFO info, PSP_DEVICE_INTERFACE_DATA data)
{
    FIXME("(%p, %p): stub\n", info, data);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}


WINSETUPAPI BOOL WINAPI SetupDiGetDeviceInterfaceAlias(IN HDEVINFO  DeviceInfoSet, IN PSP_DEVICE_INTERFACE_DATA  DeviceInterfaceData, IN CONST GUID *AliasInterfaceClassGuid, OUT PSP_DEVICE_INTERFACE_DATA  AliasDeviceInterfaceData)
{
    FIXME("%p %p %p %p %p stub\n", DeviceInfoSet, DeviceInterfaceData, AliasInterfaceClassGuid, AliasDeviceInterfaceData);
    SetLastError(ERROR_INVALID_PARAMETER);
    return FALSE;
}

/***********************************************************************
 *      SetupVerifyInfFileA(SETUPAPI.@)
 */
BOOL WINAPI
SetupVerifyInfFileA(
    IN PCSTR InfName,
    IN PSP_ALTPLATFORM_INFO AltPlatformInfo,
    OUT PSP_INF_SIGNER_INFO_A InfFileName)
{
    FIXME ("Stub %s %p %p\n", debugstr_a(InfName), AltPlatformInfo, InfFileName);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

/***********************************************************************
 *      SetupVerifyInfFileW(SETUPAPI.@)
 */
BOOL WINAPI
SetupVerifyInfFileW(
    IN PCWSTR InfName,
    IN PSP_ALTPLATFORM_INFO AltPlatformInfo,
    OUT PSP_INF_SIGNER_INFO_W InfFileName)
{
    FIXME ("Stub %s %p %p\n", debugstr_w(InfName), AltPlatformInfo, InfFileName);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

BOOL WINAPI
SetupDiSetDriverInstallParamsA(
    _In_ HDEVINFO DeviceInfoSet,
    _In_opt_ PSP_DEVINFO_DATA DeviceInfoData,
    _In_ PSP_DRVINFO_DATA_A DriverInfoData,
    _In_ PSP_DRVINSTALL_PARAMS DriverInstallParams)
{
    FIXME("Stub %p %p %p %p\n", DeviceInfoSet, DeviceInfoData, DriverInfoData, DriverInstallParams);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

BOOL WINAPI
SetupDiSetDriverInstallParamsW(
    _In_ HDEVINFO DeviceInfoSet,
    _In_opt_ PSP_DEVINFO_DATA DeviceInfoData,
    _In_ PSP_DRVINFO_DATA_W DriverInfoData,
    _In_ PSP_DRVINSTALL_PARAMS DriverInstallParams)
{
    FIXME("Stub %p %p %p %p\n", DeviceInfoSet, DeviceInfoData, DriverInfoData, DriverInstallParams);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

/***********************************************************************
 *              CM_Request_Device_EjectA  (SETUPAPI.@)
 */
CONFIGRET WINAPI CM_Request_Device_EjectA(DEVINST dev, PPNP_VETO_TYPE type, LPSTR name, ULONG length, ULONG flags)
{
    FIXME("(0x%08lx, %p, %p, %lu, 0x%08lx) stub\n", dev, type, name, length, flags);
    return CR_SUCCESS;
}

/***********************************************************************
 *              CM_Request_Device_EjectW  (SETUPAPI.@)
 */
CONFIGRET WINAPI CM_Request_Device_EjectW(DEVINST dev, PPNP_VETO_TYPE type, LPWSTR name, ULONG length, ULONG flags)
{
    FIXME("(0x%08lx, %p, %p, %lu, 0x%08lx) stub\n", dev, type, name, length, flags);
    return CR_SUCCESS;
}

BOOL WINAPI SetupDiGetClassRegistryPropertyW(const GUID *class, DWORD prop, DWORD *datatype, BYTE *buff, DWORD size,
    DWORD *req_size, const WCHAR *name, VOID *reserved)
{
    FIXME("class %s, prop %ld, datatype %p, buff %p, size %ld, req_size %p, name %s, reserved %p stub!\n",
        debugstr_guid(class), prop, datatype, buff, size, req_size, debugstr_w(name), reserved);
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}
