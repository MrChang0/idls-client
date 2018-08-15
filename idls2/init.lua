local device = {
    uuid = "00000010000000100000002",
    type = "example",
    descrpition = "test",
    signals = {
        {
            name = "signalA",
            args = {}
        }
    },
    events = {
        {
            name = "eventA",
            args = {
                {
                    name = "a",
                    type = "string"
                }
            }
        }
    }
}

gpio.mode(4,gpio.OUTPUT)
local events = {
    eventA = function(args)
        print("eventA")
        local a = args[1].data
        print(a)
        if a == "open" then
            gpio.write(4,gpio.LOW)  
        elseif a == "close" then
            gpio.write(4,gpio.HIGH)
        end
    end
}

local ip = "192.168.1.100"
local port = 5566
local ver = "idp.v1"

function pack(data)
    local length = #data
    return string.char(length/256,length%256) .. data
end

local cmds = {}
cmds["register"] = function(sck,data)
    local client = {
        proto = ver,
        prototype = "register",
        data = device
    }
    sck:send(pack(sjson.encode(client)))
end

cmds["event"] = function(sck,event)
    events[event.name](event.args)
end

local rev_cb = function(sck,c)
    local length = c:byte(1)*256 + c:byte(2)
    local data = string.sub(c,3)
    if length ~= string.len(data) then
        print("data error")
        return 
    end
    print(data)
    local tab = sjson.decode(data)
    cmds[tab.command](sck,tab.data)
end

local online = function()
    local client={
        proto = "idp.v1",
        prototype = "online",
        data = {
            uuid = device.uuid
        }
    }
    return sjson.encode(client)
end

local signalA = function()
    local client = {
        proto = "idp.v1",
        prototype = "signal",
        data = {
            name = "signalA",
            arg = {}
        }
    }
    return sjson.encode(client)
end

local wifi_cb = function(T)
    print("wifi connected")
    print(wifi.sta.getip())
    local conn = net.createConnection(net.TCP,0)
    conn:on("receive",rev_cb)
    conn:on("connection",function(sck)
        print("connect success")
        sck:send(pack(online()))
        function onBtnEvent()
            gpio.trig(1)
            tmr.alarm(0,500,tmr.ALARM_SINGLE,function()
                gpio.trig(1,'down',onBtnEvent)
            end)
            print("send signalA")
            sck:send(pack(signalA()))
        end
        gpio.trig(1,'down',onBtnEvent)
    end)
    conn:on("disconnection",function(sck,c)
        print("socket disconnected",c)
    end)
    conn:connect(port, ip)
end

wifi.setmode(wifi.STATION)

wifi.eventmon.register(wifi.eventmon.STA_GOT_IP,wifi_cb)

station_cfg={}
station_cfg.ssid="IDMS"
station_cfg.pwd="12345678"
station_cfg.auto=false
wifi.sta.config(station_cfg)
wifi.sta.connect()

gpio.mode(1,gpio.INT,gpio.PULLUP)


