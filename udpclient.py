import socket
import math

timeout = 30  #timeout in seconds
bufferSize=1024 #bytes
packSeparator="#"
go=True;

port = 5555

UDPSocket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
UDPSocket.settimeout(timeout)
serverAddress = ('', port)
print('Listening on port ' + str(port))
UDPSocket.bind(serverAddress)
while go:
	[data,attr] = UDPSocket.recvfrom(bufferSize)
	if not data: break
	print(data)
UDPSocket.close()

'''
UDP_IP = "192.168.43.200"
UDP_PORT = 4210
MESSAGE = "Hello, World!\n hjbghjbn"

print "UDP target IP:", UDP_IP
print "UDP target port:", UDP_PORT
print "message:", MESSAGE

sock = socket.socket(socket.AF_INET, # Internet
                    socket.SOCK_DGRAM) # UDP
sock.sendto(MESSAGE, (UDP_IP, UDP_PORT))

'''
































'''
def strings2Floats(listString):

  	out=[]
  	for j in range(0, len(listString)-1):
  		out.append( float(listString[j]))
  	return out

def printSensorsData (dataString):
	packages = dataString.split(packSeparator)
	for pack in packages:
		try:
			pack = pack+","
			lFloat =strings2Floats(pack.split(","))
			numSensors = int(math.floor(len(lFloat)/3))
			for i in range(0,numSensors):
				p=lFloat[i*3:3*(i + 1)]
				print('Sensor' + str(i+1) +  ": " + str(p))
		except:
			pass
'''
