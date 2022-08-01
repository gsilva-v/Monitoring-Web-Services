# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <curl/curl.h>

char	*strjoin(const char *s1, const char *s2){
	int		n = 0, s = 0;
	char	*new = (char *) malloc (sizeof(char) * (strlen(s1) + strlen(s2)) + 1);

	if (!new)
		return (NULL);
	while (s1[n] != '\0'){	
		new[n] = s1[n];
		n++;
	}
	while (s2[s] != '\0'){
		new[n + s] = s2[s];
		s++;
	}
	new[n + s] = '\0';
	return (new);
}


int main(int argc, char const *argv[])
{	
	int fd = open("./logs/dns.log", O_CREAT | O_TRUNC | O_RDWR , 0777);
	
	if (fd < 0){
		printf("nao criou o arquivo\n");
		exit (1);
	}

	int _stdout = dup(STDOUT_FILENO);

// google	DNS	google.com	30	8.8.8.8

	char *endereco = strdup(" yahoo.com");
	char *dns_server = strdup("8.8.8.8");
	int pause = 3;

	char *query = strjoin("dig @", dns_server);
	query = strjoin(query, endereco);
	query = strjoin(query, " +timeout=1 +nocomments +short");
	
	while (true){
		dup2(fd, STDOUT_FILENO);
		int ret = system(query);
		dup2(_stdout, STDOUT_FILENO);
		if (ret != 0){
			printf("esse endereço nao existe nesse servidor DNS, veja se as informações estão corretas ou se o endereço esta funcionando corretamente\n");
		}else 
			printf("sucesso na ultima request\n");

		sleep(pause);
	}
	

	return 0;
}





// static void
// state_cb(void *data, int s, int read, int write)
// {
//     printf("Change state fd %d read:%d write:%d\n", s, read, write);
// }


// static void
// callback(void *arg, int status, int timeouts, struct hostent *host)
// {

//     if(!host || status != ARES_SUCCESS){
//         printf("Failed to lookup %s\n", ares_strerror(status));
//         return;
//     }

//     printf("Found address name %s\n", host->h_name);
//     char ip[INET6_ADDRSTRLEN];
//     int i = 0;

//     for (i = 0; host->h_addr_list[i]; ++i) {
//         inet_ntop(host->h_addrtype, host->h_addr_list[i], ip, sizeof(ip));
//         printf("%s\n", ip);
//     }
// }

// static void
// wait_ares(ares_channel channel)
// {
//     for(;;){
//         struct timeval *tvp, tv;
//         fd_set read_fds, write_fds;
//         int nfds;

//         FD_ZERO(&read_fds);
//         FD_ZERO(&write_fds);
//         nfds = ares_fds(channel, &read_fds, &write_fds);
//         if(nfds == 0){
//             break;
//         }
//         tvp = ares_timeout(channel, NULL, &tv);
//         select(nfds, &read_fds, &write_fds, NULL, tvp);
//         ares_process(channel, &read_fds, &write_fds);
//     }
// }

// int
// main(void)
// {
//     ares_channel channel;
//     int status;
//     struct ares_options options;
//     int optmask = 0;

//     status = ares_library_init(ARES_LIB_INIT_ALL);
//     if (status != ARES_SUCCESS){
//         printf("ares_library_init: %s\n", ares_strerror(status));
//         return 1;
//     }
//     //options.sock_state_cb_data;
//     options.sock_state_cb = state_cb;
//     optmask |= ARES_OPT_SOCK_STATE_CB;

//     status = ares_init_options(&channel, &options, optmask);
//     if(status != ARES_SUCCESS) {
//         printf("ares_init_options: %s\n", ares_strerror(status));
//         return 1;
//     }

//     ares_gethostbyname(channel, "google.com", AF_INET, callback, NULL);
//     //ares_gethostbyname(channel, "google.com", AF_INET6, callback, NULL);
//     wait_ares(channel);
//     ares_destroy(channel);
//     ares_library_cleanup();
//     printf("fin\n");
//     return 0;
// }