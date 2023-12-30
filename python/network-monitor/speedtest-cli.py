import speedtest

# Create a Speedtest object
st = speedtest.Speedtest()

# Perform the speed test
try:
    # Find the best server to connect to
    st.get_best_server()

    # Measure download speed
#    download_speed = st.download() / 1024 / 1024  # Convert bits per second to megabits per second

    # Measure upload speed
    upload_speed = st.upload() / 1024 / 1024  # Convert bits per second to megabits per second

    # Print the results
    print(f"ISP: {st.config['client']['isp']}")
#    print(f"Download speed: {download_speed:.2f} Mbps")
    print(f"Upload speed: {upload_speed:.2f} Mbps")

except speedtest.SpeedtestException as e:
    print(f"Error: Could not perform speed test: {e}")