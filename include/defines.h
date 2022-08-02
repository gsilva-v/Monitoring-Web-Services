#if !defined(DEFINES_H)
# define DEFINES_H

/*General Macros*/ 
# define SUCCESS "OK Success"
# define FAILED "KO The service didn't respond as expected, something might be broken"
# define MONITORED "%s\nMonitored: \033[33m%s\n"
# define STATUS "\033[0mStatus: %s %d\033[0m\n\n"
# define STATUSWD "\033[0mStatus: %s\033[0m\n\n"
# define OK "\033[32mOK"
# define KO "KO"
# define KOE "\033[31mKO expected "
# define FROUTINE "Finish routine\n-----------------------------------------------------\n"
# define FAIL "Some error happened, see \'errors.log\' for more information\n"
# define DIVL "===========================\n"

/*Ping Macros*/ 
# define PINGR "Ping routine started: checking necessary requests ...\n"
# define PING "\033[0mPing: %.1f ms\033[0m\n\n"
# define PLOGOK "%s; Monitored: %s; Url: %s; Protocol: %s; Ping : %.1f;\n"
# define PLOGKO "%s; Monitored: %s; Protocol: %s; Failed to resolve Ping with this service\n"
# define PLOGSOK "%s; Monitored: %s; Ping : %.1f;\n"
# define PLOGSKO "%s; Monitored: %s; Protocol: %s; Ping : Failed;\n"
// Pretty
# define PPLOGOK "Date: %s\nMonitored: %s\nUrl: %s\nProtocol: %s\nPing : %.1f ms\n"
# define PPLOGKO "Date: %s\nMonitored: %s\nUrl: %s\nProtocol: %s\nPing : %.1f ms\n\
Failed to resolve Ping with this service\n"
# define PPLOGSOK "Date: %s\nMonitored: %s\nPing : %.1f ms\n"
# define PPLOGSKO "Date: %s\nMonitored: %s\nProtocol: %s\nFailed to resolve Ping with this service\n" 

/*HTTP Macros*/ 
# define HTTPR "HTTP routine started: checking necessary requests ...\n"
# define HLOG "%s Monitored: %s -> Url: %s; Protocol: %s; Expected Status: %d; \
Returned Status: %d; Working : %s; Ping: %.1f ms\n"
# define HLOGKO "%s; Monitored: %s; Url: %s; Protocol: %s; \
Expected Status: %d; Returned Status: %d; Working : %s; \
Check the address of service and try again; Ping: %.1f ms;"
# define HLOGOK "%s; Monitored: %s; Url: %s; Protocol: %s; \
Expected Status: %d; Returned Status: %d; Working : %s; Ping: %.1f ms;"
# define HLOGS "%s Monitored: %s -> Protocol: %s; Working : %s\n"
// Pretty
# define PHLOGOK "Date: %s\nMonitored: %s\nUrl: %s\nProtocol: %s\n\
Expected Status: %d\nReturned Status: %d\nWorking : %s; \nPing: %.1f ms\n"
# define PHLOGKO "Date: %s\nMonitored: %s\nUrl: %s\nProtocol: %s\n\
Expected Status: %d\nReturned Status: %d\nWorking : %s; \
Check the address of service and try again\nPing: %.1f ms\n"
# define PHLOGS "Date: %s\nMonitored: %s\nProtocol: %s\nWorking : %s\n"

/*DNS Macros*/ 
# define DNSR "DNS routine started: checking necessary requests ...\n"
# define FDNSH "Failed in DNS Handler\n"
# define DNSFLAGS " +timeout=1 +nocomments +short"
# define DLOGOK "%s Monitored: %s -> Url: %s; Protocol: %s; Working : OK; Ping: %.1f ms\n"
# define DLOGKO "%s Monitored: %s -> Url: %s; Protocol: %s; Working : KO \
Service not found in DNS server \'%s\'; Ping: Fail ms\n"
# define DLOGSOK "%s Monitored: %s -> Protocol: %s; Working : OK;\n"
# define DLOGSKO "%s Monitored: %s -> Protocol: %s; Working : KO\n"
// Pretty
# define PDLOGOK "Date: %s\nMonitored: %s\nUrl: %s\nProtocol: %s\nWorking : OK\nPing: %.1f ms\n"
# define PDLOGKO "Date: %s Monitored: %s\nUrl: %s\nProtocol: %s\nWorking : \
Service not found in DNS server \'%s\'\nPing: Fail ms\n"
# define PDLOGSOK "Date: %s Monitored: %s\nProtocol: %s\nWorking : OK\n"
# define PDLOGSKO "Date: %s Monitored: %s\nProtocol: %s\nWorking : KO\n"

/*Error Messages Macros*/ 
# define INVUSE "Sintax error: Invalid flags or option; %s\nUse \"--help\" to see how to use command\n"
# define INVCONF "Invalid config file, Try Another!\n"
# define INVOPT "Invalid flags or option\nUse \"--help\" to see how to use command\n"
# define INVTABS "Error: Columns must be separeted by tabs\n"
# define MISSARG "Need one config file: conf/monitoring.db\n"
# define LOGFAIL "Can't open log file\n"
# define WITHOUTPROTOCOL "For what you want use me without any protocol???"

/*Flags Macros*/ 
# define HELP "Web Monitor: use ./monitoring [file config] [flags]\nAccepted flags: \n\
--simplify | -s: will simplify the generated log.\n\
--pretty : change the layout of log, make this beautiful\n\
--http=[yes/no] : toogle http monitoriment. Default is yes.\n\
--ping=[yes/no] : toogle ping monitoriment. Default is yes.\n\
--dns=[yes/no] : toogle dns monitoriment. Default is yes.\n\
--times=[number of requests] : Control how many request for each config.\n\n"
# define FS "-s"
# define FSIMP "--simplify"
# define FHELP "--help"
# define FHTTP "--http"
# define FPING "--ping"
# define FDNS "--dns"
# define FHTTPON "--http=yes"
# define FHTTPOFF "--http=no"
# define FPINGON "--ping=yes"
# define FPINGOFF "--ping=no"
# define FDNSON "--dns=yes"
# define FDNSOFF "--dns=no"
# define DBEXT ".db"
# define PRETTY "--pretty"

#endif // DEFINES_H
