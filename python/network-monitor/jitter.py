# License: AI generated code - use as you wish
# Shawn Rosti


import subprocess
import statistics
from pythonping import ping

def measure_latency(host, count=5):
  """
  Measures average latency to a specified host using ICMP echo requests.

  Args:
    host: The hostname or IP address to ping.
    count: The number of packets to send (default: 5).

  Returns:
    The average latency in milliseconds, or None if no responses received.
  """

  responses = ping(host, count=count)

  if responses:
    return responses.rtt_avg_ms
  else:
    return None

#experiment with scapy, so we don't have to scrap the "ping" output
# Note: ran into socket permission issues, scapy may be to overweight for this application. Tabling this for now
# Fixed the permision issue: sudo setcap cap_net_raw=eip /path/to/python_interpreter
# Gemini generated wrong code here, needed to fix it
from scapy.all import *
import time
def measure_latency_scapy(host, count=5):
    """
    Measures average latency to a specified host using ICMP echo requests.

    Args:
        host: The hostname or IP address to ping.
        count: The number of packets to send (default: 5).

    Returns:
        The average latency in milliseconds, or None if no responses received.
    """

    total_latency = 0
    received_count = 0

    for i in range(count):
        packet = IP(dst=host)/ICMP()
        reply = sr1(packet, timeout=2, verbose=0)  # Send and receive a single packet

        if reply is not None:
            latency = (reply.time - packet.sent_time) * 1000  # Calculate latency in milliseconds
            total_latency += latency
            received_count += 1

    if received_count > 0:
        return total_latency / received_count
    else:
        return None


def measure_latency_jitter(host, count=50):
    """Measures latency and jitter to a specified host."""

    latencies = []
    for _ in range(count):
        try:
            # Use ping to measure latency
            result = subprocess.run(['ping', '-c', '1', host], capture_output=True, text=True)
            # srosti - modified to match the output of my version of ping
            latency_ms = int(float(result.stdout.splitlines()[1].split()[-2].split('=')[1]))
            latencies.append(latency_ms)
        except Exception as e:
            print(f"Error measuring latency: {e}")

    if latencies:
        average_latency = statistics.mean(latencies)
        jitter = statistics.stdev(latencies)
        print(f"Average latency to {host}: {average_latency:.2f} ms")
        print(f"Jitter: {jitter:.2f} ms")
    else:
        print("No valid latency measurements obtained.")

if __name__ == "__main__":
    host = "8.8.8.8"  # Replace with the desired host
    #measure_latency_jitter(host)
    latency=measure_latency_scapy(host)
    print(f"Average Latency (scapy)={latency}")
    latency=measure_latency(host)
    print(f"Average Latency (pythonping)={latency}")