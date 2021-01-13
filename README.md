# ServiceControl

systemctl is the basic. ServiceControl this is a Qt creator project!

also download Qt Creator.

This is a Qt Creator Projekt for run you musst set two options.

That is the clock jump of my development and also consists of parts of this preliminary work.

chkservice can be installed on Ubuntu with:

> apt install chkservice

https://github.com/caparisotto/chkservices

https://github.com/hflautert/chkservices

https://github.com/linuxenko/chkservice

![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/main/Screenshot/ServiceControll-v1.0.2.png)


# 1. the first option is shadowbuild muss off.

this is while this projekt have own options into the pro file and work with a special folder set.

![ShadowBuild](https://github.com/fett-tony/NcursesWindowTemplate/blob/main/README/ShadowBuild.png)

# 2. the second option for debugger

when you need to work with threads or pthread you must set SIGSTOP options off.
for running with thread or pthread option

you musst set "handle SIGSTOP pass nostop noprint" into the Debugger option for "Locals & Expressions".

> TOOLS -> Options -> Debugger -> Locals & Expressions -> Debugging Helper Customization

> handle SIGSTOP pass nostop noprint

![Debugging_Helper_Customization](https://github.com/fett-tony/NcursesWindowTemplate/blob/main/README/Debugging_Helper_Customization.png)



![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/main/Screenshot/ServiceControl-1.png)
![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/main/Screenshot/ServiceControl-2.png)
![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/main/Screenshot/ServiceControl-3.png)
![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/main/Screenshot/ServiceControll-branch.png)
