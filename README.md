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
