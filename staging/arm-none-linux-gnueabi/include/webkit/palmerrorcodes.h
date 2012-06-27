#ifndef WEBOS_ERROR_CODES_H
#define WEBOS_ERROR_CODES_H

namespace Palm
{

/**
 * <strong>Do not change these values w/o coordinating the changes with the browser application
 * and other WebKit (direct or indirect) clients.</strong>
 */

/*
 * Component/Module: Error range
 * ================  ===========
 * No error          0 
 * OS (errno)        1 .. 999
 * WebKit            1000 .. 1999
 * CURL              2000 .. 2999
 */

/** @defgroup OperatingSystem Operating system errors
 *  @{
 */

const int ERR_SYS_FILE_DOESNT_EXIST = 14;  ///< The file doesn't exist.
const int ERR_SYS_FAILURE           = 999; ///< Unknown error code
const int ERR_SYS_LAST_ERROR        = 999;

/** @} */ // end of OperatingSystem





/** @defgroup WebKit Palm's WebKit library errors
 *  @{
 */

const int ERR_WK_FLOADER_CANCELLED   = 1000; ///< The user cancelled the frame load.
const int ERR_WK_FLOADER_BLOCKED     = 1001; ///< Loading of the resource was blocked.
const int ERR_WK_FLOADER_CANNOT_SHOW = 1002; ///< Frame loader cannot show URL.
const int ERR_WK_FLOADER_CANNOT_SHOW_MIME = 1003; ///< Frame loader cannot show MIME type.
const int ERR_WK_CERT_NOT_AUTO_VERIFY= 1004; ///< Certificate could not be automatically verified.
const int ERR_NO_INTERNET_CONNECTION = 1005; ///< Request was made with no Internet connection.

/** @} */ // end of WebKit





/** @defgroup CURL libcurl errors
 * Errors returned by the CURL library (libcurl).
 * /usr/include/curl/curl.h
 *  @{
 */

/// All other CURL errors are mapped to this value.
const int ERR_CURL_FIRST_ERROR           = 2000;
const int ERR_CURL_FAILURE               = 2000;

const int ERR_CURL_UNSUPPORTED_PROTOCOL  = 2001; ///< CURLE_UNSUPPORTED_PROTOCOL(1)
const int ERR_CURL_FAILED_INIT           = 2002; ///< CURLE_FAILED_INIT(2)
const int ERR_CURL_URL_MALFORMAT         = 2003; ///< CURLE_URL_MALFORMAT(3)
const int ERR_CURL_COULDNT_RESOLVE_PROXY = 2005; ///< CURLE_COULDNT_RESOLVE_PROXY(5)
const int ERR_CURL_COULDNT_RESOLVE_HOST  = 2006; ///< CURLE_COULDNT_RESOLVE_HOST(6)
const int ERR_CURL_COULDNT_CONNECT       = 2007; ///< CURLE_COULDNT_CONNECT(7)
const int ERR_CURL_FTP_WEIRD_SERVER_REPLY= 2008; ///< CURLE_FTP_WEIRD_SERVER_REPLY(8)
const int ERR_CURL_REMOTE_ACCESS_DENIED  = 2009; ///< CURLE_REMOTE_ACCESS_DENIED(9)
const int ERR_CURL_FTP_WEIRD_PASS_REPLY  = 2011; ///< CURLE_FTP_WEIRD_PASS_REPLY(11)
const int ERR_CURL_FTP_WEIRD_PASV_REPLY  = 2013; ///< CURLE_FTP_WEIRD_PASV_REPLY(13)
const int ERR_CURL_FTP_WEIRD_227_FORMAT  = 2014; ///< CURLE_FTP_WEIRD_227_FORMAT(14)
const int ERR_CURL_FTP_CANT_GET_HOST     = 2015; ///< CURLE_FTP_CANT_GET_HOST(15)
const int ERR_CURL_FTP_COULDNT_SET_TYPE  = 2017; ///< CURLE_FTP_COULDNT_SET_TYPE(17)
const int ERR_CURL_PARTIAL_FILE          = 2018; ///< CURLE_PARTIAL_FILE(18)
const int ERR_CURL_FTP_COULDNT_RETR_FILE = 2019; ///< CURLE_FTP_COULDNT_RETR_FILE(19)
const int ERR_CURL_QUOTE_ERROR           = 2021; ///< CURLE_QUOTE_ERROR(21)
const int ERR_CURL_HTTP_RETURNED_ERROR   = 2022; ///< CURLE_HTTP_RETURNED_ERROR(22)
const int ERR_CURL_WRITE_ERROR           = 2023; ///< CURLE_WRITE_ERROR(23)
const int ERR_CURL_UPLOAD_FAILED         = 2025; ///< CURLE_UPLOAD_FAILED(25)
const int ERR_CURL_READ_ERROR            = 2026; ///< CURLE_READ_ERROR(26)
const int ERR_CURL_OUT_OF_MEMORY         = 2027; ///< CURLE_OUT_OF_MEMORY(27)
const int ERR_CURL_OPERATION_TIMEDOUT    = 2028; ///< CURLE_OPERATION_TIMEDOUT(28)
const int ERR_CURL_FTP_PORT_FAILED       = 2030; ///< CURLE_FTP_PORT_FAILED(30)
const int ERR_CURL_FTP_COULDNT_USE_REST  = 2031; ///< CURLE_FTP_COULDNT_USE_REST(31)
const int ERR_CURL_RANGE_ERROR           = 2033; ///< CURLE_RANGE_ERROR(33)
const int ERR_CURL_HTTP_POST_ERROR       = 2034; ///< CURLE_HTTP_POST_ERROR(34)
const int ERR_CURL_SSL_CONNECT_ERROR     = 2035; ///< CURLE_SSL_CONNECT_ERROR(35)
const int ERR_CURL_BAD_DOWNLOAD_RESUME   = 2036; ///< CURLE_BAD_DOWNLOAD_RESUME(36)
const int ERR_CURL_FILE_COULDNT_READ_FILE= 2037; ///< CURLE_FILE_COULDNT_READ_FILE(37)
const int ERR_CURL_LDAP_CANNOT_BIND      = 2038; ///< CURLE_LDAP_CANNOT_BIND(38)
const int ERR_CURL_LDAP_SEARCH_FAILED    = 2039; ///< CURLE_LDAP_SEARCH_FAILED(39)
const int ERR_CURL_FUNCTION_NOT_FOUND    = 2041; ///< CURLE_FUNCTION_NOT_FOUND(41)
const int ERR_CURL_ABORTED_BY_CALLBACK   = 2042; ///< CURLE_ABORTED_BY_CALLBACK(42)
const int ERR_CURL_BAD_FUNCTION_ARGUMENT = 2043; ///< CURLE_BAD_FUNCTION_ARGUMENT(43)
const int ERR_CURL_INTERFACE_FAILED      = 2045; ///< CURLE_INTERFACE_FAILED(45)
const int ERR_CURL_TOO_MANY_REDIRECTS    = 2047; ///< CURLE_TOO_MANY_REDIRECTS (47)
const int ERR_CURL_UNKNOWN_TELNET_OPTION = 2048; ///< CURLE_UNKNOWN_TELNET_OPTION(48)
const int ERR_CURL_TELNET_OPTION_SYNTAX  = 2049; ///< CURLE_TELNET_OPTION_SYNTAX (49)
const int ERR_CURL_PEER_FAILED_VERIFICATION = 2051; ///< CURLE_PEER_FAILED_VERIFICATION(51)
const int ERR_CURL_GOT_NOTHING           = 2052; ///< CURLE_GOT_NOTHING(52)
const int ERR_CURL_SSL_ENGINE_NOTFOUND   = 2053; ///< CURLE_SSL_ENGINE_NOTFOUND(53)
const int ERR_CURL_SSL_ENGINE_SETFAILED  = 2054; ///< CURLE_SSL_ENGINE_SETFAILED(54)
const int ERR_CURL_SEND_ERROR            = 2055; ///< CURLE_SEND_ERROR(55)
const int ERR_CURL_RECV_ERROR            = 2056; ///< CURLE_RECV_ERROR(56)
const int ERR_CURL_SSL_CERTPROBLEM       = 2058; ///< CURLE_SSL_CERTPROBLEM(58)
const int ERR_CURL_SSL_CIPHER            = 2059; ///< CURLE_SSL_CIPHER(59)
const int ERR_CURL_SSL_CACERT            = 2060; ///< CURLE_SSL_CACERT(60)
const int ERR_CURL_BAD_CONTENT_ENCODING  = 2061; ///< CURLE_BAD_CONTENT_ENCODING(61)
const int ERR_CURL_LDAP_INVALID_URL      = 2062; ///< CURLE_LDAP_INVALID_URL(62)
const int ERR_CURL_FILESIZE_EXCEEDED     = 2063; ///< CURLE_FILESIZE_EXCEEDED(63)
const int ERR_CURL_USE_SSL_FAILED        = 2064; ///< CURLE_USE_SSL_FAILED(64)
const int ERR_CURL_SEND_FAIL_REWIND      = 2065; ///< CURLE_SEND_FAIL_REWIND(65)
const int ERR_CURL_SSL_ENGINE_INITFAILED = 2066; ///< CURLE_SSL_ENGINE_INITFAILED(66)
const int ERR_CURL_LOGIN_DENIED          = 2067; ///< CURLE_LOGIN_DENIED(67)
const int ERR_CURL_TFTP_NOTFOUND         = 2068; ///< CURLE_TFTP_NOTFOUND(68)
const int ERR_CURL_TFTP_PERM             = 2069; ///< CURLE_TFTP_PERM(69)
const int ERR_CURL_REMOTE_DISK_FULL      = 2070; ///< CURLE_REMOTE_DISK_FULL(70)
const int ERR_CURL_TFTP_ILLEGAL          = 2071; ///< CURLE_TFTP_ILLEGAL(71)
const int ERR_CURL_TFTP_UNKNOWNID        = 2072; ///< CURLE_TFTP_UNKNOWNID(72)
const int ERR_CURL_REMOTE_FILE_EXISTS    = 2073; ///< CURLE_REMOTE_FILE_EXISTS(73)
const int ERR_CURL_TFTP_NOSUCHUSER       = 2074; ///< CURLE_TFTP_NOSUCHUSER(74)
const int ERR_CURL_CONV_FAILED           = 2075; ///< CURLE_CONV_FAILED(75)
const int ERR_CURL_CONV_REQD             = 2076; ///< CURLE_CONV_REQD(76)
const int ERR_CURL_SSL_CACERT_BADFILE    = 2077; ///< CURLE_SSL_CACERT_BADFILE(77)
const int ERR_CURL_REMOTE_FILE_NOT_FOUND = 2078; ///< CURLE_REMOTE_FILE_NOT_FOUND(78)
const int ERR_CURL_SSH                   = 2079; ///< CURLE_SSH(79)
const int ERR_CURL_SSL_SHUTDOWN_FAILED   = 2080; ///< CURLE_SSL_SHUTDOWN_FAILED(80)
const int ERR_CURL_AGAIN                 = 2081; ///< CURLE_AGAIN(81)
const int ERR_CURL_SSL_CRL_BADFILE       = 2082; ///< CURLE_SSL_CRL_BADFILE(82)
const int ERR_CURL_SSL_ISSUER_ERROR      = 2083; ///< CURLE_SSL_ISSUER_ERROR(83)

/** @} */ // end of CURL



/**
 * Map a system error (errno) to a Palm error code.
 */
int MapErrnoToPalmError(int errNo);

#if defined(__CURL_CURL_H)
/**
 * Map a CURL error code to a Palm error code.
 */
int MapCurlErrToPalmError(CURLcode errNo);
#endif


} // namespace Palm


#endif // WEBOS_ERROR_CODES_H
