print('init.lua ver 1.2')
print('set mode=STATION (mode='..wifi.getmode()..')')
print('MAC: ',wifi.sta.getmac())
print('chip: ',node.chipid())
print('heap: ',node.heap())


dofile("configWifi.lua")


--services
dofile("services.lua")
print("Services UP")




print("Executing main")
dofile("main.lua")
