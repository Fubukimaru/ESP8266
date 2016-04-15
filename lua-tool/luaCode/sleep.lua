gsleep=10 --sec to retry sleep
sleep=300 -- sec of sleep

print("Reached sleep target")
tmr.alarm(5, gsleep*1000, 1, function()
	if not inUse then 
		print("Node not in use. Sleep")
		node.dsleep(sleep*1000)
	end
end)

