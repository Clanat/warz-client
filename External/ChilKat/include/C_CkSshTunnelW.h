#ifndef _C_CkSshTunnel_W_H
#define _C_CkSshTunnel_W_H
#include "Chilkat_C.h"

HCkSshTunnelW CkSshTunnelW_Create(void);
HCkSshTunnelW CkSshTunnelW_Create2(bool bForMono);
void CkSshTunnelW_Dispose(HCkSshTunnelW handle);
void CkSshTunnelW_getAcceptThreadSessionLogPath(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putAcceptThreadSessionLogPath(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getConnectLog(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putConnectLog(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getConnectTimeoutMs(HCkSshTunnelW cHandle);
void CkSshTunnelW_putConnectTimeoutMs(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getDebugLogFilePath(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putDebugLogFilePath(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getDestHostname(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putDestHostname(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getDestPort(HCkSshTunnelW cHandle);
void CkSshTunnelW_putDestPort(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getHttpProxyAuthMethod(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putHttpProxyAuthMethod(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getHttpProxyDomain(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putHttpProxyDomain(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getHttpProxyHostname(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putHttpProxyHostname(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getHttpProxyPassword(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putHttpProxyPassword(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getHttpProxyPort(HCkSshTunnelW cHandle);
void CkSshTunnelW_putHttpProxyPort(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getHttpProxyUsername(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putHttpProxyUsername(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getIdleTimeoutMs(HCkSshTunnelW cHandle);
void CkSshTunnelW_putIdleTimeoutMs(HCkSshTunnelW cHandle, int newVal);
BOOL CkSshTunnelW_getIsAccepting(HCkSshTunnelW cHandle);
BOOL CkSshTunnelW_getKeepConnectLog(HCkSshTunnelW cHandle);
void CkSshTunnelW_putKeepConnectLog(HCkSshTunnelW cHandle, BOOL newVal);
void CkSshTunnelW_getLastErrorHtml(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_getLastErrorText(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_getLastErrorXml(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_getListenBindIpAddress(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putListenBindIpAddress(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getListenPort(HCkSshTunnelW cHandle);
int CkSshTunnelW_getMaxPacketSize(HCkSshTunnelW cHandle);
void CkSshTunnelW_putMaxPacketSize(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getOutboundBindIpAddress(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putOutboundBindIpAddress(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getOutboundBindPort(HCkSshTunnelW cHandle);
void CkSshTunnelW_putOutboundBindPort(HCkSshTunnelW cHandle, int newVal);
int CkSshTunnelW_getSoRcvBuf(HCkSshTunnelW cHandle);
void CkSshTunnelW_putSoRcvBuf(HCkSshTunnelW cHandle, int newVal);
int CkSshTunnelW_getSoSndBuf(HCkSshTunnelW cHandle);
void CkSshTunnelW_putSoSndBuf(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getSocksHostname(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSocksHostname(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getSocksPassword(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSocksPassword(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getSocksPort(HCkSshTunnelW cHandle);
void CkSshTunnelW_putSocksPort(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getSocksUsername(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSocksUsername(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getSocksVersion(HCkSshTunnelW cHandle);
void CkSshTunnelW_putSocksVersion(HCkSshTunnelW cHandle, int newVal);
void CkSshTunnelW_getSshHostname(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSshHostname(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getSshLogin(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSshLogin(HCkSshTunnelW cHandle, const wchar_t *newVal);
void CkSshTunnelW_getSshPassword(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putSshPassword(HCkSshTunnelW cHandle, const wchar_t *newVal);
int CkSshTunnelW_getSshPort(HCkSshTunnelW cHandle);
void CkSshTunnelW_putSshPort(HCkSshTunnelW cHandle, int newVal);
BOOL CkSshTunnelW_getTcpNoDelay(HCkSshTunnelW cHandle);
void CkSshTunnelW_putTcpNoDelay(HCkSshTunnelW cHandle, BOOL newVal);
void CkSshTunnelW_getTunnelErrors(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_getTunnelThreadSessionLogPath(HCkSshTunnelW cHandle, HCkStringW retval);
void CkSshTunnelW_putTunnelThreadSessionLogPath(HCkSshTunnelW cHandle, const wchar_t *newVal);
BOOL CkSshTunnelW_getVerboseLogging(HCkSshTunnelW cHandle);
void CkSshTunnelW_putVerboseLogging(HCkSshTunnelW cHandle, BOOL newVal);
void CkSshTunnelW_getVersion(HCkSshTunnelW cHandle, HCkStringW retval);
BOOL CkSshTunnelW_BeginAccepting(HCkSshTunnelW cHandle, int listenPort);
void CkSshTunnelW_ClearTunnelErrors(HCkSshTunnelW cHandle);
BOOL CkSshTunnelW_GetTunnelsXml(HCkSshTunnelW cHandle, HCkStringW outStr);
BOOL CkSshTunnelW_SaveLastError(HCkSshTunnelW cHandle, const wchar_t *path);
BOOL CkSshTunnelW_SetSshAuthenticationKey(HCkSshTunnelW cHandle, HCkSshKeyW key);
BOOL CkSshTunnelW_StopAccepting(HCkSshTunnelW cHandle);
BOOL CkSshTunnelW_StopAllTunnels(HCkSshTunnelW cHandle, int maxWaitMs);
BOOL CkSshTunnelW_UnlockComponent(HCkSshTunnelW cHandle, const wchar_t *unlockCode);
const wchar_t *CkSshTunnelW__acceptThreadSessionLogPath(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__connectLog(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__debugLogFilePath(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__destHostname(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__getTunnelsXml(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__httpProxyAuthMethod(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__httpProxyDomain(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__httpProxyHostname(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__httpProxyPassword(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__httpProxyUsername(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__lastErrorHtml(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__lastErrorText(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__lastErrorXml(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__listenBindIpAddress(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__outboundBindIpAddress(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__socksHostname(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__socksPassword(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__socksUsername(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__sshHostname(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__sshLogin(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__sshPassword(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__tunnelErrors(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__tunnelThreadSessionLogPath(HCkSshTunnelW cHandle);
const wchar_t *CkSshTunnelW__version(HCkSshTunnelW cHandle);
#endif
