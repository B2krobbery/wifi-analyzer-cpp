#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// -------- Get interfaces --------
std::vector<std::string> getInterfaces() {
  std::vector<std::string> interfaces;

  FILE *pipe = popen("iw dev | awk '$1==\"Interface\"{print $2}'", "r");
  if (!pipe)
    return interfaces;

  char buffer[128];
  while (fgets(buffer, sizeof(buffer), pipe)) {
    std::string iface = buffer;
    iface.pop_back();
    interfaces.push_back(iface);
  }

  pclose(pipe);
  return interfaces;
}

// -------- Select interface --------
std::string selectInterface() {
  auto interfaces = getInterfaces();

  if (interfaces.empty()) {
    std::cout << "No interfaces found\n";
    exit(1);
  }

  std::cout << "\nAvailable Interfaces:\n";
  for (int i = 0; i < interfaces.size(); i++) {
    std::cout << i + 1 << ". " << interfaces[i] << "\n";
  }

  int choice;
  std::cout << "Select interface: ";
  std::cin >> choice;

  return interfaces[choice - 1];
}
//---------Desable monitor mod-----------//
void disableMonitor(std::string iface) {
  std::cout << "[INFO] Restoring normal Wi-Fi mode...\n";

  std::string cmd;

  cmd = "sudo ip link set " + iface + " down";
  system(cmd.c_str());

  cmd = "sudo iw dev " + iface + " set type managed";
  system(cmd.c_str());

  cmd = "sudo ip link set " + iface + " up";
  system(cmd.c_str());

  system("sudo systemctl restart NetworkManager");

  std::cout << "✅ Switched back to managed mode (normal Wi-Fi)\n";
}

// -------- Enable monitor mode --------
void enableMonitor(std::string iface) {
  std::string cmd;

  cmd = "sudo ip link set " + iface + " down";
  system(cmd.c_str());

  cmd = "sudo iw dev " + iface + " set type monitor";
  system(cmd.c_str());

  cmd = "sudo ip link set " + iface + " up";
  system(cmd.c_str());

  std::cout << "Monitor mode enabled on " << iface << "\n";
}

// -------- Verify monitor mode --------
bool isMonitorMode(std::string iface) {
  FILE *pipe = popen("iw dev", "r");
  if (!pipe)
    return false;

  char buffer[256];
  std::string output;

  while (fgets(buffer, sizeof(buffer), pipe)) {
    output += buffer;
  }

  pclose(pipe);

  return (output.find("Interface " + iface) != std::string::npos &&
          output.find("type monitor") != std::string::npos);
}

// -------- Run scan --------
void startScan(std::string iface) {
  std::string cmd = "sudo airodump-ng " + iface;
  system(cmd.c_str());
}
// -------- Check kill--------
void checkKill() {
  std::cout << "[INFO] Checking and killing interfering processes...\n";
  int res = system("sudo airmon-ng check kill");

  if (res == 0) {
    std::cout << "✅ Processes handled successfully\n";
  } else {
    std::cout << "❌ Failed to run check kill\n";
  }
}

// -------- MAIN MENU --------
int main() {
  std::string iface = selectInterface();

  int option;

  while (true) {
    std::cout << "\n==== WIFI TOOL ====\n";
    std::cout << "1. Check & Kill Interfering Processes\n";
    std::cout << "2. Enable Monitor Mode\n";
    std::cout << "3. Start Scan (Airodump)\n";
    std::cout << "4. Disable Monitor Mode (Normal Wi-Fi)\n";
    std::cout << "5. Exit\n";
    std::cout << "Choose option: ";
    std::cin >> option;

    if (option == 1) {
      checkKill();
    } else if (option == 2) {
      enableMonitor(iface);

      if (isMonitorMode(iface))
        std::cout << "Monitor mode verified ✅\n";
      else
        std::cout << "Monitor mode failed ❌\n";
    } else if (option == 3) {
      if (!isMonitorMode(iface)) {
        std::cout << "⚠ Enable monitor mode first!\n";
      } else {
        startScan(iface);
      }
    } else if (option == 4) {
      disableMonitor(iface);
    } else if (option == 5) {
      break;
    }

    else {
      std::cout << "Invalid option\n";
    }
  }

  return 0;
}
