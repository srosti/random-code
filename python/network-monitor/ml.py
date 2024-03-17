from scapy.all import sniff
from statistics import mean, stdev  # for calculating statistics

# Define threshold for standard deviation multiplier (adjust as needed)
threshold_multiplier = 3

# Function to store and analyze latencies
def analyze_latency(packet):
  global last_received_times, latency_data
  current_time = packet.time
  if last_received_times:
    # Calculate latency as difference between current and previous packet time
    latency = current_time - last_received_times[-1]
    latency_data.append(latency)
    # Check for latency anomaly based on standard deviation
    if len(latency_data) > 10:  # Minimum data points for analysis (adjust as needed)
      average_latency = mean(latency_data)
      std_dev = stdev(latency_data)
      if latency > (average_latency + (threshold_multiplier * std_dev)):
        print(f"Anomaly detected! Latency: {latency:.3f}s (exceeds threshold)")
  last_received_times.append(current_time)

# Initialize variables
last_received_times = []
latency_data = []

# Start capturing packets and analyze latencies
sniff(prn=analyze_latency)