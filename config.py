import ConfigParser

config = ConfigParser.ConfigParser()

config.read("/Users/adore/Documents/Petri Net/Petri Net/config")

def getvalue(name, type):
    k = config.get(name, type)
    if ':' in k:
        tmp = []
        for i in k.split(':'):
            tmp.append(int(i))
        return tmp
    else:
        return int(k)

def getflux(orientation):
    k = config.get("flux", orientation)
    tmp = k.split(':')
    t = []
    t.append(float(tmp[0]))
    t.append(float(tmp[1]))
    t.append(float(tmp[2]))
    t.append(float(tmp[3]))
    return t;