#ifndef _C_CkImap_H
#define _C_CkImap_H
#include "Chilkat_C.h"

HCkImap CkImap_Create(void);
void CkImap_Dispose(HCkImap handle);
BOOL CkImap_getAppendSeen(HCkImap cHandle);
void CkImap_putAppendSeen(HCkImap cHandle, BOOL newVal);
int CkImap_getAppendUid(HCkImap cHandle);
void CkImap_getAuthMethod(HCkImap cHandle, HCkString retval);
void CkImap_putAuthMethod(HCkImap cHandle, const char *newVal);
void CkImap_getAuthzId(HCkImap cHandle, HCkString retval);
void CkImap_putAuthzId(HCkImap cHandle, const char *newVal);
BOOL CkImap_getAutoDownloadAttachments(HCkImap cHandle);
void CkImap_putAutoDownloadAttachments(HCkImap cHandle, BOOL newVal);
BOOL CkImap_getAutoFix(HCkImap cHandle);
void CkImap_putAutoFix(HCkImap cHandle, BOOL newVal);
void CkImap_getClientIpAddress(HCkImap cHandle, HCkString retval);
void CkImap_putClientIpAddress(HCkImap cHandle, const char *newVal);
int CkImap_getConnectTimeout(HCkImap cHandle);
void CkImap_putConnectTimeout(HCkImap cHandle, int newVal);
void CkImap_getConnectedToHost(HCkImap cHandle, HCkString retval);
void CkImap_getDebugLogFilePath(HCkImap cHandle, HCkString retval);
void CkImap_putDebugLogFilePath(HCkImap cHandle, const char *newVal);
void CkImap_getDomain(HCkImap cHandle, HCkString retval);
void CkImap_putDomain(HCkImap cHandle, const char *newVal);
HCkImapProgress CkImap_getEventCallbackObject(HCkImap cHandle);
void CkImap_putEventCallbackObject(HCkImap cHandle, HCkImapProgress newVal);
long CkImap_getHeartbeatMs(HCkImap cHandle);
void CkImap_putHeartbeatMs(HCkImap cHandle, long newVal);
void CkImap_getHttpProxyAuthMethod(HCkImap cHandle, HCkString retval);
void CkImap_putHttpProxyAuthMethod(HCkImap cHandle, const char *newVal);
void CkImap_getHttpProxyDomain(HCkImap cHandle, HCkString retval);
void CkImap_putHttpProxyDomain(HCkImap cHandle, const char *newVal);
void CkImap_getHttpProxyHostname(HCkImap cHandle, HCkString retval);
void CkImap_putHttpProxyHostname(HCkImap cHandle, const char *newVal);
void CkImap_getHttpProxyPassword(HCkImap cHandle, HCkString retval);
void CkImap_putHttpProxyPassword(HCkImap cHandle, const char *newVal);
int CkImap_getHttpProxyPort(HCkImap cHandle);
void CkImap_putHttpProxyPort(HCkImap cHandle, int newVal);
void CkImap_getHttpProxyUsername(HCkImap cHandle, HCkString retval);
void CkImap_putHttpProxyUsername(HCkImap cHandle, const char *newVal);
BOOL CkImap_getKeepSessionLog(HCkImap cHandle);
void CkImap_putKeepSessionLog(HCkImap cHandle, BOOL newVal);
void CkImap_getLastAppendedMime(HCkImap cHandle, HCkString retval);
void CkImap_getLastCommand(HCkImap cHandle, HCkString retval);
void CkImap_getLastErrorHtml(HCkImap cHandle, HCkString retval);
void CkImap_getLastErrorText(HCkImap cHandle, HCkString retval);
void CkImap_getLastErrorXml(HCkImap cHandle, HCkString retval);
void CkImap_getLastIntermediateResponse(HCkImap cHandle, HCkString retval);
void CkImap_getLastResponse(HCkImap cHandle, HCkString retval);
void CkImap_getLoggedInUser(HCkImap cHandle, HCkString retval);
long CkImap_getNumMessages(HCkImap cHandle);
BOOL CkImap_getPeekMode(HCkImap cHandle);
void CkImap_putPeekMode(HCkImap cHandle, BOOL newVal);
int CkImap_getPort(HCkImap cHandle);
void CkImap_putPort(HCkImap cHandle, int newVal);
int CkImap_getReadTimeout(HCkImap cHandle);
void CkImap_putReadTimeout(HCkImap cHandle, int newVal);
void CkImap_getSearchCharset(HCkImap cHandle, HCkString retval);
void CkImap_putSearchCharset(HCkImap cHandle, const char *newVal);
void CkImap_getSelectedMailbox(HCkImap cHandle, HCkString retval);
int CkImap_getSendBufferSize(HCkImap cHandle);
void CkImap_putSendBufferSize(HCkImap cHandle, int newVal);
char CkImap_getSeparatorChar(HCkImap cHandle);
void CkImap_putSeparatorChar(HCkImap cHandle, char newVal);
void CkImap_getSessionLog(HCkImap cHandle, HCkString retval);
int CkImap_getSoRcvBuf(HCkImap cHandle);
void CkImap_putSoRcvBuf(HCkImap cHandle, int newVal);
int CkImap_getSoSndBuf(HCkImap cHandle);
void CkImap_putSoSndBuf(HCkImap cHandle, int newVal);
void CkImap_getSocksHostname(HCkImap cHandle, HCkString retval);
void CkImap_putSocksHostname(HCkImap cHandle, const char *newVal);
void CkImap_getSocksPassword(HCkImap cHandle, HCkString retval);
void CkImap_putSocksPassword(HCkImap cHandle, const char *newVal);
int CkImap_getSocksPort(HCkImap cHandle);
void CkImap_putSocksPort(HCkImap cHandle, int newVal);
void CkImap_getSocksUsername(HCkImap cHandle, HCkString retval);
void CkImap_putSocksUsername(HCkImap cHandle, const char *newVal);
int CkImap_getSocksVersion(HCkImap cHandle);
void CkImap_putSocksVersion(HCkImap cHandle, int newVal);
BOOL CkImap_getSsl(HCkImap cHandle);
void CkImap_putSsl(HCkImap cHandle, BOOL newVal);
void CkImap_getSslProtocol(HCkImap cHandle, HCkString retval);
void CkImap_putSslProtocol(HCkImap cHandle, const char *newVal);
BOOL CkImap_getSslServerCertVerified(HCkImap cHandle);
BOOL CkImap_getStartTls(HCkImap cHandle);
void CkImap_putStartTls(HCkImap cHandle, BOOL newVal);
int CkImap_getUidNext(HCkImap cHandle);
int CkImap_getUidValidity(HCkImap cHandle);
BOOL CkImap_getUtf8(HCkImap cHandle);
void CkImap_putUtf8(HCkImap cHandle, BOOL newVal);
BOOL CkImap_getVerboseLogging(HCkImap cHandle);
void CkImap_putVerboseLogging(HCkImap cHandle, BOOL newVal);
void CkImap_getVersion(HCkImap cHandle, HCkString retval);
BOOL CkImap_AddPfxSourceData(HCkImap cHandle, HCkByteData pfxData, const char *password);
BOOL CkImap_AddPfxSourceFile(HCkImap cHandle, const char *pfxFilePath, const char *password);
BOOL CkImap_AppendMail(HCkImap cHandle, const char *mailbox, HCkEmail email);
BOOL CkImap_AppendMime(HCkImap cHandle, const char *mailbox, const char *mimeText);
BOOL CkImap_AppendMimeWithDate(HCkImap cHandle, const char *mailbox, const char *mimeText, SYSTEMTIME *internalDate);
BOOL CkImap_AppendMimeWithDateStr(HCkImap cHandle, const char *mailbox, const char *mimeText, const char *internalDateStr);
BOOL CkImap_AppendMimeWithFlags(HCkImap cHandle, const char *mailbox, const char *mimeText, BOOL seen, BOOL flagged, BOOL answered, BOOL draft);
HCkMessageSet CkImap_CheckForNewEmail(HCkImap cHandle);
void CkImap_ClearSessionLog(HCkImap cHandle);
BOOL CkImap_CloseMailbox(HCkImap cHandle, const char *mailbox);
BOOL CkImap_Connect(HCkImap cHandle, const char *hostname);
BOOL CkImap_Copy(HCkImap cHandle, long msgId, BOOL bUid, const char *copyToMailbox);
BOOL CkImap_CopyMultiple(HCkImap cHandle, HCkMessageSet messageSet, const char *copyToMailbox);
BOOL CkImap_CopySequence(HCkImap cHandle, int startSeqNum, int count, const char *copyToMailbox);
BOOL CkImap_CreateMailbox(HCkImap cHandle, const char *mailbox);
BOOL CkImap_DeleteMailbox(HCkImap cHandle, const char *mailbox);
BOOL CkImap_Disconnect(HCkImap cHandle);
BOOL CkImap_ExamineMailbox(HCkImap cHandle, const char *mailbox);
BOOL CkImap_Expunge(HCkImap cHandle);
BOOL CkImap_ExpungeAndClose(HCkImap cHandle);
BOOL CkImap_FetchAttachment(HCkImap cHandle, HCkEmail email, int attachIndex, const char *saveToPath);
BOOL CkImap_FetchAttachmentBytes(HCkImap cHandle, HCkEmail email, int attachIndex, HCkByteData outBytes);
BOOL CkImap_FetchAttachmentString(HCkImap cHandle, HCkEmail email, int attachIndex, const char *charset, HCkString outStr);
HCkEmailBundle CkImap_FetchBundle(HCkImap cHandle, HCkMessageSet messageSet);
HCkStringArray CkImap_FetchBundleAsMime(HCkImap cHandle, HCkMessageSet messageSet);
BOOL CkImap_FetchFlags(HCkImap cHandle, long msgId, BOOL bUid, HCkString outStrFlags);
HCkEmailBundle CkImap_FetchHeaders(HCkImap cHandle, HCkMessageSet messageSet);
HCkEmailBundle CkImap_FetchSequence(HCkImap cHandle, int startSeqNum, int numMessages);
HCkStringArray CkImap_FetchSequenceAsMime(HCkImap cHandle, int startSeqNum, int count);
HCkEmailBundle CkImap_FetchSequenceHeaders(HCkImap cHandle, int startSeqNum, int numMessages);
HCkEmail CkImap_FetchSingle(HCkImap cHandle, long msgId, BOOL bUid);
BOOL CkImap_FetchSingleAsMime(HCkImap cHandle, long msgId, BOOL bUid, HCkString outStrMime);
HCkEmail CkImap_FetchSingleHeader(HCkImap cHandle, long msgId, BOOL bUid);
BOOL CkImap_FetchSingleHeaderAsMime(HCkImap cHandle, int msgId, BOOL bUID, HCkString outStr);
HCkMessageSet CkImap_GetAllUids(HCkImap cHandle);
BOOL CkImap_GetMailAttachFilename(HCkImap cHandle, HCkEmail email, long attachIndex, HCkString outStrFilename);
long CkImap_GetMailAttachSize(HCkImap cHandle, HCkEmail email, long attachIndex);
long CkImap_GetMailFlag(HCkImap cHandle, HCkEmail email, const char *flagName);
long CkImap_GetMailNumAttach(HCkImap cHandle, HCkEmail email);
long CkImap_GetMailSize(HCkImap cHandle, HCkEmail email);
HCkCert CkImap_GetSslServerCert(HCkImap cHandle);
BOOL CkImap_IsConnected(HCkImap cHandle);
BOOL CkImap_IsLoggedIn(HCkImap cHandle);
BOOL CkImap_IsUnlocked(HCkImap cHandle);
HCkMailboxes CkImap_ListMailboxes(HCkImap cHandle, const char *reference, const char *wildcardedMailbox);
HCkMailboxes CkImap_ListSubscribed(HCkImap cHandle, const char *reference, const char *wildcardedMailbox);
BOOL CkImap_Login(HCkImap cHandle, const char *login, const char *password);
BOOL CkImap_Logout(HCkImap cHandle);
BOOL CkImap_Noop(HCkImap cHandle);
BOOL CkImap_RefetchMailFlags(HCkImap cHandle, HCkEmail emailInOut);
BOOL CkImap_RenameMailbox(HCkImap cHandle, const char *fromMailbox, const char *toMailbox);
BOOL CkImap_SaveLastError(HCkImap cHandle, const char *path);
HCkMessageSet CkImap_Search(HCkImap cHandle, const char *criteria, BOOL bUid);
BOOL CkImap_SelectMailbox(HCkImap cHandle, const char *mailbox);
BOOL CkImap_SendRawCommand(HCkImap cHandle, const char *rawCommand, HCkString outRawResponse);
#if defined(WIN32) && !defined(__MINGW32__)
#if defined(WIN32) && !defined(WINCE) && !defined(__MINGW32__)
BOOL CkImap_SetCSP(HCkImap cHandle, HCkCsp csp);
#endif
#endif
BOOL CkImap_SetDecryptCert2(HCkImap cHandle, HCkCert cert, HCkPrivateKey key);
BOOL CkImap_SetFlag(HCkImap cHandle, long msgId, BOOL bUid, const char *flagName, long value);
BOOL CkImap_SetFlags(HCkImap cHandle, HCkMessageSet messageSet, const char *flagName, long value);
BOOL CkImap_SetMailFlag(HCkImap cHandle, HCkEmail email, const char *flagName, long value);
BOOL CkImap_SetSslClientCert(HCkImap cHandle, HCkCert cert);
BOOL CkImap_SetSslClientCertPem(HCkImap cHandle, const char *pemDataOrPath, const char *pemPassword);
BOOL CkImap_SetSslClientCertPfx(HCkImap cHandle, const char *pfxPath, const char *pfxPassword);
BOOL CkImap_SshAuthenticatePk(HCkImap cHandle, const char *sshLogin, HCkSshKey privateKey);
BOOL CkImap_SshAuthenticatePw(HCkImap cHandle, const char *sshLogin, const char *sshPassword);
BOOL CkImap_SshTunnel(HCkImap cHandle, const char *sshServerHostname, int sshServerPort);
BOOL CkImap_StoreFlags(HCkImap cHandle, long msgId, BOOL bUid, const char *flagName, long value);
BOOL CkImap_Subscribe(HCkImap cHandle, const char *mailbox);
BOOL CkImap_UnlockComponent(HCkImap cHandle, const char *unlockCode);
BOOL CkImap_Unsubscribe(HCkImap cHandle, const char *mailbox);
const char *CkImap_authMethod(HCkImap cHandle);
const char *CkImap_authzId(HCkImap cHandle);
const char *CkImap_clientIpAddress(HCkImap cHandle);
const char *CkImap_connectedToHost(HCkImap cHandle);
const char *CkImap_debugLogFilePath(HCkImap cHandle);
const char *CkImap_domain(HCkImap cHandle);
const char *CkImap_fetchAttachmentString(HCkImap cHandle, HCkEmail email, int attachIndex, const char *charset);
const char *CkImap_fetchFlags(HCkImap cHandle, long msgId, BOOL bUid);
const char *CkImap_fetchSingleAsMime(HCkImap cHandle, long msgId, BOOL bUid);
const char *CkImap_fetchSingleHeaderAsMime(HCkImap cHandle, int msgId, BOOL bUID);
const char *CkImap_getMailAttachFilename(HCkImap cHandle, HCkEmail email, long attachIndex);
const char *CkImap_httpProxyAuthMethod(HCkImap cHandle);
const char *CkImap_httpProxyDomain(HCkImap cHandle);
const char *CkImap_httpProxyHostname(HCkImap cHandle);
const char *CkImap_httpProxyPassword(HCkImap cHandle);
const char *CkImap_httpProxyUsername(HCkImap cHandle);
const char *CkImap_lastAppendedMime(HCkImap cHandle);
const char *CkImap_lastCommand(HCkImap cHandle);
const char *CkImap_lastErrorHtml(HCkImap cHandle);
const char *CkImap_lastErrorText(HCkImap cHandle);
const char *CkImap_lastErrorXml(HCkImap cHandle);
const char *CkImap_lastIntermediateResponse(HCkImap cHandle);
const char *CkImap_lastResponse(HCkImap cHandle);
const char *CkImap_loggedInUser(HCkImap cHandle);
const char *CkImap_searchCharset(HCkImap cHandle);
const char *CkImap_selectedMailbox(HCkImap cHandle);
const char *CkImap_sendRawCommand(HCkImap cHandle, const char *rawCommand);
const char *CkImap_sessionLog(HCkImap cHandle);
const char *CkImap_socksHostname(HCkImap cHandle);
const char *CkImap_socksPassword(HCkImap cHandle);
const char *CkImap_socksUsername(HCkImap cHandle);
const char *CkImap_sslProtocol(HCkImap cHandle);
const char *CkImap_version(HCkImap cHandle);
#endif