gsleep=20 --sec to retry sleep
sleep=60 -- sec of sleep
alarmToSec=1000
sleepToSec=1000000

print("Reached sleep target")
tmr.alarm(5, gsleep*alarmToSec, tmr.ALARM_AUTO, function()
	if not inUse then 
		print("Node not in use. Sleep")
		node.dsleep(sleep*sleepToSec, 4)
	end
end)

