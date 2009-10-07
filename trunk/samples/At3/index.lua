--LuaPlayer Euphoria At3 Sample
--By Zack - www.retroemu.com

--Assign all available colors to a table (makes life easier)
IntraCol = {black = 0, red = 1, blue = 2, white = 3, lightGrey = 4, grey = 5, darkGrey = 6, purple = 7, yellow  = 8, orange = 9, transparent = 10}

--Load our background Image
backGround = Image.load("debug/bk.png")

--Load a Font using IntraFont
font = IntraFont.load("font.pgf")

--Load a At3 into channel 0
At3.load("sample.at3", 0)

local volume = 1.0
local speed = 1.0

--Get last pad state
oldpad = Controls.readPeek()

while not Controls.readPeek():start() do

	pad = Controls.readPeek()

	--Initialize the GU (Note : Any graphical functions MUST be placed AFTER this)
	System.draw()
	
	--Clear the screen
	screen:clear()
	
	--Blit our uber cool background to the screen (with variable alpha)
	screen:blit(0, 0, backGround, alpha)
		
	--Print some controls using IntraFont	
	IntraFont.print(font, 20, 120, 0.5, IntraCol.white, IntraCol.black, "now playing : sample.at3")
	IntraFont.print(font, 20, 150, 0.5, IntraCol.white, IntraCol.black, "press x to pause/unpause")
	IntraFont.print(font, 20, 170, 0.5, IntraCol.white, IntraCol.black, "tap l to decrease the volume")
	IntraFont.print(font, 20, 190, 0.5, IntraCol.white, IntraCol.black, "tap r to increase the volume")
	IntraFont.print(font, 20, 210, 0.5, IntraCol.white, IntraCol.black, "tap square to decrease the playback speed")
	IntraFont.print(font, 20, 230, 0.5, IntraCol.white, IntraCol.black, "tap circle to increase the playback speed")
	IntraFont.print(font, 20, 250, 0.5, IntraCol.white, IntraCol.black, "press start to quit")
	
	--Pause/Unpause the At3
	if pad:cross() and pad:cross() ~= oldpad:cross() then
		At3.pause(0)
	end

	--Lower the At3 volume
	if pad:l() and pad:l() ~= oldpad:l() then
		volume = volume - 0.1
		if volume <= 0.0 then
			volume = 0.0
		end
	end
	
	--Raise the At3 volume
	if pad:r() and pad:r() ~= oldpad:r() then
		volume = volume + 0.1
		if volume >= 1.0 then
			volume = 1.0
		end
	end
	
	--Lower the At3 Playback Speed
	if pad:square() and pad:square() ~= oldpad:square() then
		speed = speed - 0.1
		if speed <= 0.0 then
			speed = 0.0
		end
	end
	
	--Raise the At3 Playback Speed
	if pad:circle() and pad:circle() ~= oldpad:circle() then
		speed = speed + 0.1
		if speed >= 1.0 then
			speed = 1.0
		end
	end
	
	--Finish the GU and Sync
	System.endDraw()
	
	--Show the FPS (Note : MUST be called after System.endGU()
	System.showFPS()
	--Flip buffers
	screen.flip()
	--Assign oldpad to pad
	oldpad = pad
end

IntraFont.unLoad() -- Unload any fonts used by IntraFont
System.quit() -- Quit the application after the main loop breaks
