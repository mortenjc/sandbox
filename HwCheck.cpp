///
///

#include <HwCheck.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>


HwCheck::HwCheck() {};

bool HwCheck::checkMTU(std::string interface, int mtu) {
  int s, af = AF_INET;
	struct ifreq ifr;

	if ((s = socket(af, SOCK_DGRAM, 0)) < 0) {
		printf("error: socket\n");
  }

	ifr.ifr_addr.sa_family = af;
	strcpy(ifr.ifr_name, interface.c_str());
	if (ioctl(s, SIOCGIFMTU, (caddr_t)&ifr) < 0) {
		printf("warn: ioctl (get mtu): %s\n", ifr.ifr_name);
    return false;
  }

	fprintf(stdout, "MTU of %s is %d\n", interface.c_str(), ifr.ifr_mtu);
	close(s);

  return ifr.ifr_mtu == mtu;
}


int main(int argc, char * argv []) {
  HwCheck hwcheck;
  hwcheck.checkMTU("lo0", 9000);
  hwcheck.checkMTU("fw0", 9000);
}
