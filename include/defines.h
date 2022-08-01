#if !defined(DEFINES_H)
#define DEFINES_H

# define SUCCESS "OK Success"
# define FAILED "KO The service didn't respond as expected, something might be broken"
# define MONITORED "%s Monitored: \033[33m%s\n"
# define STATUS "\033[0mStatus: %s %d\033[0m\n\n"
# define PING "\033[0mPing: %.1f ms\033[0m\n\n"
# define PLOG "%s Monitored: %s -> Url: %s; Ping : %.1f ms\n"
# define PLOGS "%s Monitored: %s -> Ping : %.1f ms\n"
# define HLOG "%s Monitored: %s -> Url: %s; Protocol: %s; Expected Status: %d; Working : %s; Latency: %.1f\n"
# define HLOGS "%s Monitored: %s -> Protocol: %s; Working : %s\n"
# define DLOG "%s Monitored: %s -> Url: %s; Protocol: %s; Working : %s; Latency: %.1f\n"
# define DLOGS "%s Monitored: %s -> Protocol: %s; Working : %s\n"
# define OK "\033[32mOK"
# define KO "KO"
# define KOE "\033[31mKO expected "
# define FROUTINE "Finish routine\n-----------------------------------------------------\n"
# define INVCONF "Invalid config file, Try Another!\n"
# define INVTABS "Error: Columns must be separeted by tabs\n"
# define MISSARG "Need one config file: conf/monitoring.db"
# define HELP "Web Monitor: use ./monitoring [file config] [flags]\nAccepted flags: \n--simplify : will simplify the generated log\n"
# define INVUSE "Sintax error: Invalid flags or option; %s\nUse \"--help\" to see how to use command\n"


#endif // DEFINES_H
