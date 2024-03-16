import socket
import time

def measure_dns_lookup_rtt(hostname):
  """
  Measures the round trip time (RTT) for a DNS lookup of a hostname.

  Args:
      hostname: The hostname to perform the DNS lookup for.

  Returns:
      The RTT in seconds as a float, or None if an error occurs.
  """
  try:
    start_time = time.time()
    socket.gethostbyname(hostname)
    end_time = time.time()
    return end_time - start_time
  except socket.gaierror:
    return None

if __name__ == "__main__":
  hostname = "www.milli-vanilli.com" # Use some rarely used domain name to reduce the chance of DNS caching
  rtt = measure_dns_lookup_rtt(hostname)

  if rtt is None:
    print(f"Error: DNS lookup failed for {hostname}")
  else:
    print(f"Round trip time for DNS lookup of {hostname}: {rtt*1000:.2f} miliseconds")