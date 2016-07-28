print('init.lua ver 1.2')
print('set mode=STATION (mode='..wifi.getmode()..')')
print('MAC: ',wifi.sta.getmac())
print('chip: ',node.chipid())
print('heap: ',node.heap())


dofile("configWifi.lua")


-- wait for an IP
cnt = 20
tmr.alarm(0,1000,1,function()
  if wifi.sta.getip()==nil then
    cnt = cnt-1
    print "Not IP yet. Retry..."
    if cnt<=0 then
      -- Did not get an IP in time, so quitting
      tmr.stop(0)
      print "Not connected to wifi."
    end
  else

    -- Connected to the wifi
    tmr.stop(0)
    --services
    dofile("services.lua")
    print("Services UP")

    print("Executing main")
    dofile("main.lua")
  end
end)
