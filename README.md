# ServiceControl

chkservice is the basis for ServiceControl.

This is a Qt Creator project!

Also download Qt Creator.

You need to set two options before you can begin.

That is the clock leap in my development and also consists of parts of this preliminary work.

chkservice can be installed on Ubuntu with:

> apt install chkservice

https://github.com/caparisotto/chkservices

https://github.com/hflautert/chkservices

https://github.com/linuxenko/chkservice

![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/ServiceControl_v1.0.4/Screenshot/ServiceControl_v1.0.4.png)

![ServiceControl](https://github.com/fett-tony/ServiceControl/blob/ServiceControl_v1.0.4/Screenshot/ServiceControl_v1.0.4_2.png)

# 1. The first option is Shadowbuild Must Off.

This has to be done because this project has a special folder system for the build.

![ShadowBuild](https://github.com/fett-tony/NcursesWindowTemplate/blob/main/README/ShadowBuild.png)

# 2. The second option is for the debugger

when you need to work with threads or pthread you must set SIGSTOP options off.
for running with thread or pthread option

you must set "handle SIGSTOP pass nostop noprint" into the Debugger option for "Locals & Expressions".

> TOOLS -> Options -> Debugger -> Locals & Expressions -> Debugging Helper Customization

> handle SIGSTOP pass nostop noprint

![Debugging_Helper_Customization](https://github.com/fett-tony/NcursesWindowTemplate/blob/main/README/Debugging_Helper_Customization.png)


