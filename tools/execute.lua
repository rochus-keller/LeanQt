os = require "os"

local cmd = ""
for i = 1,#arg do
	cmd = cmd .. arg[i] .. " "
end
os.execute(cmd)
