import numpy as np
from sklearn.linear_model import LinearRegression
import time
import ping3

# Simulated latency data (replace this with your actual data fetching mechanism)
def fetch_latency():
    rtt = None
    while rtt is None:
        rtt = ping3.ping("8.8.8.8")
        if rtt is not None:
           return int(rtt * 1000)
    # Simulate latency as a function of time
    #    return np.random.randint(50, 300)

# Function to collect latency data over a specified interval
def collect_data(interval, num_samples):
    data = []
    for _ in range(num_samples):
        latency = fetch_latency()
        data.append(latency)
        time.sleep(interval)
    return data

# Function to predict future latency using linear regression
def predict_latency(data):
    X = np.arange(len(data)).reshape(-1, 1)
    y = np.array(data)
    model = LinearRegression()
    model.fit(X, y)
    future_X = np.array([[len(data)]])
    future_latency = model.predict(future_X)
    return future_latency[0]

# Main function to continuously monitor network latency
def monitor_latency(interval, num_samples, prediction_window):
    data = collect_data(interval, num_samples)
    print("Initial latency data:", data)

    while True:
        current_latency = fetch_latency()
        print("Current latency:", current_latency)

        # Update data with new latency and predict future latency
        data.append(current_latency)
        data = data[-prediction_window:]  # Retain only the last 'prediction_window' samples
        future_latency = predict_latency(data)

        if int(future_latency) > 200:
            print("Predicted latency is getting sketchy...")
        print("Predicted latency in", prediction_window, "samples:", int(future_latency))

        time.sleep(interval)

if __name__ == "__main__":
    interval = 0.5  # Interval in seconds between latency measurements
    num_samples = 30  # Number of initial samples to collect
    prediction_window = 10  # Window size for predicting future latency
    monitor_latency(interval, num_samples, prediction_window)