# License: AI generated code - use as you wish
# Shawn Rosti
import subprocess
import statistics

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
    measure_latency_jitter(host)