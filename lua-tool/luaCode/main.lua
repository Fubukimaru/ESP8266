--tmr.alarm(3, 500, 1, function()
--   if wifi.sta.getip() == nil then
--      print("Connecting to AP...")
--   else
--      print('IP: ',wifi.sta.getip())
--      tmr.stop(0)
--   end
--end)


dofile("dht.lua")
dofile("sleep.lua")
