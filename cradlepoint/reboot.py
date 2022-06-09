#!/usr/bin/env python3
import sys
import subprocess
import random
import re
from time import strftime, sleep 
import json

addr = ''
ipaddr = '192.168.0.1'
if len(sys.argv) > 1:
	addr = sys.argv[1]
else:
	addr = input('Enter admin password: ')
if len(sys.argv) > 2:
	ipaddr = sys.argv[2]
url = None
router_outlet = 5 #plug router into outlet 5, or change this value to match

random.seed()

def sleep_delay(seconds):
	#print("Sleeping for %d seconds"%(seconds))
	orig = seconds
	while seconds != 0:
		print("Sleeping for %d seconds ( %04d )"%(orig, seconds), end='\r')
		sys.stdout.flush()
		sleep(1)
		seconds-=1
	print("")

def get_val(pth,timeout=20):
	get_req = 'curl -s  -u admin:{} --connect-timeout {} -X GET http://{}/api/{}'.format(addr, timeout, ipaddr, pth)
	proc = subprocess.Popen(get_req.split(),stdout=subprocess.PIPE)
	resp = proc.communicate()[0]
	#communicate returns a bytes array. Need to convert to string so we can do a regular expression match
	try:
		resp = resp.decode("utf-8")
	except Exception as e:
		print("get_val, no decode")
		return None, -1

	try:
		json_data = json.loads(resp)
		if json_data == None:
			print("get_val, no json")
			return None, -1
		if json_data['success'] == False:
			#print("get_val, returned false")
			return None, 0
		else:
			#print("get_val, returned true")
			return json_data['data'],1
	except:
		print("get_val, exception")
		return None,-1


def put_val(pth,val,timeout=20):
	put_req = 'curl -s  -u admin:{} --connect-timeout {} -X PUT http://{}/api/{} -d data={}'.format(addr,timeout,ipaddr, pth,val)
	proc = subprocess.Popen(put_req.split(),stdout=subprocess.PIPE)
	resp = proc.communicate()[0]
	#communicate returns a bytes array. Need to convert to string so we can do a regular expression match
	try:
		resp = resp.decode("utf-8")
	except Exception as e:
		return None,-1

	try:
		json_data = json.loads(resp)
		if json_data == None:
			return None,-1
		if 'success' not in json_data:
			return None,-1

		if json_data['success'] == False:
			return None,0
		else:
			data = json_data['data']
			return data,1
	except:
		return None,-1


def get_device_list():
	dev_list = []

	pth = 'status/wan/devices'
	devices, res = get_val(pth)
	if res != 1:
		return dev_list

	for dev in devices:
		#print("device: {}".format(dev))
		dev_name = "{}".format(dev)
		#print("data: {}".format(devices[dev]))
		#print("Dev status: {}".format(devices[dev]['status']['summary']))
		if 'mdm' in dev_name:
			status = devices[dev]['status']['summary']
			port = devices[dev]['info']['port']

			validstatus = ('configure error')
			if status in validstatus:
				print("Add device {} with status {} on port {}".format(dev, status,port))
				dev_list.append(dev)
	return dev_list

def ping_router():
	# ping to see if router is up, if not sleep and continue
	ping_args = ['ping', '-q', '-c', '1', '-w','10', ipaddr]
	proc = subprocess.Popen(ping_args,stdout=subprocess.PIPE)
	data = proc.communicate()[0]
	#communicate returns a bytes array. Need to convert to string so we can do a regular expression match
	val = data.decode("utf-8")
	#print("ping response: {}".format(val))
	ver = re.search(r'.*0 received',val,flags=0)
	if ver != None:
		return False
	else:
		return True


def remote_router_reboot(outlet):
	router_power_cycle = ['curl', '-s', '--user', '{}:{}'.format('admin','1234'), '-X', 'GET', 'http://192.168.0.100/outlet?{}=CCL'.format(outlet)]
	print("Cycling power on outlet: {}".format(outlet))
	proc = subprocess.Popen(router_power_cycle,stdout=subprocess.PIPE)
	data = proc.communicate()[0]
	val = data.decode("utf-8")


soft_reset = True
delay = 10

while 1:
	#print("Sleeping for %d seconds..."%(delay))
	sleep_delay(delay)
	time = strftime("%Y-%m-%d %H:%M:%S")

	try:
		# ping to see if router is up, if not sleep and continue
		print(time, "Pinging router....")
		res = ping_router()
		if res == False:
			print(time, "No response from router")
			delay = 10
			continue
		else:
			print(time, "Got response from router")

#		dev_names = get_device_list()
#		num_devs = len(dev_names)
#		#print("dev_len: {}. type:{}".format(num_devs,type(devices)))
#		if num_devs < 1:
#			print(time, "**** NO valid wandevs found *****")
#			delay = 10
#			continue

#		time = strftime("%Y-%m-%d %H:%M:%S")
#		print(time, "Found %d wandevs"%(num_devs))

		print(time, "Rebooting router")
		if soft_reset:
			pth = 'control/system/reboot'
			val = 'true'
			data,res = put_val(pth,val)
			if res != 1:
				print("Failed to reboot device for some reason.")
				continue
		else:
			remote_router_reboot(router_outlet)

		#delay = random.randint(600,700)
		delay = random.randint(60,61)
	except Exception as e:
		print("Exception: {}", e)
		continue

