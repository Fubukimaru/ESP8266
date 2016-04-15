function createMQTTClient()
	print("Creating MQTT Client")
	--Config thing
	token = "r3hRgolkrLFJ1oTZS9AsL6Ck0xCR7xpDBC_gCOIwqdA"
    m = mqtt.Client("FubuMetro", 120, "", "")

    m:on("offline", function(client)
        print("MQTT offline, reconnecting...")
        --checkConnection()
    end)

    m:connect("mqtt.thethings.io", 1883, 0, function(conn)
        print("MQTT connected")
    end)
end


function sendData()
	pin = 4
	status, temp, humi, temp_dec, humi_dec = dht.read11(pin)
	--m:publish("v2/things/"..token, "{\"values\":[{\"key\":\"button\",\"value\":1}]}", 0, 0, function(client) print("sent") end)		
	if status == dht.OK then
	    -- Float firmware using this example
		print("DHT Temperature:"..temp..";".."Humidity:"..humi.."\n")

		--Mandar info "The things"		
		m:publish("v2/things/"..token, "{\"values\":[{\"key\":\"temperature\",\"value\":"..tostring(temp).."},{\"key\":\"humidity\",\"value\":"..tostring(humi).."}]}", 0, 0, function(client) print("sent\n") end)		

	elseif status == dht.ERROR_CHECKSUM then
		print( "DHT Checksum error." )
	elseif status == dht.ERROR_TIMEOUT then
		print( "DHT timed out." )
	end


end

createMQTTClient()

tmr.alarm(2, 12000, 1, function() sendData() end )
--tmr.alarm(2, 1000, 1, function() sendData() end )
