PORT=/dev/ttyUSB0
./luatool.py --port $PORT --src luaCode/init.lua 
./luatool.py --port $PORT --src luaCode/services.lua 
./luatool.py --port $PORT --src luaCode/configWifi.lua 
./luatool.py --port $PORT --src luaCode/telnet_srv.lua 


