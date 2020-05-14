
#include <string>

class HwCheck {
public:
  HwCheck();

  bool checkMTU(std::string interface, int mtu);
private:
};
