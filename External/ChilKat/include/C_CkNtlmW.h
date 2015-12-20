#ifndef _C_CkNtlm_W_H
#define _C_CkNtlm_W_H
#include "Chilkat_C.h"

HCkNtlmW CkNtlmW_Create(void);
HCkNtlmW CkNtlmW_Create2(bool bForMono);
void CkNtlmW_Dispose(HCkNtlmW handle);
void CkNtlmW_getClientChallenge(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putClientChallenge(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getDebugLogFilePath(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putDebugLogFilePath(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getDnsComputerName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putDnsComputerName(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getDnsDomainName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putDnsDomainName(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getDomain(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putDomain(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getEncodingMode(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putEncodingMode(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getFlags(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putFlags(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getLastErrorHtml(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_getLastErrorText(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_getLastErrorXml(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_getNetBiosComputerName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putNetBiosComputerName(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getNetBiosDomainName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putNetBiosDomainName(HCkNtlmW cHandle, const wchar_t *newVal);
int CkNtlmW_getNtlmVersion(HCkNtlmW cHandle);
void CkNtlmW_putNtlmVersion(HCkNtlmW cHandle, int newVal);
int CkNtlmW_getOemCodePage(HCkNtlmW cHandle);
void CkNtlmW_putOemCodePage(HCkNtlmW cHandle, int newVal);
void CkNtlmW_getPassword(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putPassword(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getServerChallenge(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putServerChallenge(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getTargetName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putTargetName(HCkNtlmW cHandle, const wchar_t *newVal);
void CkNtlmW_getUserName(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putUserName(HCkNtlmW cHandle, const wchar_t *newVal);
BOOL CkNtlmW_getVerboseLogging(HCkNtlmW cHandle);
void CkNtlmW_putVerboseLogging(HCkNtlmW cHandle, BOOL newVal);
void CkNtlmW_getVersion(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_getWorkstation(HCkNtlmW cHandle, HCkStringW retval);
void CkNtlmW_putWorkstation(HCkNtlmW cHandle, const wchar_t *newVal);
BOOL CkNtlmW_CompareType3(HCkNtlmW cHandle, const wchar_t *msg1, const wchar_t *msg2);
BOOL CkNtlmW_GenType1(HCkNtlmW cHandle, HCkStringW outStr);
BOOL CkNtlmW_GenType2(HCkNtlmW cHandle, const wchar_t *type1Msg, HCkStringW outStr);
BOOL CkNtlmW_GenType3(HCkNtlmW cHandle, const wchar_t *type2Msg, HCkStringW outStr);
BOOL CkNtlmW_LoadType3(HCkNtlmW cHandle, const wchar_t *type3Msg);
BOOL CkNtlmW_ParseType1(HCkNtlmW cHandle, const wchar_t *type1Msg, HCkStringW outStr);
BOOL CkNtlmW_ParseType2(HCkNtlmW cHandle, const wchar_t *type2Msg, HCkStringW outStr);
BOOL CkNtlmW_ParseType3(HCkNtlmW cHandle, const wchar_t *type3Msg, HCkStringW outStr);
BOOL CkNtlmW_SaveLastError(HCkNtlmW cHandle, const wchar_t *path);
BOOL CkNtlmW_SetFlag(HCkNtlmW cHandle, const wchar_t *flagLetter, BOOL on);
BOOL CkNtlmW_UnlockComponent(HCkNtlmW cHandle, const wchar_t *unlockCode);
const wchar_t *CkNtlmW__clientChallenge(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__debugLogFilePath(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__dnsComputerName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__dnsDomainName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__domain(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__encodingMode(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__flags(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__genType1(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__genType2(HCkNtlmW cHandle, const wchar_t *type1Msg);
const wchar_t *CkNtlmW__genType3(HCkNtlmW cHandle, const wchar_t *type2Msg);
const wchar_t *CkNtlmW__lastErrorHtml(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__lastErrorText(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__lastErrorXml(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__netBiosComputerName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__netBiosDomainName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__parseType1(HCkNtlmW cHandle, const wchar_t *type1Msg);
const wchar_t *CkNtlmW__parseType2(HCkNtlmW cHandle, const wchar_t *type2Msg);
const wchar_t *CkNtlmW__parseType3(HCkNtlmW cHandle, const wchar_t *type3Msg);
const wchar_t *CkNtlmW__password(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__serverChallenge(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__targetName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__userName(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__version(HCkNtlmW cHandle);
const wchar_t *CkNtlmW__workstation(HCkNtlmW cHandle);
#endif
