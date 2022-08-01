#if !defined(DEFINES_H)
# define DEFINES_H

/*General Macros*/ 
# define SUCCESS "OK Success"
# define FAILED "KO The service didn't respond as expected, something might be broken"
# define MONITORED "%s Monitored: \033[33m%s\n"
# define STATUS "\033[0mStatus: %s %d\033[0m\n\n"
# define STATUSWD "\033[0mStatus: %s\033[0m\n\n"
# define OK "\033[32mOK"
# define KO "KO"
# define KOE "\033[31mKO expected "
# define FROUTINE "Finish routine\n-----------------------------------------------------\n"

/*Ping Macros*/ 
# define PINGR "Ping routine started: checking necessary requests ...\n"
# define PING "\033[0mPing: %.1f ms\033[0m\n\n"
# define PLOG "%s Monitored: %s -> Url: %s; Ping : %.1f ms\n"
# define PLOGS "%s Monitored: %s -> Ping : %.1f ms\n"

/*HTTP Macros*/ 
# define HTTPR "HTTP routine started: checking necessary requests ...\n"
# define HLOG "%s Monitored: %s -> Url: %s; Protocol: %s; Expected Status: %d; Working : %s; Ping: %.1f ms\n"
# define HLOGS "%s Monitored: %s -> Protocol: %s; Working : %s\n"

/*DNS Macros*/ 
# define DNSR "DNS routine started: checking necessary requests ...\n"
# define DLOG "%s Monitored: %s -> Url: %s; Protocol: %s; Working : %s; Ping: %.1f ms\n"
# define DLOGS "%s Monitored: %s -> Protocol: %s; Working : %s\n"
# define FDNSH "Failed in DNS Handler\n"
# define DNSFLAGS " +timeout=1 +nocomments +short"


/*Error Messages Macros*/ 
# define INVUSE "Sintax error: Invalid flags or option; %s\nUse \"--help\" to see how to use command\n"
# define INVCONF "Invalid config file, Try Another!\n"
# define INVOPT "Invalid flags or option\nUse \"--help\" to see how to use command\n"
# define INVTABS "Error: Columns must be separeted by tabs\n"
# define MISSARG "Need one config file: conf/monitoring.db\n"
# define LOGFAIL "Can't open log file\n"

/*Flags Macros*/ 
# define HELP "Web Monitor: use ./monitoring [file config] [flags]\nAccepted flags: \n\
--simplify | -s: will simplify the generated log.\n\
--http=[yes/no] : toogle http monitoriment. Default is yes.\n\
--ping=[yes/no] : toogle ping monitoriment. Default is yes.\n\
--dns=[yes/no] : toogle dns monitoriment. Default is yes.\n\n"
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


#endif // DEFINES_H
