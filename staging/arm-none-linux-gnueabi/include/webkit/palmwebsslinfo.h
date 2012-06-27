/* Copyright (C) 2008 Palm, Inc. All rights reserved
 *
 * 
 */

#ifndef SSLVALIDINFO_H
#define SSLVALIDINFO_H

#include <string>

namespace Palm {

class SSLValidationInfo {
	
public:
	
	enum {
		ValidationFailReason_SSL,
		ValidationFailReason_NameMismatch
	};
	
	enum {
		AcceptDecision_Reject = 0,
		AcceptDecision_AcceptPermanently = 1,
		AcceptDecision_AcceptForSessionOnly = 2
	};
	
	SSLValidationInfo(const std::string& certFileAndPath, const std::string& userMsgString,const std::string& commonName,
						 	const std::string& hostName, const std::string& signingCA, int failReason) :
		m_certFileAndPath(certFileAndPath),
		m_userMsgString(userMsgString),
		m_CommonName(commonName),
		m_HostName(hostName),
		m_signingCA(signingCA),
		m_validationFailReason(failReason) {}
	
	std::string getCertFile() { return m_certFileAndPath; }
	std::string getUserMessage() { return m_userMsgString; }
	std::string getCommonName() { return m_CommonName; }
	std::string getHostName() { return m_HostName; }
	std::string getSigningCA() { return m_signingCA; }
	int			getValidationFailureReasonCode() { return m_validationFailReason; }
	int			getAcceptDecision() { return m_acceptDecision; }
	void		setAcceptDecision(int decision) { m_acceptDecision = decision;}
	
private:
	
	std::string m_certFileAndPath;
	std::string m_userMsgString;
	std::string m_CommonName;
	std::string m_HostName;
	std::string m_signingCA;
	int			m_validationFailReason;
	
	int 		m_acceptDecision;
};

}
#endif
