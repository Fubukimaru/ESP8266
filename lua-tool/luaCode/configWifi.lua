wifi.setmode(wifi.STATION)
wifi.sta.config("Orange-7360","zhpKKkmc")
wifi.sta.connect()

print('Network mode:', wifi.getmode())
print('Wifi Config:', wifi.sta.getconfig())

