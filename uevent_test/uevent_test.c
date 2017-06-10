#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/types.h>  
#include <asm/types.h>  
#include <sys/socket.h>    
#include <linux/netlink.h> 


#define UEVENT_MSG_LEN 4096

int main(void)
{
	int s;
	int ret;
	char buf[UEVENT_MSG_LEN];
	struct sockaddr_nl addr;

	memset(&addr, 0, sizeof(addr));
	addr.nl_family = AF_NETLINK;
	addr.nl_pid = getpid();
	addr.nl_groups = 0xffffffff;

	s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
	if (s < 0) {
		perror("socket");
		exit(-1);
	}
	
	ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0) {
		perror("bind");
		close(s);
		exit(-1);
	}
	
	for (;;) {
		memset(buf, 0 sizeof(buf));
		ret = recv(s, buf, sizeof(buf), 0);
		if (ret < 0) {
			printf("receive error!\n");
		} 
		printf("recv: %s\n", buf);			
	}
	
	return 0;
}