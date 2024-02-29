# ArduinoCore-rl78g23_fpb_64p

This repository contains the source code and configuration files of the Arduino Core for Renesas RL78/G23-64p Fast Prototyping Board platform.

# Quick Start Guide and more information

The wiki below includes ‘Quick Start Guide’ about how to install and use Arduino Library on the Renesas Board and more information.  Please try to take a look at the site.

  * https://github.com/renesas/Arduino/wiki

# Set udev rules for Renesas RL78 boards on Linux

If you have any troubles in failed uploads on Linux, please try to set udev rules for Renesas RL78 Boards.  
(This description will be posted to the [Arduino Wiki](https://github.com/renesas/Arduino/wiki) in the future and will be removed from here.)

* You can set the udev rules by running `post_install.sh` as root.

* Follow these steps:

1. Go to the [post_install.sh file for Renesas Boards on GitHub](https://github.com/renesas/Arduino).

2. Download the file to your computer.

   ![The "Download raw file" button on github.com](https://support.arduino.cc/hc/article_attachments/9005017123484)

3. Open your Download folder in Terminal:

   - **On Ubuntu:** Open the Files application and navigate to your Download folder. Right-click on an empty area inside the folder (not on a file) and select **Open in Terminal**.

   - Open Terminal, and navigate to your Download folder:

     `cd ~/Downloads`

4. Run this command:

   `sudo ./post_install.sh`

5. If prompted, enter your password, and press Enter again.

Try uploading your sketch again.