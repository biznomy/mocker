# mocker
  Mock Data using c++ web socket(ws://localhost:8383)
  
 > Dependencies for this project is c++ (poco [1.7.8](https://pocoproject.org/)) librrary and c++11 only, tested on ubuntu 16.04)
 
 > download poco from [here](https://pocoproject.org/releases/poco-1.7.8/poco-1.7.8.tar.gz)
 
 > install c++ using command `sudo apt-get install g++ make`


**configuration file :**

  mocker_conf_8383.json 
  default location of conf file is:  /opt/otfs/install/etc/
  

**if you like to change the data of mocker change data to configuration file**

```
  * lower : refere to the lower range -> airthmetic value
  * upper : refer to the upper range -> airthmetic value
  * fluctuation : refer to the fluctuation value of mean value of airthmetic value of upper and lower limit
```

**Change port number at line 195 '8383' to some other available port**

```
194			// get parameters from configuration file
195			unsigned short port = (unsigned short) config().getInt("WebSocketServer.port", 8383);
196
197			// set-up a server socket
```

**Test data Available At:**

  http://localhost:8383

**Mocker Data branch 9.x.x specific NOTES**
---------------

**Installation Instruction**
    
    step 1 : git clone
    step 2 : change directory to mocker
    step 3 : cp mocker.9.json /**(config file)**/ to configuration location
    step 4 : mkdir bin
    step 5 : make clean install
    step 6 : ./bin/main

**NOTE:-** 
If error while loading shared libraries: libPocoFoundation.so.48: cannot open shared object file: No such file or directory occurs then :
``` 
    sudo find / -iname *libraryname*.so*
    
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/library (either in ~/.bashrc or the Makefile)
```

Initial request is received on http request handler and websocket depend on protocol used

**HTTP** for port 8383

Request
```http://localhost:port/```

Response single response as per the config and schema
```
{
  "sysInfoFalse": {
    "cpu-perc-active": "7.31707",
    "cpu-perc-idle": "92.6829",
    "dsk-free-size": 12198,
    "dsk-total-size": 100763,
    "mem-free-ram": 2256,
    "mem-total-ram": 7833,
    "sys-uptime": 14774
  },
  "system-board": {
 ...
 ...
 ...
 }
  }
}
```

**Websocket** for port 8383

Request 
```ws://localhost:8383``` 
And 
    
>SEND SOME RANDOM TEXT

Response iterative resonse each second

```
{
  "sysInfoFalse": {
    "cpu-perc-active": "7.31707",
    "cpu-perc-idle": "92.6829",
    "dsk-free-size": 12198,
    "dsk-total-size": 100763,
    "mem-free-ram": 2256,
    "mem-total-ram": 7833,
    "sys-uptime": 14774
  },
  "system-board": {
 ...
 ...
 ...
 }
  }
}
```
