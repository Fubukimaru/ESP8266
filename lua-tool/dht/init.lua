sleep = 5 --minutes to sleep
wait = 3 --seconds before executing file
gsleep = 20 --seconds until it goes to sleep, don't go below 20

FileToExecute="readdht22.lua" --file to execute
l = file.list()
for k,v in pairs(l) do
  if k == FileToExecute then
    print("*** You've got "..wait.." sec to stop timer 0 ***")
    tmr.alarm(0, (wait*1000), 0, function()
		print("Executing ".. FileToExecute)
		dofile(FileToExecute)
    end)
	--tmr.alarm(1, gsleep*1000, 0, function()
	--	print("timer1 trigger dsleep")
	--	node.dsleep(sleep*60*1000*1000)
	-- end)
  end
end